//Prateek
//www.prateeks.in

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int lock = D0;
int red = D8;
int yellow = 10;

char auth[] = "E8tWL79acBi3SY0NS2HAJB185HjcMLd4";   //Blynk Authentication Token -- sent via Email from Blynk

char ssid[] = "justdoelectronics";   //Enter WiFi Name
char pass[] = "123456789";   //Enter Wifi Password

String page = "";
char input[12];
int count = 0;
int a;
double total = 0;
int count_prod = 0;

SimpleTimer timer;
int fflag = 0;
int jflag = 0;
WidgetTerminal terminal(V2);

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Welcome To");
  lcd.setCursor(0, 1);
  lcd.print("JustDoElectronic");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Plz Scan Card");

  Blynk.begin(auth, ssid, pass);
  pinMode(lock, OUTPUT);
  digitalWrite(lock, LOW);
  pinMode(red, OUTPUT);
  digitalWrite(red, LOW);
    pinMode(yellow, OUTPUT);
  digitalWrite(yellow, LOW);
  timer.setInterval(1000L, iot_rfid);
}

void loop() {

  timer.run(); // Initiates SimpleTimer
  Blynk.run();
  iot_rfid();

}

void iot_rfid()
{
  if (Serial.available())
  {
    count = 0;
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12)
    {
      if ((strncmp(input, "03007BFA20A2", 12) == 0) && (fflag == 1))
      {
        Serial.println("Prateek");   //Enter User2 Name
        Blynk.virtualWrite(V2, "Prateek" );   //Enter User2 Name
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Prateek Welcome");
        digitalWrite(lock, HIGH);
        digitalWrite(yellow, HIGH);
        delay(3000);
        digitalWrite(lock, LOW);
        digitalWrite(yellow, LOW);

      }
      else if ((strncmp(input, "03007C8531CB", 12) == 0) && (jflag == 1))
      {
        Serial.println("Aditya");   //Enter User3 Name
        Blynk.virtualWrite(V2, "Aditya" );   //Enter User3 Name
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Aditya Welcome");
        digitalWrite(lock, HIGH);
        digitalWrite(yellow, HIGH);
        delay(3000);
        digitalWrite(lock, LOW);
        digitalWrite(yellow, LOW);

      }
      else
        Serial.println("Unregistered User");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Plz Scan Card");
      digitalWrite(red, HIGH);
      delay(3000);
      digitalWrite(red, LOW);

    }
  }
}

// in Blynk app writes values to the Virtual Pin 3
BLYNK_WRITE(V3)
{
  fflag = param.asInt();

}

BLYNK_WRITE(V5)
{
  jflag = param.asInt();

}
