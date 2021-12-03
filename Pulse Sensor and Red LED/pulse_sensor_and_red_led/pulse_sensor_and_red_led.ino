#define USE_ARDUINO_INTERRUPTS true 
#include <PulseSensorPlayground.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
 

const int PulseWire = 0; 
const int LED7 = 7; 
int Threshold = 550; 
const int buzzer = 9;

PulseSensorPlayground pulseSensor; 
void setup() 
{
  pinMode(A0, INPUT);
  pinMode(LED7, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LED7, OUTPUT); 
  Serial.begin(9600); 
  lcd.begin(16,2);
 
  
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED7); 
  pulseSensor.setThreshold(Threshold);
 
  
  if (pulseSensor.begin()) 
  {
  Serial.println("We created a UltrasonicSensor Object !"); 
  }
}
 
void loop() 
{
  int myBPM = pulseSensor.getBeatsPerMinute(); 
  
  if (pulseSensor.sawStartOfBeat()) 
  { 
  Serial.print("BPM: "); 
  Serial.println(myBPM); 
  lcd.setCursor(0,2);
  lcd.print("HeartBeat Rate !"); 
  Serial.println("HeartBeat Rate !");
  lcd.setCursor(5,3);
  lcd.print("BPM: "); 
  lcd.print(myBPM);
  if(myBPM>=60 && myBPM<=100)
  {
  Serial.println(" Pulse Rate Normal ");
  }
}
delay(10); 
if (myBPM <= 59) 
  {
    digitalWrite(7, HIGH);
    delay(3000);
    lcd.setCursor(0,0);
    Serial.println("Pulse Rate noted !");
    Serial.println("Pulse is very LOW !");
    tone(buzzer,10);
    
    delay(3000);
  }
  else
  {
    digitalWrite(7, LOW);
    noTone(buzzer);
    
  }
if (myBPM > 100) 
  {
    digitalWrite(7, HIGH);
    delay(3000);
    lcd.setCursor(0,0);
    Serial.println("Pulse Rate noted");
    Serial.println("Pulse is very HIGH !");
    tone(buzzer,10);
    delay(3000);
  }
  else
  {
    digitalWrite(7, LOW);
    noTone(buzzer);
  }
}
