#include <Arduino.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  float f=dht.readTemperature(true);

  if(isnan(h)||isnan(t)||isnan(f)){
    Serial.println("failed to read sensor");
    return;
  }

  float hif=dht.computeHeatIndex(f,h);
  float hic=dht.computeHeatIndex(t,h,false);

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
}