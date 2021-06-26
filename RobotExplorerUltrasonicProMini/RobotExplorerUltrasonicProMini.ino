#include "Explorer.h"

Explorer robot;


int buzzer = 4;

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(9600);                   
  while (!Serial);
  pinMode(buzzer,OUTPUT);
  
  robot.robotSetup();

    tone(buzzer,261);    
    delay(200);
    noTone(buzzer); 

    tone(buzzer,293);             
    delay(200);    
    noTone(buzzer); 

    tone(buzzer,329);      
    delay(200);
    noTone(buzzer);     

    tone(buzzer,349);    
    delay(200);    
    noTone(buzzer); 

    tone(buzzer,392);            
    delay(200);
    noTone(buzzer); 
    
  Serial.println("GO FRITZEN I/O ROBOT!");

}

void loop() 
{ 
  robot.robotLoop();
}
