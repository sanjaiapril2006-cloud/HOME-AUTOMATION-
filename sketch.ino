#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define LDR_PIN A0
#define PIR_PIN 3

#define LIGHT_LED 8
#define SECURITY_LED 10

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  pinMode(LIGHT_LED, OUTPUT);
  pinMode(SECURITY_LED, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  dht.begin();

  lcd.init();
  lcd.backlight();
}

void loop() {

  int lightValue = analogRead(LDR_PIN);
  float temp = dht.readTemperature();
  int motion = digitalRead(PIR_PIN);

  // Automatic Light Control
  if (lightValue < 500) {
    digitalWrite(LIGHT_LED, HIGH);
  } else {
    digitalWrite(LIGHT_LED, LOW);
  }

  // Security System
  if (motion == HIGH) {
    digitalWrite(SECURITY_LED, HIGH);
  } else {
    digitalWrite(SECURITY_LED, LOW);
  }

  // LCD Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Light:");
  lcd.print(lightValue);

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C  Light: ");
  Serial.println(lightValue);

  delay(1000);
}
