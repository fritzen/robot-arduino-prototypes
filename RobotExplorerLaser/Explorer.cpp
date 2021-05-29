#include "Explorer.h"


void Explorer::robotSetup() {
    motor.attach(TYPE_L293); //TYPE_SERVO, TYPE_L293
    motor.setSpeed(100,100);
    distance.attach(TYPE_LASER); // TYPE_NONE, TYPE_DIGITAL_DISTANCE, TYPE_ULTRASONIC, TYPE_LASER
}


void Explorer::robotLoop() {

  delay(1);

 if (distance.isCollision()){
    Serial.println("COLISION");
    motor.stop();
    delay(400);
    motor.backward();    
    delay(300);
    motor.stop();
    delay(400);
    
    int rnd = random(2);
    Serial.println(rnd);
    if (rnd == 1){
      motor.turnRightAxis();
      Serial.println("motor.turnRightAxis();");
    } else {
      motor.turnLeftAxis(); 
      Serial.println("motor.turnLeftAxis();");
    }

    int giro = random(300);
    
    delay(250 + giro);
    motor.stop();
    delay(1000);
  }
  else{
    motor.forward();
    delay(10);
    motor.stop();
    delay(1);    
  }
}
