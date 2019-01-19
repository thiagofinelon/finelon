/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file aws_iot_certifcates.c
 * @brief File to store the AWS certificates in the form of arrays
 */

#ifdef __cplusplus
extern "C" {
#endif

const char aws_root_ca_pem[] = {"-----BEGIN CERTIFICATE-----\n\
MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\n\
yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\n\
ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\n\
U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\n\
ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\n\
aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\n\
MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\n\
ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\n\
biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\n\
U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\n\
aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\n\
nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\n\
t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\n\
SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\n\
BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\n\
rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\n\
NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\n\
BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\n\
BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\n\
aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\n\
MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\n\
p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\n\
5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\n\
WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\n\
4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\n\
hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\n\
-----END CERTIFICATE-----\n"};

const char certificate_pem_crt[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDWTCCAkGgAwIBAgIUG4bQqEBnAy3oU2h+Il3AWNsw3jEwDQYJKoZIhvcNAQEL\n\
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n\
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE4MDkxNTIyNDQw\n\
MFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n\
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJOd+s06LLQn3wNq/jCr\n\
adVxQChzu8scJt+syR6pcahsUca3A8Ag0ITAJi7C84LbDAtPvI3gl3MiFRrG7gof\n\
TKHks/goaLRaFEsNh7xP4uOhc8qO7FAYa2sTQN4WR7DG899aH0cDg9nzxA8euXm3\n\
z0VNSR5Px7NO74ZFU+XpggLdhFis3xryOG1ZwIgdxs8zo5kjewP/rOlMNivA4sYW\n\
wPM6uZmbKmXqmJwuZX6D3KrQj6LL5nF2z5cE3RzbQ97oDzKEKwZqRlA3civAGiRs\n\
2yOn0kpEv4OcokVNgKiM7wgmQKEn38SVXHR6SUXghKRXsFaUCEGr8HxZ/YQGyygl\n\
qkMCAwEAAaNgMF4wHwYDVR0jBBgwFoAUu2iZqsaRB46JF5yuECg2uXGmXBkwHQYD\n\
VR0OBBYEFOxAESZLRmIyGCu7JaZYuQIXbypUMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n\
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQB6IsFgnGaY5Xd4aOVb6mMUwP56\n\
Ga0Sy5zQV6G2U/3ToJRyzo2DIrITgEbHrk+pSkDLePHNyiDHXmbs85IsWkbWzRTI\n\
u/NQqL6w4sjFj1nHJOOAd0CK+iTPpu8mMQqrWQCeGIqWxspC+m8YnuyieZOS634I\n\
+LYpIuSsdfxA+w3xdmRY6lRbn6zG+0Z4y7jujpVHp+90A+IMrW6AlKpKEmf/Seuv\n\
yn2m2hsjJqIal5+msNvcCpfhKzCJfo7l5ja3uS8I7hdVAutNNZnLfxJ5yuf8HbhG\n\
ujNY2Zi4NUktpbLdlwKY3Wcuoylk8X3jlx9XEv2QuXCi2SZWKAJqIzwETK25\n\
-----END CERTIFICATE-----\n"};

const char private_pem_key[] = {"-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEAk536zTostCffA2r+MKtp1XFAKHO7yxwm36zJHqlxqGxRxrcD\n\
wCDQhMAmLsLzgtsMC0+8jeCXcyIVGsbuCh9MoeSz+ChotFoUSw2HvE/i46Fzyo7s\n\
UBhraxNA3hZHsMbz31ofRwOD2fPEDx65ebfPRU1JHk/Hs07vhkVT5emCAt2EWKzf\n\
GvI4bVnAiB3GzzOjmSN7A/+s6Uw2K8DixhbA8zq5mZsqZeqYnC5lfoPcqtCPosvm\n\
cXbPlwTdHNtD3ugPMoQrBmpGUDdyK8AaJGzbI6fSSkS/g5yiRU2AqIzvCCZAoSff\n\
xJVcdHpJReCEpFewVpQIQavwfFn9hAbLKCWqQwIDAQABAoIBAFp4ikvZiahof0/y\n\
9RMTG2wLWszwEXpsKI8RsLmwE86rhHsLk6re8a1KrpweM2xRn9IW7nLt4SRZESI2\n\
JZHimO7n4j0HVxSh2KofAr+xHldwjizo54A3Vy5qwGjcstdvN+v9qgm158tekRzL\n\
MdWdh9TrhxKixrvodviN6NuR/3KNLtSgY8twiojSn7BshUbUa6hKcwxnGB6ELDyj\n\
uAwPYba1liwRllbEywyMBKJRs0Ycn3+vswZgO7Oj6vbtUwd9QM4tCKDfObjPpZEs\n\
gfiIHw98j/J0N5BX57tKtOj+G6HAqOXLoPfn0nW1UKaY/eEcW7psqNRh1gI1MUMq\n\
gwS3Z5ECgYEAws27lQ3v4jzpoy5EQhSYCQCdxjsIc5pvPjRBdk43/tpnXeVLHtnG\n\
54ugENdf72An52lHMGpsKIEc/OoFA47UvPnKJ6fwmG8lqKe1xFGtPl8MEGi0Stre\n\
3hoDgA6LdZo3x4OEVAeMfRhRopp7pycbbInJu82dqZUg+NC+mRKUv+cCgYEAwf13\n\
qp+54eBAVdOiVpNplMdQ8z2JexKk3SRHUcBxaj5OehH0U76mIkafU+lSNtf2CNU9\n\
+Q0gb92uRI0VpJBEoAVRjuzFqTAhikjxwGUl+WQTuVJCpbTXdsYZjKFhPUOVdLpV\n\
6UENI/SDeMsSpLNBj/I2lwrwXqndABvspRFoZ0UCgYA4z9k6EjN4jn0w6uhbQThJ\n\
v9VDn6nKVSrGQGUrBIrOF5H3z0xGNgsNMio/XyCKZkec9JYfZ5odgfIbTICj1f7z\n\
EgJD6HWBb0DTW/3lwFA/FWcmTfLutcAzk/CbYyKG7LABzrhD7WOqg/Ii8tzHFd+o\n\
mtKro76sW2KfTfmYGNQq1wKBgQCfxPpB9LtLZT6XcW5Kj65tcpshOpV4X6qY18BF\n\
fJHsRtSrhQ4Nyv9ZS4D9wzSLJuLj83zPGhiVCab1np0spAVhJgA+DpPc/F8jXWB+\n\
bNARznLQNwfdIkwy7oUsZd2Ib5kwQidvrLv92OxPGDGKpHhi7cI4NDI0RQJXjKgi\n\
a2vpYQKBgGqLyC8LuCo06DwrUq9JzGdT7Axea/bWDBcbWb0RjY326GAG2r155B8W\n\
n7wg2mh1q0Hk6sLCkwEfAZpmW6eAiXKsD8rvGc2CJo05El35Y3+53qb1VRmmHwcU\n\
UCr1cZiXuTi8ZJXDpx5UT9WWTrnmGEg+OWolIRCnp0h8gW6lAeCp\n\
-----END RSA PRIVATE KEY-----\n"};


#ifdef __cplusplus
}
#endif
