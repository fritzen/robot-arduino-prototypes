#include "LineFollower.h"
#include "src/FioMotorDriver.h"
#include "src/FioSensorDistance.h"
#include "src/TimerFreeTone.h"

#ifdef LineFollower2IR_h


void LineFollower::robotSetup() {
    pinMode(LEFT_SENSOR_PIN,INPUT_PULLUP);
    pinMode(RIGHT_SENSOR_PIN,INPUT_PULLUP);
    motor.attach(TYPE_L293); //TYPE_SERVO, TYPE_L293
//    distance.attach(TYPE_NONE); // TYPE_NONE, TYPE_DIGITAL_DISTANCE, TYPE_ULTRASONIC, TYPE_LASER
//      int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
//      int duration[] = { 250, 125, 125, 250, 250, 250, 250, 250 };
//      for (int thisNote = 0; thisNote < 8; thisNote++) { // Loop through the notes in the array.
//        TimerFreeTone(DEFAULT_TONE_PIN, melody[thisNote], duration[thisNote]); // Play thisNote for duration.
//        delay(50); // Short delay between notes.
//      }
}


void LineFollower::readLineFollowerSensors() {
  
     left_sensor = analogRead(LEFT_SENSOR_PIN);
     right_sensor = analogRead(RIGHT_SENSOR_PIN);
    
     Serial.print(left_sensor);
     Serial.print("x");
     Serial.print(right_sensor); 
     Serial.print("*");

    if (left_sensor < SENSOR_THRESHOLD) {
      left_sensor = BLACK;
    } else {
      left_sensor = WHITE;
    }

    if (right_sensor < SENSOR_THRESHOLD) {
      right_sensor = BLACK;
    } else {
      right_sensor = WHITE;
    }     
 }

void LineFollower::doLineFollowerObstacle(){
      if (distance.isCollision()){
          Serial.print("COLISION"); 
          motor.stop(); //Parar
          motor.backward(); //Ré
          //song();
          delay(200);           
          motor.stop(); //Parar          
          motor.turnLeftAxis(); //Iniciar giro no próprio eixo          
          delay(500);
          //Girar
          while(true) {            
            readLineFollowerSensors();            
            if (right_sensor != BLACK) {
                break;
            }      
          }
    }
}


void LineFollower::robotLoop() {
	  readLineFollowerSensors();
    doLineFollowerObstacle();      
    if (left_sensor == BLACK && right_sensor == WHITE){
        lastDIR = 1;
    } else if (left_sensor == WHITE && right_sensor == BLACK)  {
        lastDIR = 2;
    }

    if (lastDIR == 1) {
        motor.turnRight();
    } else if (lastDIR == 2) {
        motor.turnLeft();
    } else {
        motor.forward();
    }
    Serial.println(";");
}
#endif
