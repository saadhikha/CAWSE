#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#define ESP8266_BAUD 9600

char auth[] = "6bae2d0e7bfa4b6096feeaffa2030e4f";
char ssid[] = "Rajashri"; //Wifi name to my wifi network

char pass[] = "RajashriMahato";  //Password of my wifi.

SoftwareSerial EspSerial(2, 3); // RX, TX
WidgetLCD lcd(V0);

ESP8266 wifi(&EspSerial);

void setup()
{

  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  Blynk.begin(auth, wifi, ssid, pass);
   lcd.clear();
 lcd.print(1, 1, "IoT");
}

void loop()
{
  Blynk.run();
}
