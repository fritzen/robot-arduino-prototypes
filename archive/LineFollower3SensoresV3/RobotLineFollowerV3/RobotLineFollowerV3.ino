//PINS
#define SPEED 120

//L293D
//Motor A
#define LEFT_MOTOR_PIN_1 5 
#define LEFT_MOTOR_PIN_2 6
//Motor B
#define RIGHT_MOTOR_PIN_1 10
#define RIGHT_MOTOR_PIN_2 9

#define LEFT_SENSOR_PIN A4
#define MIDDLE_SENSOR_PIN A3
#define RIGHT_SENSOR_PIN A2


#define SENSOR_THRESHOLD 400

bool centralizing = false;

void setup()
{
  pinMode(LEFT_MOTOR_PIN_1,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN_1,OUTPUT);
  pinMode(LEFT_MOTOR_PIN_2,OUTPUT);
  pinMode(RIGHT_MOTOR_PIN_2,OUTPUT);

  pinMode(LEFT_SENSOR_PIN,INPUT);
  pinMode(RIGHT_SENSOR_PIN,INPUT);

  Serial.begin(9600);
}

void loop() 
{ 
    short IR1, IR2, IR3; 
    
    IR1 = analogRead(LEFT_SENSOR_PIN);
    IR2 = analogRead(MIDDLE_SENSOR_PIN); 
    IR3 = analogRead(RIGHT_SENSOR_PIN); 
    
    Serial.print(IR1);
    Serial.print("*");
    Serial.print(IR2);
    Serial.print("*");
    Serial.print(IR3);
    
    if (IR1 > SENSOR_THRESHOLD) IR1 = 1; else IR1 = 0;
    if (IR2 > SENSOR_THRESHOLD) IR2 = 1; else IR2 = 0;
    if (IR3 > SENSOR_THRESHOLD) IR3 = 1; else IR3 = 0;
  
    if (centralizing) {
      if (IR2 == 1) {
          centralizing = false;
       }
       Serial.print("<centralizing>"); 
    } else {
        if (IR1 == 1 ) {
           Serial.print("left();");
           BACK();
           delay(10);
           LEFT();       
        } else if (IR3 == 1) {   
           Serial.print("right();");
           BACK();        
           delay(10);
           RIGHT();
        } else {
           Serial.print("forward();"); 
           FORWARD();
        }
    }

    Serial.println("");

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


void RIGHT (void)
{
    digitalWrite(LEFT_MOTOR_PIN_1, HIGH);
    digitalWrite(LEFT_MOTOR_PIN_2, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_1, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN_2, LOW);
    
    centralizing = true;
    
}

void LEFT (void)
{
    digitalWrite(LEFT_MOTOR_PIN_1, LOW);
    digitalWrite(LEFT_MOTOR_PIN_2, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN_2, HIGH);
    
    centralizing = true;

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
