#include <Servo.h>
//https://youtu.be/P_nScyk7b6M
Servo myservo1;
Servo myservo2;
Servo myservoSensor;

int lastDIR = 0;

#define SENSOR_PIN A4
#define SERVO_PIN A5
#define SENSOR_THRESHOLD 500


short sensor;
short right_sensor;

void setup()
{
  myservo1.attach(9);
  myservo2.attach(11);
  myservoSensor.attach(SERVO_PIN);
  
  pinMode(SENSOR_PIN,INPUT_PULLUP);
  pinMode(SERVO_PIN,OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  Serial.begin(9600);  
  
  myservoSensor.write(50);
  
}

void loop() 
{

    bool directionChanged = false;
    sensor = analogRead(SENSOR_PIN);
    Serial.print(sensor);
        
    if (sensor > SENSOR_THRESHOLD) {
      if (lastDIR == 1 ) {  
        lastDIR = 2;
        myservoSensor.write(120);
      } else {
        lastDIR = 1;
        myservoSensor.write(10);        
      }
      directionChanged = true;
    }  

    if (lastDIR == 1) {
      RIGHT(); 
    } else {
      LEFT();
    }

    if (directionChanged) {
       delay(200); //Aguardar movimentacao do servo do sensor
    }
    
    Serial.print("*");
    Serial.print(sensor);
    Serial.print("*");
    Serial.println("");
}
  

void FORWARD() {
  myservo1.write(180);   
  myservo2.write(0);
}

void BACK() {
  myservo1.write(0);
  myservo2.write(180);
}



void RIGHT (void)
{ 

  myservo1.write(185);
  myservo2.write(90); 

}

void LEFT (void)
{

  myservo1.write(0);
  myservo2.write(10);

}
