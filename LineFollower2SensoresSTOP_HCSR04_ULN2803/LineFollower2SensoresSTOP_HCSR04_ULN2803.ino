#include <Servo.h>

#define LEFT_SENSOR_PIN 11
#define RIGHT_SENSOR_PIN 12

//Motor A
#define LEFT_MOTOR_PIN 9

//Motor B
#define RIGHT_MOTOR_PIN 8


#define ADJ_PIN A0

#define BLACK  0
#define WHITE  1

#define TRIG_PIN 4
#define ECHO_PIN 2
#define BUZZ_PIN 6
#define MAX_DIST 200


void LEFT (void);
void RIGHT(void);
void STOP (void);

short left_sensor;
short right_sensor;
int distance = 100;


void setup()
{

  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);

  pinMode(A3,INPUT_PULLUP);

  pinMode(LEFT_MOTOR_PIN,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN,OUTPUT);
  pinMode(BUZZ_PIN,OUTPUT);

  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
 

  pinMode(LEFT_SENSOR_PIN,INPUT);
  pinMode(RIGHT_SENSOR_PIN,INPUT);

  Serial.begin(9600);                   
  while (!Serial);
  STOP();
 
  Serial.println("START BOT!");

}
int pingCm() 
{ 
    float temperatura = 19.307;
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    unsigned long durationus = pulseIn(ECHO_PIN, HIGH);

    double speedOfSoundInCmPerMs = 0.03313 + 0.0000606 * temperatura;
    double distanceCm = (durationus / 2.0 * speedOfSoundInCmPerMs);
    if (distanceCm == 0 || distanceCm > 400) {
        return -1.0 ;
    } else {
        return distanceCm;
    }

  return distanceCm;
}

void readSensors() {
    left_sensor = digitalRead(LEFT_SENSOR_PIN);
    right_sensor = digitalRead(RIGHT_SENSOR_PIN);    
    distance = pingCm();
}


void DoObstacle(){

 
      while (distance < 20){
          readSensors();
          delay(20);
          STOP(); //Parar
          int sensorVal = analogRead(ADJ_PIN); //Potenciometro com tempo do TOM
          if (sensorVal > 800) {
            sensorVal = sensorVal - 800;
          }
          Serial.print(sensorVal);
          Serial.print(" - ");
          Serial.println(distance);
          
          tone(BUZZ_PIN, 210);
          delay(sensorVal);
          tone(BUZZ_PIN, 220);
          delay(sensorVal);
          tone(BUZZ_PIN, 240);
          delay(sensorVal);
          tone(BUZZ_PIN, 260);
          delay(sensorVal);
          tone(BUZZ_PIN, 290);
          delay(sensorVal);
          noTone(BUZZ_PIN);
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
      
    if (left_sensor == BLACK && right_sensor == WHITE){
        Serial.println("left_sensor");
        expected = 1;
        //RIGHT();
    } else if (left_sensor == WHITE && right_sensor == BLACK)  {
        Serial.println("right_sensor");
        expected = 0;
        //LEFT();
    }
    
        Serial.println("FORWARD");
        if (expected == 1 && right_sensor == BLACK || expected == 0 && left_sensor == BLACK )  {
          //expected = 2; 
        }
        if (expected == 1) {
          RIGHT();
        } else if (expected == 0) {
          LEFT();          
        } else if (left_sensor == WHITE && right_sensor == WHITE)  {
          FORWARD();
        }                 
     
}

void FORWARD() {   
   digitalWrite(LEFT_MOTOR_PIN, HIGH);
   digitalWrite(RIGHT_MOTOR_PIN, HIGH); 
}

void RIGHT (void)
{
    digitalWrite(LEFT_MOTOR_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN,LOW);
}
void LEFT (void)
{
    digitalWrite(LEFT_MOTOR_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_PIN, HIGH);
}
void STOP (void)
{
    digitalWrite(LEFT_MOTOR_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_PIN, LOW);
}
