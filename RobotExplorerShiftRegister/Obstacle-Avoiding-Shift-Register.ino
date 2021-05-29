#include <VL53L0X.h>
#include <Wire.h>

const int buzzer = 2; //Constante armazenando o número do pino que vamos utilizar

const int LeftMotorForward = 9;
const int LeftMotorBackward = 8;
const int RightMotorForward = 11;
const int RightMotorBackward = 10;


VL53L0X sensor;

int latchPin = 5;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 6; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 4;  // Data pin of 74HC595 is connected to Digital pin 4

byte leds = 0;    // Variable to hold the pattern of which LEDs are currently turned on or off

#define LEFT_SENSOR_PIN 2
#define RIGHT_SENSOR_PIN 3

short left_sensor;
short right_sensor;

int distance = 100;

void setup() 
{
  
  Serial.begin(9600);

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(buzzer,OUTPUT);

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  Wire.begin();

  Serial.println("INIT");

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1)
    {
    }
  }

  sensor.startContinuous();

}

int countLeds = 0;

void loop() 
{
  distance = sensor.readRangeContinuousMillimeters();
  Serial.println(distance);
  if (sensor.timeoutOccurred())
  {
    Serial.print(" TIMEOUT");
  }
  
  if (distance <= 100){
    moveStop();
    tone(buzzer,1500);  
    delay(1000);
    noTone(buzzer);

    moveBackward();
    delay(200);
    moveStop();
    delay(200);
    turnRight();
    delay(270);
    moveStop();
    delay(200);
  }
  else{
    tone(buzzer,1500);  
    moveForward();
    delay(8);
  }
  

  leds = 0; 
  updateShiftRegister();
  
  countLeds++;

  if (countLeds > 15) {
    countLeds = 0;
  }  
  bitSet(leds, countLeds); 
  updateShiftRegister();

  moveStop();  
  delay(1);
  noTone(buzzer);

}


void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}



void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 

}

void moveBackward(){


  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRight(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
 
  
  
}

void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
