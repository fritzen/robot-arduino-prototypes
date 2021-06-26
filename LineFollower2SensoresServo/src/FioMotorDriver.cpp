 /* ---------------------------------------------------------------------------------------
 * Autor / Author: Eduardo Fritzen - eduardo@fritzen.io
 * Não é permitido o uso para fins comerciais deste código sem a autorização por escrito do autor
 * Use of this code for commercial purposes is not permitted without written authorization from the author
 * ---------------------------------------------------------------------------------------
 */
#include "FioMotorDriver.h"

#include <Arduino.h>

FioMotorDriver::FioMotorDriver()
{

}

void FioMotorDriver::attach(uint8_t motorType)
{          
  _isServo = (motorType == TYPE_SERVO);

  if (_isServo) {
      attachServoMotor(DEFAULT_SERVO_MOTOR_A_PIN, DEFAULT_SERVO_MOTOR_B_PIN);
  } else {
      attachDCMotor(DEFAULT_MOTOR_A_PIN_1, DEFAULT_MOTOR_A_PIN_2, DEFAULT_MOTOR_B_PIN_1, DEFAULT_MOTOR_B_PIN_2);
  }
}

void FioMotorDriver::attachDCMotor(uint8_t pin1MotorA, uint8_t pin2MotorA, uint8_t pin1MotorB, uint8_t pin2MotorB)
{
  _pin1MA = pin1MotorA; // speed
  _pin2MA = pin2MotorA; // direction
  _pin1MB = pin1MotorB; // speed
  _pin2MB = pin2MotorB; // direction
  
  _isServo = false;
  
  pinMode(_pin1MA, OUTPUT);
  pinMode(_pin2MA, OUTPUT);
  pinMode(_pin1MB, OUTPUT);
  pinMode(_pin2MB, OUTPUT);
}

void FioMotorDriver::attachServoMotor(uint8_t pinServo1, uint8_t pinServo2)
{
    _pinServoA = pinServo1;
    _pinServoB = pinServo2;    
    _isServo = true;

    _servoA.detach();
    _servoB.detach();
    pinMode(_pinServoA, OUTPUT);
    pinMode(_pinServoB, OUTPUT);  
    
    _servoA.attach(_pinServoA);
    _servoB.attach(_pinServoB);
}





void FioMotorDriver::test(){
      int pos = 0; 
            for (pos = 0; pos <= 180; pos += 1) {
          _servoA.write(pos);
         _servoB.write(pos);
          delay(15);
        }
        for (pos = 180; pos >= 0; pos -= 1) {
          _servoA.write(pos);
         _servoB.write(pos);
          delay(15);
        }
}
void FioMotorDriver::forward(uint16_t pwm)
{
  if (_isServo) {
    _servoA.write(SERVO_MIN);
    _servoB.write(SERVO_MAX);      
  } else {
    analogWrite(_pin1MA, pwm);
    digitalWrite(_pin2MA, HIGH);
    analogWrite(_pin1MB, pwm);
    digitalWrite(_pin2MB, HIGH);
  }  
}
void FioMotorDriver::backward(uint16_t pwm)
{
  if (_isServo) {
    _servoA.write(SERVO_MAX);
    _servoB.write(SERVO_MIN);
  } else {
    analogWrite(_pin1MA, pwm);
    digitalWrite(_pin2MA, LOW);
    analogWrite(_pin1MB, pwm);
    digitalWrite(_pin2MB, LOW);
  }
}

void FioMotorDriver::turnRight(uint16_t pwm)
{
  if (_isServo) {
    _servoA.write(SERVO_MIN);
    _servoB.write(SERVO_STOP);
  } else {
    analogWrite(_pin1MA, 0);
    digitalWrite(_pin2MA, HIGH);
    analogWrite(_pin1MB, pwm);
    digitalWrite(_pin2MB, LOW);
  }
}

void FioMotorDriver::turnLeft(uint16_t pwm)
{
  if (_isServo) {
    _servoA.write(SERVO_STOP);
    _servoB.write(SERVO_MAX);
  } else {
    analogWrite(_pin1MA, pwm);
    digitalWrite(_pin2MA, LOW);
    analogWrite(_pin1MB, 0);
    digitalWrite(_pin2MB, HIGH);
  }
}

void FioMotorDriver::turnRightAxis(uint16_t pwm) 
{ 
  if (_isServo) {
    _servoA.write(SERVO_MAX);
    _servoB.write(SERVO_MAX);
  } else {
    analogWrite(_pin1MA, pwm);
    digitalWrite(_pin2MA, HIGH);
    analogWrite(_pin1MB, pwm);
    digitalWrite(_pin2MB, LOW);
  }
}

void FioMotorDriver::turnLeftAxis(uint16_t pwm) 
{ 
  if (_isServo) {
    _servoA.write(SERVO_MIN);
    _servoB.write(SERVO_MIN);
  } else {
    analogWrite(_pin1MA, pwm);
    digitalWrite(_pin2MA, LOW);
    analogWrite(_pin1MB, pwm);
    digitalWrite(_pin2MB, HIGH);
  }
}

void FioMotorDriver::stop()
{
  if (_isServo) {
    _servoA.write(SERVO_STOP);
    _servoB.write(SERVO_STOP);
  } else {
    analogWrite(_pin1MA, 0);
    digitalWrite(_pin2MA, 0);
    analogWrite(_pin1MB, 0);
    digitalWrite(_pin2MB, 0);
  }
}

void FioMotorDriver::forward()
{
  forward(DEFAULT_SPEED);
}

void FioMotorDriver::backward()
{
  backward(DEFAULT_SPEED);
}

void FioMotorDriver::turnRight()
{
  turnRight(DEFAULT_SPEED);
}

void FioMotorDriver::turnLeft()
{
  turnLeft(DEFAULT_SPEED);
}

void FioMotorDriver::turnRightAxis()
{
  turnRightAxis(DEFAULT_SPEED);
}

void FioMotorDriver::turnLeftAxis()
{
  turnLeftAxis(DEFAULT_SPEED);
}
