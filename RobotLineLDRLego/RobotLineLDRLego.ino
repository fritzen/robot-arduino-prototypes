#include <Servo.h>




Servo servoWheel;  // create servo object to control a servo
 
//ANALOGS 6, 9, 10, and 11.

// RGULADO PARA LUZ INDOR
#define THRESHOLD_LDR1 220 //LIGHT LDR Reflection
#define THRESHOLD_LDR2 240 //LIGHT LDR Reflection
#define THRESHOLD_LDR3 150 //LIGHT LDR Reflection
#define MOTOR_PIN  6
#define MAX_SPEED 220
#define START_SPEED 180

bool centralizing = false;

bool expectedLeft = false;
bool expectedRight = false;

short lastChoice = 0;

int motorSpeed = 0;


int contador = 0;

int cntMotor = 0;

void setup()
{
    Serial.begin(9600);

    Serial.println("begin");
    
    pinMode(MOTOR_PIN, OUTPUT);   // sets the pin as output
    
    motorSpeed = START_SPEED;
 
    servoWheel.attach(10);
    servoWheel.write(90);
   
}


void forward() {
    servoWheel.write(90);
    Serial.println("forward");


}

void right() {
    servoWheel.write(120);
    Serial.println("right");
}


void left() {
    servoWheel.write(60);
    Serial.println("left");
}



void loop() 
{ 
  
    short IR1, IR2, IR3; // sensor values
    
    IR1 = analogRead(A0);
    IR2 = analogRead(A1); //center
    IR3 = analogRead(A2);
    
    if (IR1 > THRESHOLD_LDR1) IR1 = 1; else IR1 = 0;
    if (IR2 > THRESHOLD_LDR2) IR2 = 1; else IR2 = 0;
    if (IR3 > THRESHOLD_LDR3) IR3 = 1; else IR3 = 0;

    
   
   if (centralizing) {
      if (IR2 == 1) {
          motorSpeed = START_SPEED;
          centralizing = false;
       }
    } else {
        if (IR1 == 1 ) {
            motorSpeed = START_SPEED;
            centralizing = true;
            lastChoice = 1;
            left();
        } else if (IR3 == 1) {
            motorSpeed = START_SPEED;
            centralizing = true;
            lastChoice = 2;  
            right();
        } else {
            lastChoice = 3;
            forward();
        }
    }

    if (lastChoice == 1) {
      left();
    }

    if (lastChoice == 2) {
      right();
    }

    contador++;

    if (contador > 20) {

        motorSpeed++;     
        if (motorSpeed > MAX_SPEED) {
            motorSpeed = START_SPEED;
        }
        
        contador=0;

      }

      analogWrite(MOTOR_PIN,motorSpeed);


    Serial.println(motorSpeed);

    
}






