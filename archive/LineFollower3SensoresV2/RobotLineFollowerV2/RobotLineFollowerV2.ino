//PINS
#define SPEED 120

#define LeftMotorPin1  2
#define RightMotorPin1 3


#define THRESHOLD 500 //IR Reflection

bool centralizing = false;

void setup()
{


    pinMode(LeftMotorPin1,OUTPUT); //Left Motor Pin 1  
    pinMode(RightMotorPin1,OUTPUT); //Right Motor Pin 1

    analogWrite(LeftMotorPin1,SPEED);
    analogWrite(RightMotorPin1,SPEED);
    
    Serial.begin(9600);
  
}




void forward() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(RightMotorPin1,HIGH);  
}

void right() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(RightMotorPin1,LOW);
    centralizing = true;
}


void left() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(RightMotorPin1,HIGH); 
    centralizing = true;  
}

void loop() 
{ 
    short IR1, IR2, IR3; 
    
    IR1 = analogRead(A0);
    IR2 = analogRead(A1); 
    IR3 = analogRead(A2); 
    
    Serial.print(IR1);
    Serial.print("*");
    Serial.print(IR2);
    Serial.print("*");
    Serial.print(IR3);
    
    if (IR1 > THRESHOLD) IR1 = 1; else IR1 = 0;
    if (IR2 > THRESHOLD) IR2 = 1; else IR2 = 0;
    if (IR3 > THRESHOLD) IR3 = 1; else IR3 = 0;

    
    if (centralizing) {
      if (IR2 == 1) {
          centralizing = false;
       }
       Serial.print("<centralizing>"); 
    } else {
        if (IR1 == 1 ) {
           Serial.print("left();");
           left();       
        } else if (IR3 == 1) {   
            Serial.print("right();");          
            right();
        } else {
            Serial.print("forward();"); 
            forward();
        }
    }

    Serial.println("");

}






