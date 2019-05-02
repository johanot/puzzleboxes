#include <Key.h>
#include <Keypad.h>

/*
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 This sketch prints "Hello World!" to the LCD and uses the
 display() and noDisplay() functions to turn on and off
 the display.
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi
 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay
*/

// include the library code:
#include <LiquidCrystal.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {6, 1, 0}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int count = 0;
String code;
String codes[5][1] = {
  {"1111"},
  {"1111"} 
};

char buf[16 ];
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  
  sprintf(buf, "Indtast kode %d", count + 1);
  lcd.print(buf);
  lcd.setCursor(0, 1);
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey)
  {   
    if (customKey == '#')
    {
      code = "";
      lcd.clear();
      sprintf(buf, "Indtast kode %d", count + 1);
      lcd.print(buf);
      lcd.setCursor(0, 1);
    }
    else
    {
      lcd.print(customKey);
      code += customKey;
    }
    
    if (code.equals(codes[count][0]))
    {
      code = "";
      lcd.clear();
      count++;
      lcd.setCursor(0, 0);
      if (count < 2)
        sprintf(buf, "Indtast kode %d", count + 1);
      else
        sprintf(buf, "Du vandt!");
      lcd.print(buf);
      lcd.setCursor(0, 1);
    }
  }
}
