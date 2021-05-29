#include <Servo.h>
#include <NewPing.h>
#define LEFT_SENSOR_PIN A2
#define RIGHT_SENSOR_PIN A3


//L293D
//Motor A
#define LEFT_MOTOR_PIN_1 5
#define LEFT_MOTOR_PIN_2 6
//Motor B
#define RIGHT_MOTOR_PIN_1 10
#define RIGHT_MOTOR_PIN_2 9

#define SENSOR_THRESHOLD 390

void LEFT (void);
void RIGHT(void);
void STOP (void);

short left_sensor;
short right_sensor;



#define BLACK  0
#define WHITE  1

#define TRIG_PIN A0 //analog input 1
#define ECHO_PIN A1 //analog input 2
#define MAX_DIST 200
int distance = 100;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);

void setup()
{

  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);

  pinMode(LEFT_MOTOR_PIN_1,OUTPUT);
  pinMode(LEFT_MOTOR_PIN_1,OUTPUT);
    
  pinMode(LEFT_MOTOR_PIN_1,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN_1,OUTPUT);
  pinMode(LEFT_MOTOR_PIN_2,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN_2,OUTPUT);


  pinMode(LEFT_SENSOR_PIN,INPUT);
  pinMode(RIGHT_SENSOR_PIN,INPUT);

  Serial.begin(9600);                   
  while (!Serial);
  BREAK();
 
  Serial.println("DUDU START!");

}
int readPing(){
  delay(7);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }

  return cm;
}


void readSensors() {
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

  distance = readPing();  


 }


void DoObstacle(){
      if (distance < 10){
          BREAK(); //Parar
          BACK(); //Ré
          delay(50);
          
          BREAK(); //Parar
 
          LEFT(); //Iniciar giro
          delay(600);
          //Girar
          while(true) {
            
            readSensors();
            
            if (right_sensor != BLACK) {
                break;
            }      
          }
    }
}


//0 = expectedRight
//1 = expectedLeft
//2 = nothing
int expected = 0;
    
void loop() 
{ 
    readSensors();
    DoObstacle();
    //DoServo(); //Opcional    
      
    if (left_sensor == BLACK && right_sensor == WHITE){
        Serial.println("left_sensor");
        expected = 1;
        RIGHT2();
    } else if (left_sensor == WHITE && right_sensor == BLACK)  {
        Serial.println("right_sensor");
        expected = 0;
        LEFT2();
     } else {
        Serial.println("FORWARD");
        if (expected == 1 && right_sensor == BLACK || expected == 0 && left_sensor == BLACK )  {
          expected = 2; 
        }        
        if (expected == 1) {
          RIGHT();
        } else if (expected == 0) {
          LEFT();          
        } else if (left_sensor == WHITE && right_sensor == WHITE)  {
          FORWARD();
        }                 
     }
}


void FORWARD() {   
    digitalWrite(LEFT_MOTOR_PIN_1, HIGH);
    digitalWrite(LEFT_MOTOR_PIN_2, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_2, HIGH); 
}

void BACK() {
    digitalWrite(LEFT_MOTOR_PIN_1, LOW);
    digitalWrite(LEFT_MOTOR_PIN_2, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN_1, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN_2, LOW);
}


void RIGHT2 (void)
{
    digitalWrite(LEFT_MOTOR_PIN_1, HIGH);
    digitalWrite(LEFT_MOTOR_PIN_2, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_2, LOW);
}

void RIGHT (void)
{
    digitalWrite(LEFT_MOTOR_PIN_1, HIGH);
    digitalWrite(LEFT_MOTOR_PIN_2, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_1, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN_2, LOW);
}


void LEFT2 (void)
{
    digitalWrite(LEFT_MOTOR_PIN_1, LOW);
    digitalWrite(LEFT_MOTOR_PIN_2, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_2, HIGH);

}

void LEFT (void)
{
    digitalWrite(LEFT_MOTOR_PIN_1, LOW);
    digitalWrite(LEFT_MOTOR_PIN_2, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_2, HIGH);

}
void STOP (void)
{
    digitalWrite(LEFT_MOTOR_PIN_1, LOW);
    digitalWrite(LEFT_MOTOR_PIN_2, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_2, LOW);
}

void BREAK (void)
{
    digitalWrite(LEFT_MOTOR_PIN_1, HIGH);
    digitalWrite(LEFT_MOTOR_PIN_2, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN_1, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN_2, HIGH);
}
