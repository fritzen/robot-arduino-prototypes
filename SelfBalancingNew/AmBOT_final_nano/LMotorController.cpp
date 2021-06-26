#include "LMotorController.h"
#include "Arduino.h"


//L9110S pwm - PWM signal to input IA to control the motor speed and a digital output to input IB to control its direction.

LMotorController::LMotorController(int ena, int in1, int enb, int in3, double motorAConst, double motorBConst)
{
    _motorAConst = motorAConst;
    _motorBConst = motorBConst;
    
	_ena = ena;
	_in1 = in1;
	_enb = enb;
	_in3 = in3;

	pinMode(_ena, OUTPUT);
	pinMode(_in1, OUTPUT);

	pinMode(_enb, OUTPUT);
	pinMode(_in3, OUTPUT);

}


void LMotorController::move(int leftSpeed, int rightSpeed, int minAbsSpeed)
{
    if (rightSpeed < 0)
    {
        rightSpeed = min(rightSpeed, -1*minAbsSpeed);
        rightSpeed = max(rightSpeed, -255);
    }
    else if (rightSpeed > 0)
    {
        rightSpeed = max(rightSpeed, minAbsSpeed);
        rightSpeed = min(rightSpeed, 255);
    }
    
    int realRightSpeed = map(abs(rightSpeed), 0, 255, minAbsSpeed, 255);

    if (leftSpeed < 0)
    {
        leftSpeed = min(leftSpeed, -1*minAbsSpeed);
        leftSpeed = max(leftSpeed, -255);
    }
    else if (leftSpeed > 0)
    {
        leftSpeed = max(leftSpeed, minAbsSpeed);
        leftSpeed = min(leftSpeed, 255);
    }
    
    int realLeftSpeed = map(abs(leftSpeed), 0, 255, minAbsSpeed, 255);
    
    digitalWrite(_in3, rightSpeed > 0 ? HIGH : LOW);
    digitalWrite(_in1, leftSpeed > 0 ? HIGH : LOW);
    analogWrite(_ena, realRightSpeed * _motorAConst);
    analogWrite(_enb, realLeftSpeed * _motorBConst);
}


void LMotorController::move(int speed, int minAbsSpeed)
{
    int direction = 1;
    
    if (speed < 0)
    {
        direction = -1;
        
        speed = min(speed, -1*minAbsSpeed);
        speed = max(speed, -255);
    }
    else
    {
        speed = max(speed, minAbsSpeed);
        speed = min(speed, 255);
    }
    
    if (speed == _currentSpeed) return;
    
    int realSpeed = max(minAbsSpeed, abs(speed));
    
    digitalWrite(_in1, speed > 0 ? HIGH : LOW);
    digitalWrite(_in3, speed > 0 ? HIGH : LOW);
    analogWrite(_ena, realSpeed * _motorAConst);
    analogWrite(_enb, realSpeed * _motorBConst);
    
    _currentSpeed = direction * realSpeed;
}


void LMotorController::move(int speed)
{
    if (speed == _currentSpeed) return;
    
    if (speed > 255) speed = 255;
    else if (speed < -255) speed = -255;
    
    digitalWrite(_in1, speed > 0 ? HIGH : LOW);
    digitalWrite(_in3, speed > 0 ? HIGH : LOW);
    analogWrite(_ena, abs(speed) * _motorAConst);
    analogWrite(_enb, abs(speed) * _motorBConst);
    
    _currentSpeed = speed;
}


void LMotorController::turnLeft(int speed, bool kick)
{
    digitalWrite(_in1, HIGH);
    digitalWrite(_in3, LOW);

    
    if (kick)
    {
        analogWrite(_ena, 255);
        analogWrite(_enb, 255);
    
        delay(100);
    }
    
    analogWrite(_ena, speed * _motorAConst);
    analogWrite(_enb, speed * _motorBConst);
}


void LMotorController::turnRight(int speed, bool kick)
{
    digitalWrite(_in1, LOW);
    digitalWrite(_in3, HIGH);

 
    if (kick)
    {
        analogWrite(_ena, 255);
        analogWrite(_enb, 255);
    
        delay(100);
    }
    
    analogWrite(_ena, speed * _motorAConst);
    analogWrite(_enb, speed * _motorBConst);
}


void LMotorController::stopMoving()
{
    digitalWrite(_in1, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_ena, HIGH);
    digitalWrite(_enb, HIGH);
    
    _currentSpeed = 0;
}
