#ifndef LMotorController_h
#define LMotorController_h


#include "Arduino.h"


class LMotorController
{
protected:
    int _ena, _in1, _enb, _in3;
    int _currentSpeed;
    double _motorAConst, _motorBConst;
public:
    LMotorController(int ena, int in1, int enb, int in3, double motorAConst, double motorBConst);
    void move(int leftSpeed, int rightSpeed, int minAbsSpeed);
    void move(int speed);
    void move(int speed, int minAbsSpeed);
    void turnLeft(int speed, bool kick);
    void turnRight(int speed, bool kick);
    void stopMoving();
};


#endif
