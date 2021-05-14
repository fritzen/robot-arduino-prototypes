#include <Servo.h>
#include <NewPing.h>


#define SENSOR_LDR_PIN A2
#define SENSOR_A_PIN A4
#define SENSOR_B_PIN A3


//L293D
//Motor A
#define LEFT_MOTOR_PIN_1 5
#define LEFT_MOTOR_PIN_2 6
//Motor B
#define RIGHT_MOTOR_PIN_1 10
#define RIGHT_MOTOR_PIN_2 9

#define FLOWER_PIN 3

#define SENSOR_THRESHOLD 520

void LEFT (void);
void RIGHT(void);
void STOP (void);

short sensor_ldr;
short sensor_a;
short sensor_b;

//LDR dinâmico: aprende de acordo com a luminosidade do ambiente
int min_ldr = 5000;
int max_ldr = 0;


#define SERVO_SENSOR_PIN 2
#define SERVO_CENTER_POS 68

#define LED_MEIO_PIN 8

#define BLACK  0
#define WHITE  1

#define TRIG_PIN A0 //analog input 1
#define ECHO_PIN A1 //analog input 2
#define MAX_DIST 200

Servo myservo3;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);

int distance = 250;

void setup()
{
  myservo3.attach(SERVO_SENSOR_PIN);

  pinMode(LEFT_MOTOR_PIN_1,OUTPUT);
  pinMode(LEFT_MOTOR_PIN_1,OUTPUT);
    
  pinMode(LEFT_MOTOR_PIN_1,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN_1,OUTPUT);
  pinMode(LEFT_MOTOR_PIN_2,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN_2,OUTPUT);

  pinMode(FLOWER_PIN,OUTPUT);

  pinMode(LED_MEIO_PIN,OUTPUT);

  
  pinMode(SENSOR_LDR_PIN,INPUT_PULLUP);
  pinMode(SENSOR_A_PIN,INPUT_PULLUP);
  pinMode(SENSOR_B_PIN,INPUT_PULLUP);
  

  Serial.begin(9600);                   
  while (!Serial);
  myservo3.write(SERVO_CENTER_POS);
  BREAK();

  Serial.println("START!");


}

unsigned long millisTarefa1 = millis();

bool doPing = false;

void readPing(){


  if((millis() - millisTarefa1) < 20){        
      doPing = true; //wait for ping      
  } else {
    if (doPing) {
      doPing = false;
      distance = sonar.ping_cm();
      if (distance==0){
        distance=250;
      }
    }      
  }
  // Verifica se já passou 400 milisegundos
  if((millis() - millisTarefa1) > 100){
    millisTarefa1 = millis();
  }
}

void readSensors() {
    sensor_ldr = analogRead(SENSOR_LDR_PIN);
    sensor_a = analogRead(SENSOR_A_PIN);
    sensor_b = analogRead(SENSOR_B_PIN);
    Serial.print(sensor_a);
    Serial.print("*");
    Serial.print(sensor_b);
    Serial.print("*");
    Serial.print(sensor_ldr);     
    Serial.print("*");

    if (sensor_ldr < min_ldr){
      min_ldr = sensor_ldr;
    }

    if (sensor_ldr > max_ldr){
      max_ldr = sensor_ldr;
    }

    int mean_ldr = (min_ldr + max_ldr) / 2;

    if (sensor_ldr > mean_ldr) {
      sensor_ldr = WHITE;
    } else {
      sensor_ldr = BLACK;
    }


    if (sensor_a < SENSOR_THRESHOLD) {
      sensor_a = WHITE;
    } else {
      sensor_a = BLACK;
    }


    if (sensor_b < SENSOR_THRESHOLD) {
      sensor_b = WHITE;
    } else {
      sensor_b = BLACK;
    }
    readPing();
 


     Serial.print(distance);      
     Serial.println("*");
  
 }


void DoObstacle(){
      if (distance <= 10){
          Serial.println("DoObstacle");
          BREAK(); //Parar

          
          for (size_t i = 0; i < 50; i++)
          {
            DoServo();
            delay(20);
          }

          digitalWrite(FLOWER_PIN, HIGH);         
          delay(200);
          digitalWrite(FLOWER_PIN, LOW); 
          
          BACK(); //Ré

          delay(350);
          
          BREAK(); //Parar
                    
          myservo3.write(SERVO_CENTER_POS);
          delay(300);
          
          digitalWrite(FLOWER_PIN, HIGH);    
          LEFT(); //Iniciar giro
          delay(600);
          digitalWrite(FLOWER_PIN, LOW); 
        
          while(true) {
            
            readSensors(); //parar giro quando encontrar sensor_b
            
            if (sensor_b == BLACK) {
                break;
            }
          }
    }
}

int servoPos = SERVO_CENTER_POS;
bool servoSomando = true;

void DoServo(){
    if (servoSomando) {
      servoPos+=5;
    } else {
      servoPos-=5;
    }
    if (servoPos > SERVO_CENTER_POS + 20)
    {
      servoSomando = false;
    } 
    if (servoPos < SERVO_CENTER_POS - 20)
    {
      servoSomando = true;
    } 
     myservo3.write(servoPos);
}

  
void loop() 
{ 
    readSensors();
    DoObstacle();    

    if (sensor_a == BLACK) {
      LEFT2();
    } else if (sensor_b == BLACK) {            
      RIGHT2();
    }  

    if (sensor_ldr != BLACK) {
        digitalWrite(LED_MEIO_PIN, HIGH);
    } else {
      digitalWrite(LED_MEIO_PIN, LOW);
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
