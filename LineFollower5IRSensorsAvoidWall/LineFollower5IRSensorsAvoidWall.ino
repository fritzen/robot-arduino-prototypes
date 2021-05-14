#include <NewPing.h>
#include "TimerFreeTone.h" 

#define LeftMotorPin1  2
#define LeftMotorPin2  3
#define RightMotorPin1 4
#define RightMotorPin2 5

#define SENSOR_PIN_1 6
#define SENSOR_PIN_2 7
#define SENSOR_PIN_CENTER 8
#define SENSOR_PIN_3 9
#define SENSOR_PIN_4 10
#define SENSOR_PIN_WALL  11


#define TONE_PIN 13

#define BLACK  0

#define TRIG_PIN A1 //analog input 1
#define ECHO_PIN A2 //analog input 2
#define MAX_DIST 200
int distance = 100;

bool centralizingLeft = false;
bool centralizingRight = false;

int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int duration[] = { 250, 125, 125, 250, 250, 250, 250, 250 };

int countSteps = 0;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);


short IR1, IR2, IR3, IR4, IR_CENTER, WALL_BUTTON; // sensor values


void setup()
{  


    pinMode(SENSOR_PIN_1,INPUT); 
    pinMode(SENSOR_PIN_2,INPUT);
    pinMode(SENSOR_PIN_3,INPUT);
    pinMode(SENSOR_PIN_4,INPUT);
    pinMode(SENSOR_PIN_WALL,INPUT);
    pinMode(SENSOR_PIN_CENTER,INPUT);
    pinMode(TONE_PIN,OUTPUT);
    pinMode(12,OUTPUT);

    digitalWrite(12,OUTPUT);

    
    Serial.begin(9600);                   
    while (!Serial);
    off();
    song();
    delay(1000);
    Serial.println("START!");

}

void song() {
  for (int thisNote = 0; thisNote < 8; thisNote++) { 
    TimerFreeTone(TONE_PIN, melody[thisNote], duration[thisNote]); 
    delay(50); 
  }
}


void mode1() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,HIGH);  
}

void mode2() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,LOW);  
}


void mode3() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,LOW);  
}


void mode4() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,HIGH);  
}


void mode5() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);  
}

void mode6() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);  
}

void mode7() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);  
}
void mode8() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);  
}


void off() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,LOW);        
}

void forward() {
    Serial.print("forwards");
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);  
}

void back() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);  
}

void left() {
    Serial.print("left");
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);    
}


void left2() {
    Serial.print("left");
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,LOW);
}


void right() {
    Serial.print("right");
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);
}


void right2() {
    Serial.print("right");
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);
}


int readPing(){
  delay(7);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  Serial.print(cm);
  Serial.print(" cm");
  return cm;
}


void readSensors() 
{ 
    
    IR1 = digitalRead(SENSOR_PIN_1);
    IR2 = digitalRead(SENSOR_PIN_2); //center
    IR3 = digitalRead(SENSOR_PIN_3); //center
    IR4 = digitalRead(SENSOR_PIN_4);

    WALL_BUTTON = digitalRead(SENSOR_PIN_WALL);
    IR_CENTER = digitalRead(SENSOR_PIN_CENTER);

    Serial.print(IR1);
    Serial.print("-");
    Serial.print(IR2);
    Serial.print("-");
    Serial.print(IR3);
    Serial.print("-");
    Serial.print(IR4);
    Serial.print("-");
    Serial.print(IR_CENTER);
    Serial.print("-");
    Serial.print(WALL_BUTTON);  

    distance = readPing();
}

void loop() 
{ 
    readSensors();
        //
    if (WALL_BUTTON == 1 || distance < 6){
      off(); //Parar
      song(); //com Delay interno
      back(); //Ré
      delay(500);
      left(); //Iniciar giro
      delay(600);

      //Girar até achar IR2 ou IR3
      while(true) {
        
        readSensors();
        
        if (IR_CENTER == BLACK || IR2 == BLACK || IR3 == BLACK) {
            centralizingLeft = false;
            centralizingRight = false;
            break;
        }      
      }
    }
    
    if (centralizingLeft || centralizingRight) {
      countSteps++;
      if (centralizingLeft  && (IR3 == BLACK || IR4 == BLACK)  ||
          centralizingRight && (IR1 == BLACK || IR2 == BLACK) || 
          IR_CENTER == BLACK){
          centralizingLeft = false;
          centralizingRight = false;
      } else if (centralizingLeft) {
        if (countSteps > 10) {
          left();  
          countSteps = 0;
        } else {
          left2();
          delay(1);
        }
        
      } else if (centralizingRight) {
        if (countSteps > 10) {
          right();
          delay(1);
          countSteps = 0;
        } else {
          right2();
          delay(1);
        }
      }
    } else {
        if (IR1 == BLACK || IR2 == BLACK ) {
           centralizingLeft = true;
           centralizingRight = false;
           left2();
        } else if (IR3 == BLACK || IR4 == BLACK) {
            centralizingLeft = false;
            centralizingRight = true;
            right2();
        } else {
            forward();
            if (IR_CENTER == BLACK) {
              delay(50);
            }
            
        }
    }

     Serial.println("*");
}
