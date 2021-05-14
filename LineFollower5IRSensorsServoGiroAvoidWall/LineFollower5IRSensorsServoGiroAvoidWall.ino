#include <Servo.h>
#include <NewPing.h>
#include "TimerFreeTone.h" 

Servo myservo1;
Servo myservo2;
Servo myservo3;


#define MONTOR_1_PIN 2
#define MONTOR_2_PIN 3
#define SENSOR_PIN_POWER 4

#define TONE_PIN 11

#define SENSOR_PIN_1 5
#define SENSOR_PIN_2 6
#define SENSOR_PIN_CENTER 7
#define SENSOR_PIN_3 8
#define SENSOR_PIN_4 9
#define SENSOR_PIN_WALL  10

#define SERVO_SENSOR_PIN 13

#define SERVO_CENTER_POS 68


#define BLACK  0

#define TRIG_PIN A1 //analog input 1
#define ECHO_PIN A2 //analog input 2
#define MAX_DIST 200
int distance = 100;

bool centralizingLeft = false;
bool centralizingRight = false;

int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int duration[] = { 250, 125, 125, 250, 250, 250, 250, 250 };

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);


short IR1, IR2, IR3, IR4, IR_CENTER, WALL_BUTTON; // sensor values


void setup()
{

    myservo1.attach(MONTOR_1_PIN);
    myservo2.attach(MONTOR_2_PIN);
      
    myservo3.attach(SERVO_SENSOR_PIN);
  
    pinMode(SENSOR_PIN_POWER,OUTPUT); 
    digitalWrite(SENSOR_PIN_POWER,HIGH);

    pinMode(SENSOR_PIN_1,INPUT); 
    pinMode(SENSOR_PIN_2,INPUT);
    pinMode(SENSOR_PIN_3,INPUT);
    pinMode(SENSOR_PIN_4,INPUT);
    pinMode(SENSOR_PIN_WALL,INPUT);
    pinMode(SENSOR_PIN_CENTER,INPUT);
    pinMode(TONE_PIN,OUTPUT);

    Serial.begin(9600);                   
    while (!Serial);
    myservo3.write(SERVO_CENTER_POS);
    off();
    song();
    delay(1000);
    Serial.println("START!");

}

void song() {
  for (int thisNote = 0; thisNote < 8; thisNote++) { // Loop through the notes in the array.
    TimerFreeTone(TONE_PIN, melody[thisNote], duration[thisNote]); // Play thisNote for duration.
    delay(50); // Short delay between notes.
  }
}

void off() {
    myservo1.write(95);    // Zero Ajustado empiricamente
    myservo2.write(42);    // Zero Ajustado empiricamente
}

void forward() {
    Serial.print("forwards");
    myservo1.write(180);   
    myservo2.write(0);
}

void back() {
  myservo1.write(0);
  myservo2.write(180);
}

void right() {
    Serial.print("right");
    myservo1.write(180);
    myservo2.write(180);     
}


void left() {
    Serial.print("left");
    myservo1.write(0);
    myservo2.write(0);
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
      if (centralizingLeft  && (IR3 == BLACK || IR4 == BLACK)  ||
          centralizingRight && (IR1 == BLACK || IR2 == BLACK)  || 
          IR_CENTER == BLACK ){
          centralizingLeft = false;
          centralizingRight = false;
          forward();
          myservo3.write(SERVO_CENTER_POS);
          delay(100);
      }
    } else {
        if (IR1 == BLACK || IR2 == BLACK ) {
           centralizingLeft = true;
           centralizingRight = false;
           left();
           myservo3.write(SERVO_CENTER_POS + 50);
        } else if (IR3 == BLACK || IR4 == BLACK) {
            centralizingLeft = false;
            centralizingRight = true;
            right();
            myservo3.write(SERVO_CENTER_POS - 50);
        } else {
            forward();
        }
    }

     Serial.println("*");
}
