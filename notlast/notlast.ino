/*
  LiquidCrystal Library - display() and noDisplay()

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

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int bars = 16;
bool pushed = false;
bool playersTurn = true;
bool playerPlaying = false;
bool replay = false;
int countRemoval = 0;
int computerGoal = 13;
int lastRead;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

unsigned long playersLastClick;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(10, OUTPUT);
  analogWrite(10, 110);
  lcd.display();
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  Serial.begin(9600);
  String text = getBars(bars);

  lcd.print(text);
  lcd.setCursor(0, 1);
  lcd.print(text);

  randomSeed(analogRead(0));
}

void loop() 
{
  if (playersTurn)
  {   
    int reading = digitalRead(7);
  
    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:
  
    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) 
    {
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) 
    {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:
  
      // if the button state has changed:
      if (reading != buttonState) 
      {
        buttonState = reading;
  
        // only toggle the LED if the new button state is HIGH
        if (buttonState == LOW) 
        {
          if (replay)
          {
            replay = false;
            bars = 16;
            countRemoval = 0;
            computerGoal = 13;
            String text = getBars(bars);
            writeToScreen(text, text);
          }
          else if (countRemoval < 3)
          {
            playerPlaying = true;
            playersLastClick = millis();
            
            bars--;
            countRemoval++;
            
            String text = getBars(bars);
            
            if (bars > 0)
            {
              writeToScreen(text, text);
            }
            else
            {
              writeToScreen("You loose!", "Play again...");
              playerPlaying = false;
            
              replay = true;
            }
            Serial.println(bars);
          }
        }
      }
    }
  
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;

    if (playerPlaying && millis() - playersLastClick > 1000)
    {
      playersTurn = false; 
      playerPlaying = false;
      countRemoval = 0; 
    }
  }
  else
  {  
     if (bars > computerGoal)
     {
       bars = computerGoal;
     }
     else if (bars == computerGoal)
     {
       int rd = random(1, 4);
       if (rd == 1)
         rd = random(1, 4);
       bars -= rd;
     }

     if (bars <= computerGoal)
     {
       computerGoal -= 4;
     }
     
     String text = getBars(bars);

     if (bars > 0)
     {
       writeToScreen(text, text);
     }
     else
     {
       writeToScreen("You win!", "Code is 7459");
       replay = true;
     }
     
     Serial.println(bars);
     playersTurn = true;
  }
}

String getBars(int bars)
{
  String text = "";
  for (int i = 0; i < bars; i++)
  {
    text += "|";   
  }
  return text;
}

void writeToScreen(String row1, String row2)
{
  lcd.clear();
  lcd.print(row1);
  lcd.setCursor(0, 1);
  lcd.print(row2);
}
