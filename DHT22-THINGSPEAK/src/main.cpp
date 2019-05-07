#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

#define DHTPIN 4
#define DHTTYPE DHT22

const char *ssid = "Famillia";
const char *password = "khaledsa14";

DHT dht(DHTPIN, DHTTYPE);

unsigned long myChannelNumber = 775988;
const char *myWriteApiKey = "5QP41GS96CC21AIX";
const char *myReadApiKey = "UZ5CDSWN13R9NH47";

const char *server = "api.thingspeak.com";

WiFiClient client;

void setup()
{

  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();

  ThingSpeak.begin(client);
  WiFi.begin(ssid, password);

  Serial.println("Connecting.....");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Waiting to connect to WiFi.....");
  }
  Serial.println("WiFi is connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("failed to read sensor");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(f);
  Serial.print("F\t");
  Serial.print(t);
  Serial.print("C\t");
  Serial.print("Heat index: ");
  Serial.print(hif);
  Serial.print("F\t");
  Serial.print(hic);
  Serial.println("C\t");

  if (client.connect(server, 80))
  {
    ThingSpeak.setField(1, t);
    ThingSpeak.setField(2, h);
    ThingSpeak.writeFields(myChannelNumber, myWriteApiKey);
    delay(20000);
  }
}