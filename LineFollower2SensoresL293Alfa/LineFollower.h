#ifndef LineFollower2IR_h
	#define LineFollower2IR_h

  	#if defined(ARDUINO) && ARDUINO >= 100
    	#include <Arduino.h>
  	#else
    	#include <WProgram.h>
		#include <pins_arduino.h>
	#endif

  #include "src/FioMotorDriver.h"
  #include "src/FioSensorDistance.h"
  #include "src/TimerFreeTone.h"


  #define LEFT_SENSOR_PIN A2
  #define RIGHT_SENSOR_PIN A3
  #define BLACK  0
  #define WHITE  1
  #define DEFAULT_TONE_PIN 4

class LineFollower
{
    public:
        
      void robotSetup();
	    void robotLoop();

     private:
         short left_sensor;
         short right_sensor;
         int lastDIR = 0;
         FioMotorDriver motor;
         FioSensorDistance distance;
         void readLineFollowerSensors();
         void doLineFollowerObstacle();
};

#endif
