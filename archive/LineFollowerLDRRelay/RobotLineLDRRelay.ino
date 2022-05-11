// ** ATENÇÃO **
// REGULADO PARA LUZ INDOR
// DEVE-SE AJUSTAR ESTES VALORES PARA NIVEIS DE ILUMINAÇÃO AMBIENTE DIFERENTES
#define THRESHOLD_LDR1 75 //LIGHT LDR Reflection
#define THRESHOLD_LDR2 75 //LIGHT LDR Reflection

//PINS
#define LeftMotorPin  9
#define RightMotorPin 10

short left_sensor;
short right_sensor;

void setup()
{
    pinMode(LeftMotorPin, OUTPUT);   // sets the pin as output
    pinMode(RightMotorPin, OUTPUT);   // sets the pin as output   
      
    FORWARD();
    
    Serial.begin(9600);
}



void readSensors() {
    left_sensor = analogRead(A0);
    right_sensor = analogRead(A1);
    
    Serial.print(left_sensor);
    Serial.print("*");
    Serial.println(right_sensor);

    if (left_sensor > THRESHOLD_LDR1) left_sensor = 1; else left_sensor = 0;
    if (right_sensor > THRESHOLD_LDR2) right_sensor = 1; else right_sensor = 0;

}

void loop() 
{

   readSensors(); 

   if (left_sensor == 1 && right_sensor == 0){   
     RIGHT2();
   } else if (left_sensor == 0 && right_sensor == 1)  {
     LEFT2();     
   }
}


void FORWARD() {
    digitalWrite(LeftMotorPin,HIGH);
    digitalWrite(RightMotorPin,HIGH);
}

void STOP() {
    digitalWrite(LeftMotorPin,LOW);
    digitalWrite(RightMotorPin,LOW);
}

void RIGHT2() {
    digitalWrite(LeftMotorPin,LOW);
    digitalWrite(RightMotorPin,HIGH);
}

void LEFT2() {
    digitalWrite(LeftMotorPin,HIGH);
    digitalWrite(RightMotorPin,LOW);
}
