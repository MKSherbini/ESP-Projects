#include <Arduino.h>
#include <ESP8266WiFi.h>

const char *ssid = "Famillia";
const char *password = "khaledsa14";

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
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
}