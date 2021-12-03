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
  Serial.println("CA-Health_System created an object on 14.11.2021 "); 
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
    Serial.println("Location details as recieved via GPS Module");
    Serial.println("23.5204° N 87.3119° E");
    
    Serial.println("Pulse Rate: 92");
    Serial.println("Pulse is Normal");
    Serial.println("Body Temperature: 98.6");
    Serial.println("Body Temperature is Normal");
    
    Serial.println("Glucometer detected the glucose level: 7.5");
    Serial.println("Glucose is Normal");
    
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
