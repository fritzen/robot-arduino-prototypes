 /* ---------------------------------------------------------------------------------------
 * Autor / Author: Eduardo Fritzen eduardo@fritzen.io
 * Não é permitida o uso para fins comerciais deste código sem a autrorização por escrito do autor
 * Use of this code for commercial purposes is not permitted without written authorization from the author
 * ---------------------------------------------------------------------------------------
 */
#ifndef FioDistanceSensor_h
#define FioDistanceSensor_h
 
#include <Arduino.h>
#include <stdio.h>
#include <inttypes.h>

#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>
//#include <HCSR04.h> //https://github.com/Martinsos/arduino-lib-hc-sr04




#define TYPE_NONE 0
#define TYPE_ULTRASONIC 1
#define TYPE_LASER 2
#define TYPE_DIGITAL_DISTANCE 3

#define DIGITAL_DISTANCE_PIN 2

#define TRIG_PIN A1
#define ECHO_PIN A2
#define MAX_DIST 200
#define COLLISION_DIST 15
// LASER SENSOR
// A4 SDA_PIN
// A5 SCL_PIN
#define SENSOR_THRESHOLD 390



class FioSensorDistance {
    public:        
        FioSensorDistance();
        bool isCollision();
        //void attachUltrasonicSensor(uint8_t pintTrig, uint8_t pinEcho);
        void attach(uint8_t sensorType);
 
    private:
        int _sensorType;
        VL53L0X _laser;
        int ping();
};
 
#endif
