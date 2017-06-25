/*************************************************************
Project     : Heat Controller
Description : Maintain temperature in a Cabin as per the values given.

Programmer  : Ashin Basil John
Board       : Arduino Uno


Pin Configuration
RS:   D8
RW:   D9
DATA: D13-D10

ENTER:  D5
DEVICE: D3
BUZZER: D4

LEFT  POT: A0
RIGHT POT: A1
TEMPERAURE SENSOR: A2 








***************************************************************/

const int buzzer = 4;
const int device = 3;
int button = 1; 


#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,13,12,11,10 );

byte termometru[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};




void setup() { 

  
  
  pinMode(5,INPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
    
  lcd.begin(16, 2);
  
  lcd.print("Heat Controller");
  lcd.createChar(1,termometru);
  lcd.setCursor(0,1);
  lcd.write(1); 


}

void loop() {
  // put your main code here, to run repeatedly:

//button = digitalRead(5);


float mv = ( analogRead(0)/1024.0)*5000; 
float cel = mv/10; 
lcd.setCursor(2,1);
lcd.print(cel);

}
