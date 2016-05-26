#include "TheThingsUno.h"

// Set your app Credentials
const byte appEui[8] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x00, 0x01, 0xFC };
const byte appKey[16] = { 0x9B, 0x14, 0x3B, 0xE4, 0x78, 0x3E, 0xA2, 0xF7, 0xBE, 0xB5, 0x84, 0x95, 0xB9, 0xB5, 0xE9, 0x7D };

#define debugSerial Serial
#define loraSerial Serial1

int echoPin = 0x07;
int trigPin = 0x08;

TheThingsUno ttu;

void setup()
{
  debugSerial.begin(115200);
  loraSerial.begin(57600);

  delay(1000);
  ttu.init(loraSerial, debugSerial); //Initializing...
  ttu.reset();
  ttu.join(appEui, appKey);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  delay(1000);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  int data;
  data = (int)distance;
  byte buf[2];
  buf[0] = (data >> 8) & 0xff;
  buf[1] = data & 0xff;
  ttu.sendBytes(buf, 2);
  debugSerial.println(distance);
  debugSerial.println(data);
  delay(10000);
}
