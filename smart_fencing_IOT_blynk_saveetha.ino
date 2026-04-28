#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3JzUe0b89"
#define BLYNK_TEMPLATE_NAME "IOT Based Smart Fence"
#define BLYNK_AUTH_TOKEN "QDFFmxfSgQ5AnC2X_G3hdo1JY3Mu8ddO"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char ssid[] = "CRKHOME";
char pass[] = "himalayan";

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pinValue, fencing_supply;

#define touch_pin D6
#define buzzer D5
#define led_pin D0

BLYNK_WRITE(V1)
{
  pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("Switch value is: ");
  Serial.println(pinValue);
}


void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(touch_pin, INPUT);
  Serial.begin(115200);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Smart Electric");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Fencing Monitoring");
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  delay(1000);
}

void loop()
{
  Blynk.run();
  if (pinValue == 0)
  {
    digitalWrite(led_pin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Electric Fencing:");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("OFF & Safe");
    delay(500);
  }
  else
  {
    digitalWrite(led_pin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Electric Fencing:");
    digitalWrite(buzzer, HIGH);
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("ON & Danger");
    digitalWrite(buzzer, LOW);
    delay(500);
  }
  if (digitalRead(touch_pin) == HIGH)
  {
    fencing_supply = 1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fencing wire");
    lcd.setCursor(0, 1);
    lcd.print("Touched");
    digitalWrite(buzzer, HIGH);
    Blynk.virtualWrite(V0, fencing_supply);
    Blynk.logEvent("fence_touch");
    delay(500);
  }
  else
  {
    fencing_supply = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fencing wire");
    lcd.setCursor(0, 1);
    lcd.print("OK");
    Blynk.virtualWrite(V0, fencing_supply);
    delay(500);
  }
}
