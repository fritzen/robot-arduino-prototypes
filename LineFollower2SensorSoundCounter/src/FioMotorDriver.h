 /* ---------------------------------------------------------------------------------------
 * Autor / Author: Eduardo Fritzen eduardo@fritzen.io
 * Não é permitida o uso para fins comerciais deste código sem a autrorização por escrito do autor
 * Use of this code for commercial purposes is not permitted without written authorization from the author
 * ---------------------------------------------------------------------------------------
 */
#ifndef FioMotorDriver_h
#define FioMotorDriver_h
 
#include <Arduino.h>
#include <stdio.h>
#include <inttypes.h>

#include <Servo.h>

#define TYPE_SERVO 1
#define TYPE_L293 2

#define DEFAULT_SPEED 60
#define SERVO_STOP 90
#define SERVO_MAX 120
#define SERVO_MIN 60

//L293D - FECHADO DE ACORDO COM A PLACA SHIELD  
#define DEFAULT_MOTOR_A_PIN_1 10
#define DEFAULT_MOTOR_A_PIN_2 12
#define DEFAULT_MOTOR_B_PIN_1 11
#define DEFAULT_MOTOR_B_PIN_2 13

/*
int E1 = 10;
int M1 = 12;
int E2 =11;
int M2 = 13;
*/

// Servo
#define DEFAULT_SERVO_MOTOR_A_PIN 10
#define DEFAULT_SERVO_MOTOR_B_PIN 12


#define SENSOR_THRESHOLD 400


class FioMotorDriver
{
    public:
        

        FioMotorDriver();
        void forward(uint16_t pwm);
        void backward(uint16_t pwm);
        void turnRight(uint16_t pwm);
        void turnLeft(uint16_t pwm);
        void turnRightAxis(uint16_t pwm);
        void turnLeftAxis(uint16_t pwm);
        void forward();
        void backward();
        void turnRight();
        void turnLeft();
        void turnRightAxis();
        void turnLeftAxis();
        void stop();
        void test();
        void attachDCMotor(uint8_t pin1MotorA, uint8_t pin2MotorA, uint8_t pin1MotorB, uint8_t pin2MotorB);
        void attachServoMotor(uint8_t pinServo1, uint8_t pinServo2);
        void attach(uint8_t motorType);
 
    private:        
        Servo _servoA;
        Servo _servoB;
        uint8_t _pin1MA;
        uint8_t _pin2MA;
        uint8_t _pin1MB;
        uint8_t _pin2MB;
        uint8_t _pinServoA;
        uint8_t _pinServoB;
        bool _isServo = false;
};
 
#endif
