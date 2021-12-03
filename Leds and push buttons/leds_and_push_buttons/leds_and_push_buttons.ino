#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(11, 8, 10, 9, 7, 6);
const int ledpin1 = 13;
const int ledpin2 = 12;
const int buttonA = 4;
const int buttonB = 3;

int state_buttonA = 0;
int state_buttonB = 0;

void setup() 
{
    Serial.begin(9600);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // put your setup code here, to run once: define arduino input and output
    pinMode(ledpin1, OUTPUT); //output pin
    pinMode(ledpin2, OUTPUT); //output pin
    pinMode(buzz, OUTPUT); // arduino output pin
    pinMode(buttonA, INPUT); //button pin is input
    pinMode(buttonB, INPUT); //button pin is input
}

void loop() {
  // put your main code here, to run repeatedly:

    state_buttonA = digitalRead(buttonA); //define state of A
    state_buttonB = digitalRead(buttonB);

    if(state_buttonA && !state_buttonB) {
        tone = 100;
        digitalWrite(ledpino1, HIGH);
    }
    if(state_buttonB && !state_buttonA) {
        tone = 200;
        digitalWrite(ledpino2, HIGH);
    }
   
    if(tone > 0) { //as long as Tone is greater than zero do what is described below:
        digitalWrite(sound, HIGH); // Turn on buzzer
        delayMicroseconds(tone); // Wait the time proportional to the wavelength of the musical note in milliseconds
        digitalWrite(sound, LOW); // Turn off buzzer
        delayMicroseconds(tone); // Wait the time proportional to the wavelength of the musical note in milliseconds
        tone = 0; // Resets the tone to zero, to exit the while loop and not play the sound constantly
        digitalWrite(ledpin1, LOW);
        digitalWrite(ledpin2, LOW);
    }

}// void loop
