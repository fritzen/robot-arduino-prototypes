#define LEFT_SENSOR_PIN A1  
#define RIGHT_SENSOR_PIN A0

#define LEFT_MOTOR_PIN 5  //PORTA PWM
#define RIGHT_MOTOR_PIN 6 //PORTA PWM

#define MOTOR_SPEED 255

#define POWER1_PIN 2 
#define POWER2_PIN 3

void LEFT (void);
void RIGHT(void);
void STOP (void);

int Left, Right = 0;

 short left_sensor;
 short right_sensor;

void setup()
{
  pinMode(LEFT_MOTOR_PIN,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN,OUTPUT);
  
  pinMode(POWER1_PIN,OUTPUT);
  pinMode(POWER2_PIN,OUTPUT);

  digitalWrite(POWER1_PIN,HIGH); 
  digitalWrite(POWER1_PIN,HIGH);
     
  pinMode(LEFT_SENSOR_PIN,INPUT);
  pinMode(RIGHT_SENSOR_PIN,INPUT);

  Serial.begin(9600);
}

void readSensors() {
    left_sensor = digitalRead(LEFT_SENSOR_PIN);
    right_sensor = digitalRead(RIGHT_SENSOR_PIN);
    Serial.print(left_sensor);
    Serial.print(" - ");
    Serial.println(right_sensor); 
 }


void loop() 
{
  int lastDIR = 0;
  //Branco = 0, Preto = 1
  readSensors();

  readSensors();
  if (left_sensor == 1 && right_sensor == 0){   
         lastDIR = 1;
  } else if (left_sensor == 0 && right_sensor == 1)  {         
         lastDIR = 2;
  }

  if (lastDIR == 1) { 
      RIGHT(); 
      Serial.print("RIGHT");
  }
  if (lastDIR == 2) { 
      LEFT();
      Serial.print("LEFT");
  }
  if (lastDIR == 0) { 
      FORWARD();
      Serial.print("FORWARD");
  }
}

void FORWARD() {
  analogWrite(LEFT_MOTOR_PIN,  MOTOR_SPEED);
  analogWrite(RIGHT_MOTOR_PIN, MOTOR_SPEED);
  Serial.println("FORWARD"); 
}


void LEFT2 (void)
{
   Serial.println("LEFT2"); 
   analogWrite(LEFT_MOTOR_PIN,MOTOR_SPEED);
   analogWrite(RIGHT_MOTOR_PIN,0);      
}

void RIGHT2 (void)
{
   Serial.println("RIGHT2"); 
   analogWrite(LEFT_MOTOR_PIN,0);
   analogWrite(RIGHT_MOTOR_PIN,MOTOR_SPEED);
}

void STOP (void)
{
  analogWrite(LEFT_MOTOR_PIN,0);
  analogWrite(RIGHT_MOTOR_PIN,0);
}
