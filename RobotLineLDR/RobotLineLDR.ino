//PINS

#define MAX_SPEED 150
#define START_SPEED 125

#define LeftMotorPin  9
#define RightMotorPin 11

//ANALOGS 6, 9, 10, and 11.

// RGULADO PARA LUZ INDOR
#define THRESHOLD_LDR1 570 //LIGHT LDR Reflection
#define THRESHOLD_LDR2 360 //LIGHT LDR Reflection
#define THRESHOLD_LDR3 360 //LIGHT LDR Reflection

bool centralizing = false;

bool expectedLeft = false;
bool expectedRight = false;

int motorSpeed = 0;

short lastChoice = 0;

int contador = 0;

void setup()
{

    pinMode(LeftMotorPin, OUTPUT);   // sets the pin as output
    pinMode(RightMotorPin, OUTPUT);   // sets the pin as output
   
    pinMode(2, OUTPUT);   // sets the pin as output
    pinMode(3, OUTPUT);   // sets the pin as output
    pinMode(4, OUTPUT);   // sets the pin as output
    pinMode(5, OUTPUT);   // sets the pin as output

    motorSpeed = START_SPEED;
    Serial.begin(9600);
}


void forward() {
    analogWrite(LeftMotorPin,motorSpeed);
    analogWrite(RightMotorPin,motorSpeed);

    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
}

void right() {
    analogWrite(LeftMotorPin,motorSpeed);
    analogWrite(RightMotorPin,0);


    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
}


void left() {
    analogWrite(LeftMotorPin,0);
    analogWrite(RightMotorPin,motorSpeed);   
    
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    
}


void loop() 
{ 
  
    short IR1, IR2, IR3; // sensor values
    
    IR1 = analogRead(A0);
    IR2 = analogRead(A1); //center
    IR3 = analogRead(A2);
    
/*
    Serial.print(IR1);
    Serial.print("*");
    Serial.print(IR2);
    Serial.print("*");
    Serial.println(IR3);
    */
    if (IR1 > THRESHOLD_LDR1) IR1 = 1; else IR1 = 0;
    if (IR2 > THRESHOLD_LDR2) IR2 = 1; else IR2 = 0;
    if (IR3 > THRESHOLD_LDR3) IR3 = 1; else IR3 = 0;

    
   
   if (centralizing) {
      if (IR2 == 1) {
          motorSpeed = START_SPEED;
          centralizing = false;
       }
    } else {
        if (IR1 == 1 ) {
            motorSpeed = START_SPEED;
            centralizing = true;
            lastChoice = 1;
            left();
        } else if (IR3 == 1) {
            motorSpeed = START_SPEED;
            centralizing = true;
            lastChoice = 2;  
            right();
        } else {
            lastChoice = 3;
            forward();
        }
    }

    if (lastChoice == 1) {
      left();
    }

    if (lastChoice == 2) {
      right();
    }

    contador++;

    if (contador > 50) {

        motorSpeed++;     
        if (motorSpeed > MAX_SPEED) {
            motorSpeed = START_SPEED;
        }
        
        contador=0;

      }


    Serial.println(motorSpeed);

    
}






