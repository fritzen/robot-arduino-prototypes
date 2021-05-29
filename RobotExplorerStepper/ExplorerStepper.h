#ifndef ExplorerStepper_h
	#define ExplorerStepper_h

  	#if defined(ARDUINO) && ARDUINO >= 100
    	#include <Arduino.h>
  	#else
    	#include <WProgram.h>
		#include <pins_arduino.h>
	#endif

  #include "src/FioMotorDriver.h"
  #include "src/FioSensorDistance.h"
  #include "src/TimerFreeTone.h"

  #define IN1  2
  #define IN2  3
  #define IN3  4
  #define IN4  5

class ExplorerStepper
{
  public:
    void robotSetup();
    void robotLoop();
  private:
     void setDirection();
     void stepper(int xw);
     FioMotorDriver motor;
     FioSensorDistance distance;
     int Steps = 0;
     boolean Direction = true;// gre
     unsigned long last_time;
     unsigned long currentMillis;
     int steps_left = 500;
     long time;

};
  
#endif
