//PINS
#include <Servo.h>

//[0] = Número de passos e [1] direção (0= esquerda, 1 = centro e 2 = direira
int comandos[9][2] = {{20, 1}, {20, 0}, {10, 2},{20, 1}, {20, 0}, {10, 2},{20, 1}, {20, 0}, {10, 2}};

#define MotorPin  5

#define LEFT_SERVO_POS 30
#define CENTER_SERVO_POS 65
#define RIGHT_SERVO_POS 100

#define MOTOR_SPEED 255



#define THRESHOLD_LIGHT 400


int sensorPin = A5;  
int sensorValue = 0; 
bool mudou = false;
bool waitForChange = false;

short i = 0;

short currentSteps = 0;
short currentDirection = 1;

short giros = 0;

Servo myservo;  // create servo object to control a servo

void setup()
{

    pinMode(MotorPin, OUTPUT);   // sets the pin as output
    analogWrite(MotorPin,MOTOR_SPEED);
    
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    
    
    Serial.begin(9600);
  
    currentSteps = comandos[i][0];
    currentDirection = comandos[i][1];
    
    SetDirection();
}


void SetDirection() {

  
  Serial.print(" COMANDO ");
  Serial.println(currentDirection);
  
              
  if (currentDirection == 0) {
    left();
  } 

  if (currentDirection == 1) {
    forward();
  } 

  if (currentDirection == 2) {
    right();
  } 
}

void forward() {
    myservo.write(CENTER_SERVO_POS);
}

void right() {
    myservo.write(RIGHT_SERVO_POS);
}


void left() {
    myservo.write(LEFT_SERVO_POS);
}


void loop() 
{  
     // read the value from the sensor:
      sensorValue = analogRead(sensorPin);
    
      if (sensorValue > THRESHOLD_LIGHT && waitForChange == false) {
        mudou = true;
    
      } else if (sensorValue <= THRESHOLD_LIGHT && waitForChange == true) {
        waitForChange = false;
      }
  
      if (mudou && waitForChange == false) {
          mudou = false;
          waitForChange = true;
          Serial.println("GIROU 1 (uma) volta ");
          
          giros++;

          if (giros >= currentSteps) {
              giros = 0;
              i++;
              currentSteps = comandos[i][0];
              currentDirection = comandos[i][1];
              SetDirection();
          }

      }
}






