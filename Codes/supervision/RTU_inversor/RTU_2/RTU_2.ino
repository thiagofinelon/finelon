#include <WiFi.h>
#include <ArduinoJson.h>
#include <AWS_IOT.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

AWS_IOT hornbill;   // AWS_IOT instance

char HOST_ADDRESS[] = "a8qqcuirk75wq.iot.us-east-1.amazonaws.com";
char CLIENT_ID[] = "esp32";
char TOPIC_NAME[] = "event/inversor";
char payload[256];

File root;

const char* ssid     = "solar2";
const char* password = "solar2ufms";

WiFiServer server(80);
WiFiClient cliente;

int cont = 0;
float P_AC, I_AC, V_AC, I_DC, V_DC = 0;
char timestamp[20];
boolean flag = false;

void setup()
{
  Serial.begin(115200);

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
/*
  if (!SD.begin(15)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }*/
}

void loop() {
  cliente = server.available();
  if (cliente) {
    inverterRead();

    if (cont == 2) {
      sprintf(payload, "{\"tipo\":\"inverter\", \"timestamp\":%s, \"P_AC\":%f, \"V_AC\":%f, \"I_AC\":%f, \"V_DC\":%f, \"I_DC\":%f}", timestamp, P_AC, V_AC, I_AC, V_DC, I_DC);

      //send2aws_old();
      if (flag) {
        //send2aws_old();
        send2aws();
      }
      else {
        connect2aws();
        //send2aws_old();
        send2aws();
      }
      cont = 0;
    }
    else {
      Serial.println("error");
    }
  }
}

void send2aws_old() {
  if (SD.exists("/flag")) {
    Serial.println("oi");
    String caminho = readFile(SD, "/flag");
    Serial.print("caminho: ");
    Serial.println(caminho);
    chamaRegistro(caminho);
  }
}

void chamaRegistro(String caminho)
{
  String linha;
  char caminho_aux[30];
  caminho.toCharArray(caminho_aux, 30);

  root = SD.open("/fronius");

  if (!root) {
    Serial.println("Failed to open file for appending");
    return;
  }

  registroGeral(root, linha);

  root.close();

  delay(500);
}

void registroGeral(File dir, String linha) {

  while (true) {

    File entry = dir.openNextFile();

    if (!entry)
      break;

    if (entry.available())
    {
      linha = entry.readStringUntil('\n');

      linha.toCharArray(payload, 512);

      unsigned long int timerInicio = millis();

      while (hornbill.publish(TOPIC_NAME, payload) != 0) {
        if (millis() - timerInicio >= 5000) {
          Serial.println("Publish failed");
          flag = false;
          //send2sd();
          break;
        }

        delay(1000);
      }

      Serial.print("Publish Message!");
    }

    if (entry.isDirectory()) {
      registroGeral(entry, linha);
    }
    entry.close();
  }
}

void send2sd() {
  String fileName;

  String dataHora = String(timestamp);
  String ano = dataHora.substring(0, 4);
  String mes = dataHora.substring(4, 6);
  String dia = dataHora.substring(6, 8);
  String hora = dataHora.substring(8, 12);

  fileName = ("/" + ano + "/" + mes + "/" + dia);

  char caminho[30];
  fileName.toCharArray(caminho, 30);

  Serial.print(caminho);
  Serial.println("#");

  if (!SD.exists(caminho)) {
    createDir(SD, "/fronius");
    fileName = ("/fronius/" + ano);
    fileName.toCharArray(caminho, 30);
    createDir(SD, caminho);
    fileName = ("/fronius/" + ano + "/" + mes);
    fileName.toCharArray(caminho, 30);
    createDir(SD, caminho);
    fileName = ("/fronius/" + ano + "/" + mes + "/" + dia);
    fileName.toCharArray(caminho, 30);
    createDir(SD, caminho);
  }

  fileName =  fileName + "/" + hora + ".txt";

  fileName.toCharArray(caminho, 30);

  writeFile(SD, caminho, payload);

  if (!SD.exists("flag")) {
    writeFile(SD, "/flag", caminho);
  }

  Serial.println("GRAVOU");
}

void createDir(fs::FS & fs, const char * path) {
  Serial.printf("Creating Dir: %s\n", path);
  if (fs.mkdir(path)) {
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

void removeDir(fs::FS & fs, const char * path) {
  Serial.printf("Removing Dir: %s\n", path);
  if (fs.rmdir(path)) {
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

String readFile(fs::FS & fs, const char * path) {
  String text_read = "";

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return "null";
  }

  Serial.print("Read from file: ");

  text_read = file.readStringUntil('\n');

  file.close();
  return text_read;
}

void writeFile(fs::FS & fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS & fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void renameFile(fs::FS & fs, const char * path1, const char * path2) {
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void deleteFile(fs::FS & fs, const char * path) {
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}
void send2aws() {

  Serial.println(payload);

  unsigned long int timerInicio = millis();

  while (hornbill.publish(TOPIC_NAME, payload) != 0) {
    if (millis() - timerInicio >= 5000) {
      Serial.println("Publish failed");
      flag = false;
      //send2sd();
      return;
    }

    delay(1000);
  }

  Serial.print("Publish Message!");
}

void connect2aws() {

  if (hornbill.connect(HOST_ADDRESS, CLIENT_ID) == 0) {
    Serial.println("Connected to AWS");
    flag = true;
    delay(1000);
  }
  else {
    Serial.println("AWS connection failed, Check the HOST Address");
    unsigned long int timerInicio = millis();

    while (true) {
      if (millis() - timerInicio >= 5000) { //espera receber a resposta do app por 5 segundos
        Serial.println("SAIU");
        break;
      }
    }
  }
}

void inverterRead() {
  char tipo;
  boolean flag_i = 0;
  String currentLine = "";
  int k = 0;

  Serial.println("New client.");

  while (cliente.connected()) {
    if (cliente.available()) {
      char c = cliente.read();
      //Serial.write(c);

      if (c == '&') {
        while ((c = cliente.read()) != '.') {
          timestamp[k] = c;
          k++;
        }
        timestamp[k] = '\0';
        tipo = cliente.read();
      }

      else if (c == '\n') {
        if (currentLine.length() == 0) {
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-type:text/html");
          cliente.println();
          break;
        } else {
          currentLine = "";
        }
      } else if (c != '\r') {
        currentLine += c;
      }
    }
  }

  if (tipo == '1' && !flag_i) {

    char json[1000];
    int i = 0;

    while (cliente.available()) {
      json[i] = cliente.read();
      i++;
    }

    json[i] = '\0';

    StaticJsonBuffer<735> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success()) {
      Serial.println("parseObject() failed");
      return;
    }

    /*int day_energy = root["Body"]["DAY_ENERGY"]["Values"]["1"];
      Serial.println("DAY_ENERGY");
      Serial.println(day_energy);*/

    P_AC = root["Body"]["PAC"]["Values"]["1"];
    //Serial.print("P_AC: ");
    //Serial.println(P_AC);

    /*int total_energy = root["Body"]["TOTAL_ENERGY"]["Values"]["1"];
      Serial.println("TOTAL_ENERGY");
      Serial.println(total_energy);

      int year_energy = root["Body"]["YEAR_ENERGY"]["Values"]["1"];
      Serial.println("YEAR_ENERGY");
      Serial.println(year_energy);*/

    cont++;
  }
  else if (tipo == '2') {

    if (cliente.available()) {
      if (cliente.find("p id=\"I_AC_CurrentA\"")) {
        //Serial.print("I_AC: ");
        String I_AC_s = cliente.readStringUntil('<');
        I_AC_s.remove(0, 1);
        I_AC = I_AC_s.toFloat();
        //Serial.println(I_AC);
      }
      else {
        flag_i = 1;
        cont = 0;
        return;
      }

      if (cliente.find("p id=\"I_AC_VoltageA\"")) {
        //Serial.print("V_AC: ");
        String V_AC_s = cliente.readStringUntil('<');
        V_AC_s.remove(0, 1);
        V_AC = V_AC_s.toFloat();
        //Serial.println(V_AC_s);
      }
      else {
        flag_i = 1;
        cont = 0;
        return;
      }

      if (cliente.find("p id=\"DCA\"")) {
        //Serial.print("I_DC: ");
        String I_DC_s = cliente.readStringUntil('<');
        I_DC_s.remove(0, 1);
        I_DC = I_DC_s.toFloat();
        //Serial.println(I_DC);
      }
      else {
        flag_i = 1;
        cont = 0;
        return;
      }

      if (cliente.find("p id=\"DCV\"")) {
        //Serial.print("V_DC: ");
        String V_DC_s = cliente.readStringUntil('<');
        V_DC_s.remove(0, 1);
        V_DC = V_DC_s.toFloat();
        //Serial.println(V_DC_s);
      }
      else {
        flag_i = 1;
        cont = 0;
        return;
      }
    }

    if (flag_i) {
      flag_i = 0;
      cont = 0;
    }
    cont++;
  }

  cliente.stop();
  Serial.println("cliente Disconnected.");
  //Serial.print("Timestamp");
  //Serial.print("Tipo");
  //Serial.println(tipo);
}
