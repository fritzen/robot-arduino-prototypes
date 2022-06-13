#define LEFT_SENSOR_PIN A2
#define RIGHT_SENSOR_PIN A3
#define SENSOR_THRESHOLD 390
#define BLACK  0
#define WHITE  1

//our L298N control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

void setup(){

  pinMode(LEFT_SENSOR_PIN,INPUT);
  pinMode(RIGHT_SENSOR_PIN,INPUT);
  
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  Serial.begin(9600);


}

void loop(){


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
      moveBackward();    
    } else  if (left_sensor == WHITE && right_sensor == BLACK){
       moveForward(); 
    } else {
      moveStop();
    }
    
   

}



void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward(){ 
  
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);


    digitalWrite(RightMotorBackward, LOW); 
    digitalWrite(RightMotorForward, HIGH);

  
}

void moveForward(){

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);

  
  digitalWrite(RightMotorBackward, HIGH); 
  digitalWrite(RightMotorForward, LOW);
  
}
