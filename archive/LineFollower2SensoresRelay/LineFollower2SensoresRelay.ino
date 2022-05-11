#include <Servo.h>

#define LEFT_SENSOR_PIN 11
#define RIGHT_SENSOR_PIN 12

//Motor A
#define RELAY_PIN 2


#define BLACK  0
#define WHITE  1

#define TRIG_PIN 4
#define ECHO_PIN 2


void LEFT (void);
void RIGHT(void);

short left_sensor;
short right_sensor;
int distance = 100;


void setup()
{


  pinMode(RELAY_PIN,OUTPUT);

 

  pinMode(LEFT_SENSOR_PIN,INPUT);
  pinMode(RIGHT_SENSOR_PIN,INPUT);

  Serial.begin(9600);                   
  while (!Serial);
 
  Serial.println("START BOT!");

}

void readSensors() {
    left_sensor = digitalRead(LEFT_SENSOR_PIN);
    right_sensor = digitalRead(RIGHT_SENSOR_PIN);    
}



//0 = expectedRight
//1 = expectedLeft
//2 = nothing
int expected = 0;
    
void loop() 
{ 
    readSensors();
      
    if (left_sensor == BLACK && right_sensor == WHITE){
        Serial.println("left_sensor");
        expected = 1;
    } else if (left_sensor == WHITE && right_sensor == BLACK)  {
        Serial.println("right_sensor");
        expected = 0;
    }
    
    if (expected == 1) {
      RIGHT();
    } else if (expected == 0) {
      LEFT();          
    }                 
     
}

void RIGHT (void)
{
    digitalWrite(RELAY_PIN, HIGH);
}
void LEFT (void)
{
    digitalWrite(RELAY_PIN, LOW);
}
