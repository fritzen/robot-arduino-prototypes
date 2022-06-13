//sensores
#define LEFT_SENSOR_PIN A2          
#define RIGHT_SENSOR_PIN A3
#define OBSTACLE_SENSOR_PIN A4 

//motores
#define LEFT_MOTOR_PIN 7
#define RIGHT_MOTOR_PIN 2

#define BLACK  0
#define WHITE  1

void LEFT (void);
void RIGHT(void);
void STOP (void);

short left_sensor;
short right_sensor;
short obstacle;

void setup()
{

  pinMode(LEFT_SENSOR_PIN,INPUT_PULLUP);
  pinMode(RIGHT_SENSOR_PIN,INPUT_PULLUP);
  pinMode(OBSTACLE_SENSOR_PIN,INPUT_PULLUP);
   

  pinMode(LEFT_MOTOR_PIN,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN,OUTPUT);

  Serial.begin(9600);                   
  while (!Serial);
  FORWARD();
  delay(2000);
  LEFT ();
  delay(2000);
  RIGHT();
  delay(2000);
  

 
  Serial.println("START BOT!");

}

void readSensors() {
    left_sensor = digitalRead(LEFT_SENSOR_PIN);
    right_sensor = digitalRead(RIGHT_SENSOR_PIN);
    obstacle = digitalRead(OBSTACLE_SENSOR_PIN);
    
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

    if (obstacle == 0    ) {
      STOP();
    } else if (expected == 1) {
      RIGHT();
    } else if (expected == 0) {
      LEFT();          
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
