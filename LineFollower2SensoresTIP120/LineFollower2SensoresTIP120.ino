#define LEFT_SENSOR_PIN A2
#define RIGHT_SENSOR_PIN A3


#define LEFT_MOTOR_PIN 5
#define RIGHT_MOTOR_PIN 6

#define SENSOR_THRESHOLD 390

void LEFT (void);
void RIGHT(void);
void STOP (void);

short left_sensor;
short right_sensor;


#define BLACK  0
#define WHITE  1

void setup()
{

  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);

  pinMode(LEFT_MOTOR_PIN,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN,OUTPUT);


  pinMode(LEFT_SENSOR_PIN,INPUT);
  pinMode(RIGHT_SENSOR_PIN,INPUT);

  Serial.begin(9600);                   

}

void loop() 
{ 

    int left_sensor = analogRead(LEFT_SENSOR_PIN);
    int right_sensor = analogRead(RIGHT_SENSOR_PIN);


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

    
    if (left_sensor == BLACK && right_sensor == WHITE){
        Serial.println("left_sensor");
        RIGHT();
    } else if (left_sensor == WHITE && right_sensor == BLACK)  {
        Serial.println("right_sensor");
        LEFT();
     }
}



void RIGHT (void)
{
    digitalWrite(LEFT_MOTOR_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN, LOW);
}

void LEFT (void)
{
    digitalWrite(LEFT_MOTOR_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_PIN, HIGH);
}
