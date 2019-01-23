// Libraries
#include <string.h>
#include <DHT.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include "RF24.h"
#include <ArduinoJson.h>

RTC_DS1307 RTC;

// Input pins

// Entradas Digitais - PWM
#define DUST_SENSOR_DIGITAL_PIN_PM10  5
#define DUST_SENSOR_DIGITAL_PIN_PM25  6
// Entradas Digitais
#define DHTPIN                        8
#define ANEMPIN                       2
#define PLUVPIN                       9

// Entradas Analógicas
byte UVPIN = A2;
byte VENTDIRPIN = A0;
byte PIRPIN = A3;

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int CS_SDcard = 4;

// Variables for RADIO
const uint64_t addr = 0xF0F0F0F0E1LL;
//RF24 radio(23, 15);                       // (CE_Pin, CSN_Pin)
char timestamp[15];


// Variables for DUST SENSOR
unsigned long duration;
unsigned long starttime;
unsigned long endtime;

// 
byte Anem_counter;

// Constantes para o Pluviometro:
const int Pluv_REED = 10;                              // The reed switch outputs to digital pin 10

// Variáveis para o Pluviometro:
int Pluv_val = 0;                                      // Current value of reed switch
int Pluv_old_val = 0;                                  // Old value of reed switch
int Pluv_REEDCOUNT = 0;                                // This is the variable that hold the count of switching
// Variables for TIME
byte DAY = 22;
byte MONTH = 01;
int  YEAR  = 2019;
byte HOUR = 15;
byte MINUTE = 20;
byte SECOND = 00;

byte sd_flag;

int counter = 0;

void setup() {
  
  
  Serial.begin(115200);
  
  // Inicialização sensor de temperatura
  dht.begin();                                         // Initialize the DHT sensor

  // Inicialização cartão microSD
  // (https://forum.arduino.cc/index.php?topic=507086.0)
  // (http://www.ktudu.com/?p=21619)
  // (https://www.dobitaobyte.com.br/ler-e-escrever-no-sd-card-com-arduino/)

  

  // Inicialização RTC
  Wire.begin();
  RTC.begin();

  // Check to see if the RTC is keeping time.  If it is, load the time from your computer.
  if (RTC.isrunning()) {
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  DateTime now = RTC.now();

  pinMode(UVPIN, INPUT);

  // Inicialização Anemômetro
  pinMode(ANEMPIN, INPUT);
  digitalWrite(ANEMPIN, HIGH);

  // Inicialização sensor de poeira
  pinMode(DUST_SENSOR_DIGITAL_PIN_PM10, INPUT); // Pin_3 PM1.0
  pinMode(DUST_SENSOR_DIGITAL_PIN_PM25, INPUT); // Pin_6 PM2.5

  // Inicializacao Pluviometro
  pinMode (PLUVPIN, INPUT_PULLUP);
  digitalWrite(PLUVPIN ,HIGH);

/*
  // Inicialização do Rádio
  radio.begin();
  radio.setChannel(28);
  radio.setPayloadSize(32);
  radio.setDataRate(RF24_1MBPS);
*/
  // Wait 60 seconds for DSM501 to warm up
  for (int i = 1; i <= 15; i++)
  {
    delay(1000);                                            // 1s
  }
  starttime = millis();
  //initialize_SD();
  //Serial.println("Start reading");
}

void loop() {
  // Imprime a data no cartão micro SD e na Serial
  print_Date();
  // Data para enviar os dados na transmissao
  sprintf(timestamp, "%d%d%d%d%d%d*", YEAR, MONTH, DAY, HOUR, MINUTE, SECOND);
/*
  // Imprime dados via serial
  Serial.println("Teste");
  Serial.println(dht.readTemperature());
  Serial.println(dht.readHumidity());
  Serial.println(get_UV());
  Serial.println(get_SpeedWind());
  Serial.println(get_DirVento());
  Serial.println(get_PluvCalc());
  Serial.println(get_PM2());
  Serial.println(get_PM1());
  Serial.println(get_piranometerRead());
  Serial.println("Finalizado");
*/  
  //Imprime os dados no cartão microSD E Envia as variáveis via rádio
  //send2SD("teste");
  send_data();

}

// =================================================
// Funções do sensor UV
// =================================================
String get_UV()
{
  String UV_index = "0";
  byte valor_sensor = analogRead(UVPIN);
  //Calcula tensao em milivolts
  byte tensao = (valor_sensor * (5.0 / 1023.0)) * 1000;
  //Compara com valores tabela UV_Index
  if (tensao > 0 && tensao < 50)
  {
    UV_index = "0";
  }
  else if (tensao > 50 && tensao <= 227)
  {
    UV_index = "0";
  }
  else if (tensao > 227 && tensao <= 318)
  {
    UV_index = "1";
  }
  else if (tensao > 318 && tensao <= 408)
  {
    UV_index = "2";
  }
  else if (tensao > 408 && tensao <= 503)
  {
    UV_index = "3";
  }
  else if (tensao > 503 && tensao <= 606)
  {
    UV_index = "4";
  }
  else if (tensao > 606 && tensao <= 696)
  {
    UV_index = "5";
  }
  else if (tensao > 696 && tensao <= 795)
  {
    UV_index = "6";
  }
  else if (tensao > 795 && tensao <= 881)
  {
    UV_index = "7";
  }
  else if (tensao > 881 && tensao <= 976)
  {
    UV_index = "8";
  }
  else if (tensao > 976 && tensao <= 1079)
  {
    UV_index = "9";
  }
  else if (tensao > 1079 && tensao <= 1170)
  {
    UV_index = "10";
  }
  else if (tensao > 1170)
  {
    UV_index = "11";
  }

  return UV_index;
}

// =================================================
// Funções do anemômetro
// =================================================
void windvelocity() {
  Anem_counter = 0;


  attachInterrupt(0, addcount, RISING);
  unsigned long millis();
  long startTime = millis();
  while (millis() < startTime + 5000) {
  }
}



float get_SpeedWind() {
  windvelocity();
  float Anem_RPM = ((Anem_counter) * 60) / (5000 / 1000); // Calculate revolutions per minute (RPM)
  float speedwind = (((4 * 3.141592 * 147 * Anem_RPM) / 60) / 1000) * 3.6; // Calculate wind speed on km/h
  return speedwind;
}

void addcount() {
  Anem_counter++;
}

// =================================================
// Função da Direção do Vento
// =================================================


int get_DirVento() {
  float Dir_Vento_valor = analogRead(VENTDIRPIN);
  Dir_Vento_valor = Dir_Vento_valor * (5.0 / 1023.0);


  if (Dir_Vento_valor <= 0.27) {
   return 315;
  }
  else if (Dir_Vento_valor <= 0.32) {
   return 270;
  }
  else if (Dir_Vento_valor <= 0.38) {
   return 225;
  }
  else if (Dir_Vento_valor <= 0.45) {
   return 180;
  }
  else if (Dir_Vento_valor <= 0.57) {
   return 135;
  }
  else if (Dir_Vento_valor <= 0.75) {
   return 90;
  }
  else if (Dir_Vento_valor <= 1.25) {
   return 45;
  }
  else {
   return 0;
  }
}

// =================================================
// Funções do Pluviometro
// =================================================
float get_PluvCalc() {
  unsigned long timer = millis();
  unsigned long millis();
  long startTime = millis();
  while (millis() < startTime + 5000) {
  // ler o estado do switch pelo pino de entrada:
  int Pluv_val = digitalRead(PLUVPIN);                      //Read the status of the Reed swtich

  if ((Pluv_val == LOW) && (Pluv_old_val == HIGH)) {      //Check to see if the status has changed
    //delay(10);                                          // Delay put in to deal with any "bouncing" in the switch.
    Pluv_REEDCOUNT = Pluv_REEDCOUNT + 1;                //Add 1 to the count of bucket tips
    Pluv_old_val = Pluv_val;                            //Make the old value equal to the current value
  }
  else {
    Pluv_old_val = Pluv_val;                           //If the status hasn't changed then do nothing
  }
  }
  return Pluv_REEDCOUNT * 0.25;
}

// =================================================
// Funções do piranometro
// =================================================

int get_piranometerRead() {
  int piranometer_volt = analogRead(PIRPIN);
  int piranometer_read = piranometer_volt * (1600 / 900.24);
  return piranometer_read;
}

// =================================================
// Funções do sensor de particulado
// =================================================
long get_PM1()
{
  return ((getPM(DUST_SENSOR_DIGITAL_PIN_PM10) * 0.0283168 / 100) *  (0.08205 * (dht.readTemperature() + 273) / 0.01)) / 1000;
}

long get_PM2()
{
  return (((getPM(DUST_SENSOR_DIGITAL_PIN_PM25) * 0.0283168) / 100) *  ((0.08205 * (dht.readTemperature() + 273)) / 0.01)) / 1000;
}

long getPM(int DUST_SENSOR_DIGITAL_PIN)
{
  unsigned long sampletime_ms = 30000;
  unsigned long lowpulseoccupancy = 0;
  float ratio = 0;
  starttime = millis();

  while (1) {
    duration = pulseIn(DUST_SENSOR_DIGITAL_PIN, LOW);
    lowpulseoccupancy += duration;
    endtime = millis();

    if ((endtime - starttime) > sampletime_ms)
    {
      ratio = (lowpulseoccupancy - endtime + starttime) / (sampletime_ms * 10.0); // Integer percentage 0 - 100%
      //ratio = lowpulseoccupancy / (sampletime_ms * 10.0);
      long concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // Datasheet Curve [pcs/283ml]
      // concentration[pcs/m³] = concentration[pcs/283ml] * 283[ml] * 10^6[ml] / 1[m³]
      // concentration = concentration * 283.1685 * 1000000; // In [pcs/283ml]?
      if (concentration < 0)
      {
        concentration = 0.0;
      }
      lowpulseoccupancy = 0;
      return (concentration);
    }
  }
}
// =================================================
// Funções cartão microSD
// =================================================
void print_Date()
{
  DateTime now = RTC.now();
  DAY    = (now.day(), DEC);
  MONTH  = (now.month(), DEC);
  YEAR   = (now.year(), DEC);
  HOUR   = (now.hour(), DEC);
  MINUTE = (now.minute(), DEC);
  SECOND = (now.second(), DEC);
}

void send2SD(char payload[])
{
  File file_test;  
  String fileName;
 
  //fileName = ("/" + String(YEAR) + "/" + String(MONTH) + "/" + String(DAY));
  /*
  char caminho[30];
  fileName.toCharArray(caminho, 30);
  
  if (!SD.exists(caminho))
    SD.mkdir(caminho);
  
  fileName =  fileName + "/" + HOUR + MINUTE + ".txt";
 
  fileName.toCharArray(caminho, 30);
 */ 
  
  file_test = SD.open("sujidade.txt", FILE_WRITE);

  file_test.write(payload);

  delay(1000);

  file_test.close();

  delay(100);
  
}

void initialize_SD() {
  if (SD.begin(CS_SDcard))  {
    Serial.println("SD Card Okay!");
    sd_flag = 1;
  }
  else  {
    Serial.println("SD Card Problem!");
    sd_flag = 0;
  }
}

// =================================================
// Funções Rádio
// =================================================
void send_data()
{
  char payload[512];
  int cont = 0;
  StaticJsonBuffer<512> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();
  String  uv = get_UV();
  float   ws   = get_SpeedWind();
  int   wd   = get_DirVento();
  float pluv = get_PluvCalc();
  long int pm2  = get_PM2;
  long int pm1  = get_PM1;
  float igh  = get_piranometerRead();  
  
  
  root["tipo"] = "sujidade";
  root["timestamp"] = counter;
  root["temp"] = temp;
  root["hum"] = hum;
  root["uv"] = uv;
  root["ws_kmh"] = ws;
  root["wind_dir"] = wd;
  root["pluv"] = pluv;
  root["pm25"] = pm2;
  root["pm10"] = pm1;
  root["igh"] = igh;
  counter ++;
  
  root.prettyPrintTo(Serial);
  //root.printTo(payload);
  delay(300);
  //send2SD(payload);

  //  while (establish_connection() != 1 || cont < 5) { // Tenta inicializar a conexao 5 vezes
  //    cont++;
  //  }

  //if (cont == 5)  {
  /* Se cont for igual a 5, nao conseguiu inicializar a conexao,
    entao, deve-se armazenar a leitura no cartao sd e enviar na proxima vez
    e tambem retornar a funcao para que os passos seguintes nao sejam executados */
  //}

  //cont = 0;
/*
  while (send2rtu(payload) != 1 || cont < 5) { // Tenta enviar 5 vezes
    cont++;
  }
*/
  //if (cont == 5)  {
  /* Se cont for igual a 5, nao conseguiu enviar, entao, deve-se armazenar a
    leitura no cartao sd e enviar na proxima vez e tambem retornar a funcao para
    que os passos seguintes nao sejam executados */
  //}

  cont = 0;

  //  while (close_connection() != 1 || cont < 5) { // Tenta finalizar a conexao 5 vezes
  //    cont++;
  //  }

  /* Caso a conexao nao seja encerrada, a RTU tem um timer para encerrar sozinha */
}
/*
boolean establish_connection() {
  char message[] = "#s";
  int i;

  radio.write(message, strlen(message));

  return ack_check('s');
}

boolean close_connection() {
  char message[] = "#f";
  int i;

  radio.write(message, strlen(message));

  return ack_check('f');
}

boolean send2rtu(char payload[]) {
  char msg[33];
  int j = 0;
  int k = 0;

  while (payload[k] != '\0') {
    if (j == 32) {
      msg[j] = '\0';
      radio.write(msg, strlen(msg));
      memset(msg, 0, 33);
      j = 0;
    }

    msg[j] = payload[k];

    k++;
    j++;
  }
  radio.write(msg, strlen(msg));

  radio.write("*$", 2);

  //return ack_check('e');
}

boolean ack_check(char id) {
  radio.openReadingPipe(1, addr);
  radio.startListening();

  unsigned long int timerInit = millis();

  while (!radio.available()) {
    if (millis() - timerInit >= 2000) {
      return 0; // Time out
    }
  }

  char ack[2];
  radio.read(ack, 2);

  radio.stopListening();
  radio.closeReadingPipe(1);

  if (ack[0] == id && ack[1] == '#')
    return 1;
  else
    return 0;
}*/
