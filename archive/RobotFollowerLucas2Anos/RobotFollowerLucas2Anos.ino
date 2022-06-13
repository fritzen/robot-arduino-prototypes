#include "display.h"
#include <Servo.h>

DisplayMatrix displayMatrix;


//PINS

#define DISPLAYNAME "LUCAS"
#define PWMPin1        13
#define PWMPin2        12

#define LeftMotorPin1  31
#define LeftMotorPin2  33

#define RightMotorPin1 35
#define RightMotorPin2 37

#define AnalogInputPin A15

#define High5VPin1 50
#define High5VPin2 51
#define High5VPin3 52
#define High5VPin4 53


#define ServoPWMPin1  11
#define ServoPWMPin2  9


//Constantes
#define FORWARD 1
#define BACKWARD 2

#define LEFT  1
#define RIGHT 2

#define MaxServo1 120
#define MinServo1 0

#define MaxServo2 120
#define MinServo2 50

const long interval = 200;           // interval in mudei pra micros

bool centralizando = false;

int currentSpeed = 150;

unsigned long previousMillis = 0;        // will store last time LED MATRIX was updated

int maxSmile = 8000;  
int smile = 0;  
bool smiling = false;      

Servo myservo1;
Servo myservo2;

void setup()
{

 myservo1.attach(ServoPWMPin1);
 myservo2.attach(ServoPWMPin2);

 servos();


  myservo1.detach();
  myservo2.detach();



 // 5v IR
 pinMode(High5VPin1,OUTPUT); 
 pinMode(High5VPin2,OUTPUT); 
 pinMode(High5VPin3,OUTPUT); 
 pinMode(High5VPin4,OUTPUT); 
 
 digitalWrite(High5VPin1,HIGH);
 digitalWrite(High5VPin2,HIGH);
 digitalWrite(High5VPin3,HIGH);
 digitalWrite(High5VPin4,HIGH);

 

 pinMode(AnalogInputPin, INPUT);



 pinMode(PWMPin1,OUTPUT); //PWM Pin 1
 pinMode(PWMPin2,OUTPUT); //PWM Pin 2
 
 pinMode(LeftMotorPin1,OUTPUT); //Left Motor Pin 1
 pinMode(LeftMotorPin2,OUTPUT); //Left Motor Pin 2
 
 pinMode(RightMotorPin1,OUTPUT); //Right Motor Pin 1
 pinMode(RightMotorPin2,OUTPUT);  //Right Motor Pin 2


 displayMatrix.SetText(DISPLAYNAME);


}


void callback() {

  if (smiling) {
      displayMatrix.ShowSmile();
  } else {
      displayMatrix.UpdateMatrix();
  }
  smile++;
  if (smile > maxSmile) {
    smile = 0;
    smiling = !smiling;
  }

  
}


String float2str(float floatVal) {
  

  char charVal[7];               //temporarily holds data from vals 
  String stringVal = "";     //data on buff is copied to this string
  
  dtostrf(floatVal, 4, 2, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff


  for(int i=0;i<sizeof(charVal);i++)
  {
    stringVal+=charVal[i];
  }

  return stringVal;
  
}


void motor(short dir, short lado, short speed) {

    if (lado == LEFT) {
      if (dir == FORWARD) {
          digitalWrite(LeftMotorPin1,HIGH);
          digitalWrite(LeftMotorPin2,LOW);
        } else {
          digitalWrite(LeftMotorPin1,LOW);
          digitalWrite(LeftMotorPin2,HIGH);
        }
        analogWrite(PWMPin1,speed);
    }
    
    if (lado == RIGHT) {
      if (dir == FORWARD) {
            digitalWrite(RightMotorPin1,LOW);
            digitalWrite(RightMotorPin2,HIGH);
        } else {
            digitalWrite(RightMotorPin1,HIGH);
            digitalWrite(RightMotorPin2,LOW);
        }
        analogWrite(PWMPin2,speed);
    }    
  
}


void servos() {

/** Brincar com os servos na inicialização */

int servo1Pos = 90;
int servo2Pos = 90;

myservo1.write(servo1Pos);
delay(300);
myservo2.write(servo2Pos);
delay(300);


bool servo1Soma = false;
bool servo2Soma = true;

for (int x = 2; x < 410; x++) {
if (servo1Soma) {
  servo1Pos++; 
} else {
  servo1Pos--; 
}
if (servo2Soma) {
  servo2Pos++;
} else {
  servo2Pos--;
}


if (servo1Pos <= MinServo1) {
    servo1Soma = true;
}
if (servo1Pos >= MaxServo1) {
  servo1Soma = false;
}


if (servo2Pos <= MinServo2) {
    servo2Soma = true;
}
if (servo2Pos >= MaxServo2) {
  servo2Soma = false;
}

 
myservo1.write(servo1Pos);
delay(10);
myservo2.write(servo2Pos);
delay(10);
  }
}


void loop() 
{ 
   /** NAO USAR delay() no loop() !!! Faca com callback para nao atrapalhar o display **/
   unsigned long currentMillis =  micros();

  if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        callback();
  }


short IR1, IR2, IR3; // sensor values


IR1 = digitalRead(A0);
IR2 = digitalRead(A1); //center
IR3 = digitalRead(A2);


if (centralizando) {

  if (IR2 == 1) {
    
    centralizando = false;
    
    
    }
  
} else {

    if (IR1 == 0 && IR2 == 1 && IR3 == 0){
        motor(FORWARD, LEFT, currentSpeed - 10);
        motor(FORWARD, RIGHT, currentSpeed - 10);
     }


    if (IR1 == 1) {
        motor(BACKWARD, LEFT, currentSpeed); 
        motor(FORWARD, RIGHT, currentSpeed); 
        
        centralizando = true;
    } 
    
    if (IR3 == 1 ) {
       motor(FORWARD, LEFT, currentSpeed);
       motor(BACKWARD, RIGHT, currentSpeed);
        
      centralizando = true;
    }
    

}

}






