#include "ExplorerStepper.h"


void ExplorerStepper::robotSetup() {
    motor.attach(TYPE_L293); //TYPE_SERVO, TYPE_L293
    motor.setSpeed(210,165);
    distance.attach(TYPE_ULTRASONIC); // TYPE_NONE, TYPE_DIGITAL_DISTANCE, TYPE_ULTRASONIC, TYPE_LASER


    pinMode(IN1, OUTPUT); 
    pinMode(IN2, OUTPUT); 
    pinMode(IN3, OUTPUT); 
    pinMode(IN4, OUTPUT); 
}


void ExplorerStepper::robotLoop() {
  
  currentMillis = micros();
  if(currentMillis-last_time>=5000){
      stepper(50); 
      time=time+micros()-last_time;
      last_time=micros();
      steps_left--;
  }

  if (steps_left == 0) {
    Direction=!Direction;
    steps_left=500;
  }

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
    delay(5);
    motor.stop();
    delay(1);
  }

}

void ExplorerStepper::stepper(int xw){
  for (int x=0;x<xw;x++){
      switch(Steps){
         case 0:
           digitalWrite(IN1, LOW); 
           digitalWrite(IN2, LOW);
           digitalWrite(IN3, LOW);
           digitalWrite(IN4, HIGH);
         break; 
         case 1:
           digitalWrite(IN1, LOW); 
           digitalWrite(IN2, LOW);
           digitalWrite(IN3, HIGH);
           digitalWrite(IN4, HIGH);
         break; 
         case 2:
           digitalWrite(IN1, LOW); 
           digitalWrite(IN2, LOW);
           digitalWrite(IN3, HIGH);
           digitalWrite(IN4, LOW);
         break; 
         case 3:
           digitalWrite(IN1, LOW); 
           digitalWrite(IN2, HIGH);
           digitalWrite(IN3, HIGH);
           digitalWrite(IN4, LOW);
         break; 
         case 4:
           digitalWrite(IN1, LOW); 
           digitalWrite(IN2, HIGH);
           digitalWrite(IN3, LOW);
           digitalWrite(IN4, LOW);
         break; 
         case 5:
           digitalWrite(IN1, HIGH); 
           digitalWrite(IN2, HIGH);
           digitalWrite(IN3, LOW);
           digitalWrite(IN4, LOW);
         break; 
           case 6:
           digitalWrite(IN1, HIGH); 
           digitalWrite(IN2, LOW);
           digitalWrite(IN3, LOW);
           digitalWrite(IN4, LOW);
         break; 
         case 7:
           digitalWrite(IN1, HIGH); 
           digitalWrite(IN2, LOW);
           digitalWrite(IN3, LOW);
           digitalWrite(IN4, HIGH);
         break; 
         default:
           digitalWrite(IN1, LOW); 
           digitalWrite(IN2, LOW);
           digitalWrite(IN3, LOW);
           digitalWrite(IN4, LOW);
         break; 
      }
    setDirection();
  }
} 

void ExplorerStepper::setDirection(){
  if(Direction==1){ Steps++;}
  if(Direction==0){ Steps--; }
  if(Steps>7){Steps=0;}
  if(Steps<0){Steps=7; }
}
