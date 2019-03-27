#include <Adafruit_LEDBackpack.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
uint8_t lines[9][20];
uint8_t temp[8];
bool correct[9][9];
bool answers[9][9];
int lastCase1 = 0;
int lastCase2 = 0;
float read1, read2;
int ledColor = LED_RED;
bool win = false;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(7, INPUT);
  matrix.begin(0x70);

//2-2,000/8
//3-1,500/1
//5-1,666/7
//8-1,600/2
//13-1,625/6
//21-1,615/3
//34-1,619/5
//55-1,618/4
  correct[1][2] = true;
  correct[2][4] = true;
  correct[3][6] = true;
  correct[4][8] = true;
  correct[5][7] = true;
  correct[6][5] = true;
  correct[7][3] = true;
  correct[8][1] = true;
  
  lines[0][0] = B00000000;
  
  lines[1][0] = B10000000;
  lines[1][1] = B01000000;
  lines[1][2] = B00100000;
  lines[1][3] = B00010000;
  lines[1][4] = B00001000;
  lines[1][5] = B00000100;
  lines[1][6] = B00000010;
  lines[1][7] = B00000001;

  lines[2][0] = B00001010;
  lines[2][1] = B10000010;
  lines[2][2] = B10100000;
  lines[2][3] = B10010000;
  lines[2][4] = B10001000;
  lines[2][5] = B10000100;
  lines[2][6] = B01000010;
  lines[2][7] = B00100010;
  lines[2][8] = B00010010;
  lines[2][9] = B00001010;
  lines[2][10] = B00001001;
  lines[2][11] = B00010001;
  lines[2][12] = B00100001;
  lines[2][13] = B01000001;
  lines[2][14] = B00101000;

  lines[3][0] = B10001010;
  lines[3][1] = B10010010;
  lines[3][2] = B10100100;
  lines[3][3] = B10010010;
  lines[3][4] = B10001001;
  lines[3][5] = B10010100;
  lines[3][6] = B01100010;
  lines[3][7] = B10100010;
  lines[3][8] = B01010010;
  lines[3][9] = B01001010;
  lines[3][10] = B01001001;
  lines[3][11] = B00010101;
  lines[3][12] = B00101001;
  lines[3][13] = B01010001;
  lines[3][14] = B10101000;

  lines[4][0] = B10101010;
  lines[4][1] = B10110010;
  lines[4][2] = B10101100;
  lines[4][3] = B10011010;
  lines[4][4] = B10101001;
  lines[4][5] = B11010100;
  lines[4][6] = B01101010;
  lines[4][7] = B10110010;
  lines[4][8] = B01010011;
  lines[4][9] = B01001110;
  lines[4][10] = B01101001;
  lines[4][11] = B01010101;
  lines[4][12] = B01101001;
  lines[4][13] = B01010101;
  lines[4][14] = B10101100;

  lines[5][0] = B10101011;
  lines[5][1] = B10110110;
  lines[5][2] = B10111100;
  lines[5][3] = B10111010;
  lines[5][4] = B11101001;
  lines[5][5] = B11010101;
  lines[5][6] = B11101010;
  lines[5][7] = B10110110;
  lines[5][8] = B01011011;
  lines[5][9] = B01011110;
  lines[5][10] = B01101101;
  lines[5][11] = B01011101;
  lines[5][12] = B01101101;
  lines[5][13] = B01011101;
  lines[5][14] = B10101101;

  lines[6][0] = B11111100;

  lines[7][0] = B01111111;
  lines[7][1] = B10111111;
  lines[7][2] = B11011111;
  lines[7][3] = B11101111;
  lines[7][4] = B11110111;
  lines[7][5] = B11111011;
  lines[7][6] = B11111101;
  lines[7][7] = B11111110;

  lines[8][0] = B11111111;
}

void loop()
{
  read2 += (analogRead(A0) - read2) * 0.05;
  /*if (read2 != read2)
    read2 = 0;*/
  read1 += (analogRead(A1) - read1) * 0.05;

  //Serial.println((int)read2);
  //Serial.println((int)read1);
  //Serial.println(" ");

    
  switch ((int)read2) {
    case 0 ... 127: 
      if (lastCase1 != 1)
      {
        lastCase1 = 1;
        Get2Lights();
      }
      break;
    case 128 ... 255:
      if (lastCase1 != 2)
      {
        lastCase1 = 2;
        Get3Lights();
      }
      break;
    case 256 ... 383:
      if (lastCase1 != 3)
      {
        lastCase1 = 3;
        Get5Lights();
      }
      break;
    case 384 ... 511:
      if (lastCase1 != 4)
      {
        lastCase1 = 4;
        Get8Lights();
      }
      break;
    case 512 ... 639:
      if (lastCase1 != 5)
      {
        lastCase1 = 5;
        Get13Lights();
      }
      break;
    case 640 ... 767:
      if (lastCase1 != 6)
      {
        lastCase1 = 6;
        Get21Lights();
      }
      break;
    case 768 ... 895:
      if (lastCase1 != 7)
      {
        lastCase1 = 7;
        Get34Lights();
      }
      break;
    case 896 ... 1023:
      if (lastCase1 != 8)
      {
        lastCase1 = 8;
        Get55Lights();
      }
      break;
  } 

  switch ((int)read1) {
    case 0 ... 127:
      if (lastCase2 != 1)
      {
        temp[7] = lines[1][0];
        lastCase2 = 1;
        UpdateMatrix();  
      }    
      break;
    case 128 ... 255:
      if (lastCase2 != 2)
      {
        temp[7] = lines[1][1];
        lastCase2 = 2;
        UpdateMatrix();  
      }
      break;
    case 256 ... 383:
      if (lastCase2 != 3)
      {
        temp[7] = lines[1][2];
        lastCase2 = 3;
        UpdateMatrix();  
      }
      break;
    case 384 ... 511:
      if (lastCase2 != 4)
      {
        temp[7] = lines[1][3];
        lastCase2 = 4;
        UpdateMatrix();  
      }
      break;
    case 512 ... 639:
      if (lastCase2 != 5)
      {
        temp[7] = lines[1][4];
        lastCase2 = 5;
        UpdateMatrix();  
      }
      break;
    case 640 ... 767:
      if (lastCase2 != 6)
      {
        temp[7] = lines[1][5];
        lastCase2 = 6;
        UpdateMatrix();  
      }
      break;
    case 768 ... 895:
      if (lastCase2 != 7)
      {
        temp[7] = lines[1][6];
        lastCase2 = 7;
        UpdateMatrix();  
      }
      break;
    case 896 ... 1023:
      if (lastCase2 != 8)
      {
        temp[7] = lines[1][7];
        lastCase2 = 8;
        UpdateMatrix();  
      }
      break;
  }
  
  

  if (digitalRead(7) == LOW)
  {
    if (win)
    {
      win = false;
      ResetAnswers();
      lastCase1 = 0;
      lastCase2 = 0;
      matrix.setRotation(0);
      UpdateMatrix();
    }
    else if (correct[lastCase2][lastCase1])
    {
      answers[lastCase2][lastCase1] = true;
      UpdateMatrix();
      if (
        answers[1][2] && 
        answers[2][4] && 
        answers[3][6] && 
        answers[4][8] && 
        answers[5][7] && 
        answers[6][5] &&
        answers[7][3] &&
        answers[8][1])
      {
        win = true;    
      }
    }
    else 
    {
      Serial.println("reset");
      ResetAnswers();
    }

    delay(500);
  }

  if (win)
  {
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextSize(1);
    matrix.setRotation(3);
    matrix.setTextColor(LED_GREEN);
    for (int8_t x=7; x>=-36; x--) {
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("3428");
      matrix.writeDisplay();
      delay(100);
    }      
  }
}

void UpdateMatrix()
{
    if (answers[lastCase2][lastCase1])
      ledColor = LED_GREEN;
    else
      ledColor = LED_RED;
  
    matrix.clear();      // clear display
    matrix.drawBitmap(0, 0, temp, 8, 8, ledColor);
    matrix.writeDisplay();  // write the changes we just made to the display
}

void Get2Lights()
{
  if (random(0, 3) > 0)
  {   
    int hit = 0;
    for (int i = 0; i < 7; i++)
    { 
      if ((random(0, 2) == 1 && hit < 2) || (i == 5 && hit == 0) || (i == 6 && hit == 1))
      {
        hit++;
        temp[i] = lines[1][random(0, 8)];
      }
      else
        temp[i] = lines[0][0]; 
    }
  }
  else
  {
    int r = random(0, 7);
    for (int i = 0; i < 7; i++)
    { 
      if (i == r)
        temp[i] = lines[2][random(0, 14)];
      else
        temp[i] = lines[0][0];
    }
  }

  UpdateMatrix();
}

void Get3Lights()
{
  if (random(0, 5) > 0)
  {   
    int hit = 0;
    for (int i = 0; i < 7; i++)
    { 
      if ((random(0, 2) == 1 && hit < 3) || (i == 4 && hit == 0) || (i == 5 && hit == 1) || (i == 6 && hit == 2))
      {
        hit++;
        temp[i] = lines[1][random(0, 8)];
      }
      else
        temp[i] = lines[0][0]; 
    }
  }
  else
  {
    int r = random(0, 7);
    for (int i = 0; i < 7; i++)
    { 
      if (i == r)
        temp[i] = lines[3][random(0, 14)];
      else
        temp[i] = lines[0][0];
    }
  }

  UpdateMatrix();
}

void Get5Lights()
{
  int hit = 0;
  for (int i = 0; i < 7; i++)
  { 
    if ((random(0, 2) == 1 && hit < 5) || (i == 2 && hit == 0) || (i == 3 && hit == 1) || (i == 4 && hit == 2) || (i == 5 && hit == 3) || (i == 6 && hit == 4))
    {
      hit++;
      temp[i] = lines[1][random(0, 8)];
    }
    else
      temp[i] = lines[0][0]; 
  }

  UpdateMatrix();
}

void Get8Lights()
{
  int hit = 0;
  for (int i = 0; i < 7; i++)
  { 
    if ((random(0, 2) == 1 && hit < 1) || (i == 6 && hit == 0))
    {
      hit++;
      temp[i] = lines[2][random(0, 14)];
    }
    else
      temp[i] = lines[1][random(0, 8)]; 
  }

  UpdateMatrix();
}

void Get13Lights()
{
  int hit = 0;
  for (int i = 0; i < 7; i++)
  { 
    if ((random(0, 2) == 1 && hit < 1) || (i == 6 && hit == 0))
    {
      hit++;
      temp[i] = lines[1][random(0, 8)];
    }
    else
      temp[i] = lines[2][random(0, 14)]; 
  }

  UpdateMatrix();
}

void Get21Lights()
{
  int hit = 0;
  for (int i = 0; i < 7; i++)
  { 
     temp[i] = lines[3][random(0, 14)];
  }

  UpdateMatrix();
}

void Get34Lights()
{
  int hit = 0;
  for (int i = 0; i < 7; i++)
  { 
    if ((random(0, 2) == 1 && hit < 1) || (i == 6 && hit == 0))
    {
      hit++;
      temp[i] = lines[4][random(0, 14)];
    }
    else
      temp[i] = lines[5][random(0, 14)]; 
  }

  UpdateMatrix();
}

void Get55Lights()
{
  int hit = 0;
  for (int i = 0; i < 7; i++)
  { 
    if ((random(0, 2) == 1 && hit < 1) || (i == 6 && hit == 0))
    {
      hit++;
      temp[i] = lines[7][random(0, 8)];
    }
    else
      temp[i] = lines[8][0]; 
  }

  UpdateMatrix();
}

void ResetAnswers()
{
  answers[1][2] = false; 
  answers[2][4] = false; 
  answers[3][6] = false;
  answers[4][8] = false;
  answers[5][7] = false;
  answers[6][5] = false;
  answers[7][3] = false;
  answers[8][1] = false;
}
