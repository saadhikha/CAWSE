/*******************************************************************
* Original Code: http://www.electrodragon.com/w/File:Rfid-master.zip
*
* Version:  0.1
* Author:   Peremptor
********************************************************************/

// You will only need the additional RFID library copied into your
// library folder, see link above
#include <SPI.h>
#include <RFID.h>
#include <LiquidCrystal.h>

// Pins used to connect the display to the Arduino
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Left-over from original code, SS means SDA
#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN); 

// Left-over from original code, variables needed to read the ID of the tag
// Setup variables:
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;

void setup()
{ 
  // I deleted the "Serial.begin"-part, after all, I've got a display :)
  SPI.begin(); 
  rfid.init();

  // The usual display code, say how many figures a row can take
  // and how many lines the display has
  lcd.begin(16,2);             
  lcd.clear();      // should be clear *lol*            
  lcd.setCursor(0,0);    // set the cursor to figure 1 in row 1 (Computers start at null)      
  lcd.print("RFID bereit");   // in English: RFID is ready.
}

void loop()
{
    
    if (rfid.isCard()) 
    {
      if (rfid.readCardSerial()) 
        {
          // get the numbers out of the stream into our variables
          serNum0 = rfid.serNum[0];
          serNum1 = rfid.serNum[1];
          serNum2 = rfid.serNum[2];
          serNum3 = rfid.serNum[3];
          serNum4 = rfid.serNum[4];
         
          // that's the usual problem with stream, integer and strings,
          // maybe some day I understand why they can't be converted in
          // C++ languages. Until then, I use Visual Basic or print every
          // stupid number on its own...
          lcd.setCursor(0,1);  // set the cursor to figure 1 in row 2
          lcd.print(rfid.serNum[0]);
          lcd.print(rfid.serNum[1]);
          lcd.print(rfid.serNum[2]);
          lcd.print(rfid.serNum[3]);
          lcd.print(rfid.serNum[4]);
                                      // every number has to digits, so your display should show 10 nubmers
          delay(10000);    // wait 10 seconds (or whatever you want if you change it)
          // start from the beginning again
          lcd.clear();                  
          lcd.setCursor(0,0);          
          lcd.print("RFID bereit");                                     
        }
    }
    
    rfid.halt();  // close the stream
}
// Enjoy!
