#include "Explorer.h"

Explorer robot;

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(9600);                   
  while (!Serial);

  robot.robotSetup();

  Serial.println("GO FRITZEN I/O ROBOT!");

}

void loop() 
{ 
  robot.robotLoop();
}
