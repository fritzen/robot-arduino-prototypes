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
      attachDCMotor(DEFAULT_MOTOR_IN1_PIN, DEFAULT_MOTOR_IN2_PIN, DEFAULT_MOTOR_IN3_PIN, DEFAULT_MOTOR_IN4_PIN, DEFAULT_MOTOR_ENA_PIN, DEFAULT_MOTOR_ENB_PIN);
  }
}

void FioMotorDriver::attachDCMotor(uint8_t pin1MotorA, uint8_t pin2MotorA, uint8_t pin1MotorB, uint8_t pin2MotorB)
{
  attachDCMotor(pin1MotorA, pin2MotorA, pin1MotorB, pin2MotorB, DEFAULT_MOTOR_ENA_PIN, DEFAULT_MOTOR_ENB_PIN);
}

void FioMotorDriver::attachDCMotor(uint8_t pin1MotorA, uint8_t pin2MotorA, uint8_t pin1MotorB, uint8_t pin2MotorB, uint8_t pinENMA, uint8_t pinENMB)
{
  _pin1MA = pin1MotorA; // direction
  _pin2MA = pin2MotorA; // direction
  _pin1MB = pin1MotorB; // direction
  _pin2MB = pin2MotorB; // direction
  _pinENMA = pinENMA; //pwm
  _pinENMB = pinENMB; //pwm
  
  _isServo = false;
  
  pinMode(_pin1MA, OUTPUT);
  pinMode(_pin2MA, OUTPUT);
  pinMode(_pin1MB, OUTPUT);
  pinMode(_pin2MB, OUTPUT);
  pinMode(_pinENMA, OUTPUT);
  pinMode(_pinENMB, OUTPUT);

  setSpeed(DEFAULT_SPEED, DEFAULT_SPEED);
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

void FioMotorDriver::setSpeed(uint16_t pwm1, uint16_t pwm2) {
  analogWrite(_pinENMA, pwm1);
  analogWrite(_pinENMB, pwm2);
}


void FioMotorDriver::forward(uint16_t pwm)
{
  if (_isServo) {
    _servoA.write(SERVO_MIN);
    _servoB.write(SERVO_MAX);      
  } else {
    digitalWrite(_pin1MA, HIGH);
    digitalWrite(_pin2MA, LOW);
    digitalWrite(_pin1MB, HIGH);
    digitalWrite(_pin2MB, LOW);
  }  
}
void FioMotorDriver::backward(uint16_t pwm)
{
  if (_isServo) {
    _servoA.write(SERVO_MAX);
    _servoB.write(SERVO_MIN);
  } else {
    digitalWrite(_pin1MA, LOW);
    digitalWrite(_pin2MA, HIGH);
    digitalWrite(_pin1MB, LOW);
    digitalWrite(_pin2MB, HIGH);
  }
}

void FioMotorDriver::turnRight(uint16_t pwm)
{
  if (_isServo) {
    _servoA.write(SERVO_MIN);
    _servoB.write(SERVO_STOP);
  } else {
    digitalWrite(_pin1MA, LOW);
    digitalWrite(_pin2MA, LOW);
    digitalWrite(_pin1MB, HIGH);
    digitalWrite(_pin2MB, LOW);
  }
}

void FioMotorDriver::turnRightAxis(uint16_t pwm) 
{ 
  if (_isServo) {
    _servoA.write(SERVO_MAX);
    _servoB.write(SERVO_MAX);
  } else {
    digitalWrite(_pin1MA, LOW);
    digitalWrite(_pin2MA, HIGH);
    digitalWrite(_pin1MB, HIGH);
    digitalWrite(_pin2MB, LOW);
  }
}

void FioMotorDriver::turnLeft(uint16_t pwm)
{
  if (_isServo) {
    _servoA.write(SERVO_STOP);
    _servoB.write(SERVO_MAX);
  } else {
    digitalWrite(_pin1MA, HIGH);
    digitalWrite(_pin2MA, LOW);
    digitalWrite(_pin1MB, LOW);
    digitalWrite(_pin2MB, LOW);
  }
}

void FioMotorDriver::turnLeftAxis(uint16_t pwm) 
{ 
  if (_isServo) {
    _servoA.write(SERVO_MIN);
    _servoB.write(SERVO_MIN);
  } else {
    digitalWrite(_pin1MA, HIGH);
    digitalWrite(_pin2MA, LOW);
    digitalWrite(_pin1MB, LOW);
    digitalWrite(_pin2MB, HIGH);
  }
}

void FioMotorDriver::stop() //PONTO MORTO = TUDO LOW
{
  if (_isServo) {
    _servoA.write(SERVO_STOP);
    _servoB.write(SERVO_STOP);
  } else {
    digitalWrite(_pin1MA, HIGH);
    digitalWrite(_pin2MA, HIGH);
    digitalWrite(_pin1MB, HIGH);
    digitalWrite(_pin2MB, HIGH);
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
