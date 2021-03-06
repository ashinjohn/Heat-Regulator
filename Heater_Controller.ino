/*****************************************************************
Project     : Heat Controller
Description : Maintain temperature in a Cabin as per the values given.
              With Temperature Adjustmet and Timer

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
int button = 1;  //enter switch default value
int selector =0; //selector knob
int temp=0;      //temperature setting
int timer=0;     //timer setting
int maxt=0;      // maximum temperature 
int mint=0;      // minimumtemperature 
int cel;
int hours=0;     // timer hours
int mins=0;      // timer minutes
int sec=0;       // timer seconds

#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,13,12,11,10 );

byte thermometer[8] = //icon for thermometer
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
  pinMode(4,OUTPUT);   // data direction initialisations
  digitalWrite(3,LOW);
  digitalWrite(4,LOW); // initial states

    
  lcd.begin(16, 2);
  lcd.print("HEAT CONTROLLER");
  lcd.createChar(1,thermometer);
  lcd.setCursor(15,1);
  lcd.write(1);
  lcd.setCursor(0,1);
  lcd.print("PILOT for MENU");
  delay(100);

  
}

void loop() {
button = digitalRead(5);

  if (button==LOW){
    button=HIGH;
    delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("      MENU");
    delay(100);
    while (1){
       button = digitalRead(5);
        
       if (button==LOW){
              button=HIGH;      
              switch(selector) {
                case 1: 
                        delay(100);
                        while (1){
                          lcd.clear();
                          lcd.setCursor(0,0);
                          lcd.write(1);
                        
                          cel = (5.0 * analogRead(2) * 100.0) / 1024;
                          lcd.setCursor(2,0); 
                          lcd.print(cel);
                          lcd.print((char)223); //degree sign
                          lcd.print("C");




                            maxt = analogRead(0);
                            
                            maxt = map(maxt, 0, 1023, 0, 255);
                            maxt = constrain(maxt, 0, 255);
                            lcd.setCursor(0,1);
                            lcd.print("MAX:");
                            lcd.print(maxt);
                            lcd.print((char)223); //degree sign
                            lcd.print("C");

                            mint = analogRead(1);
                            
                            mint = map(mint, 0, 1023, 0, 255);
                            mint = constrain(mint, 0, 255);
                            lcd.setCursor(8,1);
                            lcd.print("MIN:");
                            lcd.print(mint);
                            lcd.print((char)223); //degree sign
                            lcd.print("C");
  
                            delay(200);
                                                    
                              button=HIGH;
                              button = digitalRead(5);
                              if (button==LOW){ 
                                  button=HIGH;
                                  break;
                                  }
                                  
                                  
                                 
                        } //while 1 inside case for switch
                        
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("      MENU");
                        delay(100);
                        break;
                          
                        break;                // case 1 break
                case 2: 
                        delay(100);
                        while (1){
                          lcd.clear();
                          lcd.setCursor(0,0);
                          lcd.print("     TIMER      ");
                        
                                                   
                            hours = analogRead(0);
                            
                            hours = map(hours, 0, 1023, 0, 12);
                            hours = constrain(hours, 0, 12);
                            lcd.setCursor(0,1);
                            lcd.print("HOURS:");
                            lcd.print(hours);
                            
                            mins = analogRead(1);
                            
                            mins = map(mins, 0, 1023, 0,60);
                            mins = constrain(mins, 0, 60);
                            lcd.setCursor(9,1);
                            lcd.print("MINS:");
                            lcd.print(mins);
 
                            delay(200);

                              button=HIGH;
                              button = digitalRead(5);
                              if (button==LOW){ 
                                  button=HIGH;
                                  break;
                                  }
                                  
                                  
                                 
                        } //while 1 inside case for switch
                        
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("      MENU");
                        delay(100); 
                        
                        break;  
                        break;                // case 2 break

                case 4: 
                        delay(100);
                        while (1){
                          lcd.clear();
                          lcd.write(1);
                        
                          cel = (5.0 * analogRead(2) * 100.0) / 1024;
                          lcd.setCursor(2,0); 
                          lcd.print(cel);
                          lcd.print((char)223); //degree sign
                          lcd.print("C");
                          lcd.print(" ");
                          lcd.print(maxt);
                          lcd.print(" ");
                          lcd.print(mint);
                          
                          

                        if (mins==0&&hours==0&&sec==0)
                        {   lcd.clear();
                            lcd.setCursor(0,1);
                            lcd.print("Timer Reset !     ");
                            digitalWrite(4,HIGH);

                            lcd.setCursor(0,0);
                            lcd.print("HEATER OFF");
                            digitalWrite(3,LOW);
                                   

                              start:
                              button=HIGH;
                              button = digitalRead(5);
                              if (button==LOW){ 
                                  button=HIGH;
                                  digitalWrite(4,LOW);
                                  break;
                                  }
                              goto start;
                            
                            
                          }

                         else  if (mint==0||maxt==0)
                        {lcd.setCursor(0,1);
                            lcd.print("Set Temperature First! ");
                           

                              start1:
                              button=HIGH;
                              button = digitalRead(5);
                              if (button==LOW){ 
                                  button=HIGH;
                                  digitalWrite(4,LOW);
                                  break;
                                  }
                              goto start1;
                            
                            
                          }


                         else if (mins<=0&&hours>0){
                          mins=60;
                          hours--;
                          }

                          else if (sec<=0&&mins>0){
                            mins--;
                            sec=60;
                            }

                          else {
                            sec--;
                            }

                        if (cel>=maxt){
                          lcd.setCursor(12,0);
                          lcd.print("OFF");
                          digitalWrite(3,LOW); 
                          }
                       else if (cel<=mint){
                          lcd.setCursor(12,0);
                          lcd.print("ON");
                          digitalWrite(3,HIGH); 
                          }
                                                  
                            
                            lcd.setCursor(0,1);
                            lcd.print("H:");
                            lcd.print(hours);
                            
                            lcd.setCursor(6,1);
                            lcd.print("M:");
                            lcd.print(mins);
    
                            lcd.setCursor(11,1);
                            lcd.print("S:");
                            lcd.print(sec);
  

  
                            delay(1000);
                            
                          
                              button=HIGH;
                              button = digitalRead(5);
                              if (button==LOW){ 
                                  button=HIGH;
                                  break;
                                  }
                                  
                                  
                                 
                        } //while 1 inside case for switch
                        
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("      MENU");
                        delay(100);  
                        
                        break;
                          
                        break;                // case 4 break
 case 3: 
                        delay(100);
                        while (1){
                          lcd.clear();
                          lcd.setCursor(0,0);
                          lcd.print("HEATER ON");
                          digitalWrite(3,HIGH);
                          delay(500);
                                                    
                              button=HIGH;
                              button = digitalRead(5);
                              if (button==LOW){ 
                                  button=HIGH;
                                   lcd.setCursor(0,0);
                                   lcd.print("HEATER OFF");
                                   digitalWrite(3,LOW);
                                   delay(500);
                                                                      
                                  
                                  break;
                                  }
                                  
                                  
                                 
                        } //while 1 inside case for switch
                        
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("      MENU");
                        delay(100);
                        break;
                          
                        break;                // case 3 break



                
              }//switch closing  
          }//if button low after selecting



       
       
       
       else if (analogRead(0)<=60){
          selector=1;
          lcd.setCursor(0,1);
          lcd.print("SET TEMPERATURE ");
          }
        else if (analogRead(0)<=120){
          selector=2;
          lcd.setCursor(0,1);
          lcd.print("SET TIMER       ");
          
          }
        else if (analogRead(0)<=180){
          selector=3;
          lcd.setCursor(0,1);
          lcd.print("MANUAL HEATER ON ");
          }
      else if (analogRead(0)>180){
          selector=4;
          lcd.setCursor(0,1);
          lcd.print("START           ");
          }
     
                
    
      }// menu while 
    
    
    
  }//pilot button low

}//loop
