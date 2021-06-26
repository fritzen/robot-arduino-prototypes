#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name

Servo myservo1;
Servo myservo2;
void setup(){

  Serial.begin(9600);

  servo_motor.attach(10); //our servo pin
    
  myservo1.attach(9);
  myservo2.attach(11);
  
  servo_motor.write(115);
  delay(400);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

  randomSeed(analogRead(0));
  
  Serial.begin(9600);  
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
 // Serial.println(cm);  
  
  return cm;
}




void moveStop(){
  myservo1.write(90);
  myservo2.write(90);
    
  myservo1.detach();
  myservo2.detach();
}
long cntlong;
void moveForward(){

  cntlong++;
  delay(1);    
  Serial.println(cntlong);
  
  //if(!goesForward){

    goesForward=true;
  
    myservo1.attach(9);
    myservo2.attach(11);
      
    myservo1.write(104);   //104=frente //99 =stop

    //zigzag
    if (cntlong > 15) {
      myservo2.write(87);
      if (cntlong > 30) {
        cntlong = 0;
      }
    } else {
      myservo2.write(86);
    }
    
    
  //}
}

void moveBackward(){


  myservo1.attach(9);
  myservo2.attach(11);
  
  goesForward=false;

  myservo1.write(0);
  myservo2.write(180);
  
}

void turnRight(){


  myservo1.attach(9);
  myservo2.attach(11);
  
  myservo1.write(180);
  myservo2.write(180); 
 
  delay(500);
  
}

void turnLeft(){


  myservo1.attach(9);
  myservo2.attach(11);
  
  myservo1.write(0);
  myservo2.write(0);

  delay(500);
  

}
