//PINS
#define PWMPin1        10
#define PWMPin2        11
#define SPEED 120

#define LeftMotorPin1  4
#define LeftMotorPin2  5
#define RightMotorPin1 6
#define RightMotorPin2 7


#define IN1  4
#define IN2  5
#define IN3  6
#define IN4  7

#define THRESHOLD 150 //IR Reflection

bool centralizing = false;

void setup()
{
    pinMode(PWMPin1,OUTPUT); //PWM Pin 1
    pinMode(PWMPin2,OUTPUT); //PWM Pin 2
    
    analogWrite(PWMPin1,SPEED);
    analogWrite(PWMPin2,SPEED);
    
    pinMode(LeftMotorPin1,OUTPUT); //Left Motor Pin 1
    pinMode(LeftMotorPin2,OUTPUT); //Left Motor Pin 2
    
    pinMode(RightMotorPin1,OUTPUT); //Right Motor Pin 1
    pinMode(RightMotorPin2,OUTPUT);  //Right Motor Pin 2

    Serial.begin(9600);                   
    while (!Serial);

    Serial.println("START!");
}




void forward() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);  
}

void right() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);
     
    centralizing = true;
}


void left() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);
    
    centralizing = true;  
}

void loop() 
{ 
    short IR1, IR2, IR3, IR4; // sensor values

    IR1 = digitalRead(IN1);
    IR2 = digitalRead(IN2); //center
    IR3 = digitalRead(IN3); //center
    IR4 = digitalRead(IN4);
    
    if (centralizing) {
      if (IR2 == 1 || IR3 == 1) {
          centralizing = false;
       }
    } else {
        if (IR1 == 1 ) {
           left();       
        } else if (IR4 == 1) {             
            right();
        } else {
            forward();
        }
    }
}
