#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#define DHTPIN D6  
#define DHTTYPE DHT11
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

char auth[] = "TjVUgaTuO_7-UYOMigPBcgZwor08lUzg";
char ssid[] = "PL floor2_2.4G";
char pass[] = "1234562552";

BLYNK_CONNECTED() {
    Blynk.syncAll();
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  pinMode(D0, INPUT);
  pinMode(D4, OUTPUT);
  lcd.begin();
  lcd.backlight();
}
void loop()
{
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
  }
  Serial.print("Humidity : ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.print("*c\t");
  Serial.print(f);
  Serial.print("% *F\t\n");
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print("Celsius : ");
  lcd.print(t);
  Blynk.run();
  Blynk.virtualWrite(10, t);
  Blynk.virtualWrite(11, h); 
}
