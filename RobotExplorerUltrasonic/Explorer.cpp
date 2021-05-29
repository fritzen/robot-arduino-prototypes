#include "Explorer.h"


void Explorer::robotSetup() {
    motor.attach(TYPE_L293); //TYPE_SERVO, TYPE_L293
    motor.setSpeed(210,165);
    distance.attach(TYPE_ULTRASONIC); // TYPE_NONE, TYPE_DIGITAL_DISTANCE, TYPE_ULTRASONIC, TYPE_LASER
}


void Explorer::robotLoop() {

 if (distance.isCollision()){
    Serial.println("COLISION");
    motor.stop();
    delay(20);
    motor.backward();    
    delay(300);
    motor.stop();
    delay(20);
       
    int rnd = random(2);

    if (rnd == 1){
      motor.turnRightAxis();
      Serial.println("motor.turnRightAxis();");
    } else {
      motor.turnLeftAxis(); 
      Serial.println("motor.turnLeftAxis();");
    }
    
    delay(300);
    int tentativas = 0;
    while (distance.isCollision()){   
      delay(1);
      Serial.println("COLISION RETRY");
      tentativas++;
      if (tentativas > 10) {
        break;
      }
    }
  }
  else{
    motor.forward();
    delay(50);
    motor.stop();
    delay(30);
  }

}
