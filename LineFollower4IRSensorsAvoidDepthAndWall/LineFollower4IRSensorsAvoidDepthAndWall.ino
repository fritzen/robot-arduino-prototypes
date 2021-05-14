#define SPEED 120

#define LeftMotorPin1  3
#define LeftMotorPin2  4
#define RightMotorPin1 5
#define RightMotorPin2 6

#define SENSOR_PIN_POWER 2

#define SENSOR_PIN_1 8
#define SENSOR_PIN_2 9
#define SENSOR_PIN_3 11
#define SENSOR_PIN_4 12
#define SENSOR_PIN_WALL  7
#define SENSOR_PIN_CENTER 10

#define BLACK  0

#define THRESHOLD 150 //IR Reflection

bool centralizing = false;

void setup()
{


    pinMode(LeftMotorPin1,OUTPUT); //Left Motor Pin 1
    pinMode(LeftMotorPin2,OUTPUT); //Left Motor Pin 2    
    pinMode(RightMotorPin1,OUTPUT); //Right Motor Pin 1
    pinMode(RightMotorPin2,OUTPUT);  //Right Motor Pin 2
    
    pinMode(SENSOR_PIN_POWER,OUTPUT); 
    digitalWrite(SENSOR_PIN_POWER,HIGH);

    pinMode(SENSOR_PIN_1,INPUT); 
    pinMode(SENSOR_PIN_2,INPUT);
    pinMode(SENSOR_PIN_3,INPUT);
    pinMode(SENSOR_PIN_4,INPUT);
    pinMode(SENSOR_PIN_WALL,INPUT);
    pinMode(SENSOR_PIN_CENTER,INPUT);

    Serial.begin(9600);                   
    while (!Serial);

    Serial.println("START!");

}





void mode1() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,HIGH);  
}

void mode2() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,LOW);  
}


void mode3() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,LOW);  
}


void mode4() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,HIGH);  
}


void mode5() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);  
}

void mode6() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);  
}

void mode7() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);  
}
void mode8() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);  
}


void off() {
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,LOW);        
}

void forward() {
    Serial.print("forwards");
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);  
}

void back() {
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);  
}

void right() {
    Serial.print("right");
    digitalWrite(LeftMotorPin1,LOW);
    digitalWrite(LeftMotorPin2,HIGH);
    digitalWrite(RightMotorPin1,LOW);
    digitalWrite(RightMotorPin2,HIGH);    
    centralizing = true;
}


void left() {
    Serial.print("left");
    digitalWrite(LeftMotorPin1,HIGH);
    digitalWrite(LeftMotorPin2,LOW);
    digitalWrite(RightMotorPin1,HIGH);
    digitalWrite(RightMotorPin2,LOW);     
    centralizing = true;  
}

void loop() 
{ 
    short IR1, IR2, IR3, IR4; // sensor values


    IR1 = digitalRead(SENSOR_PIN_1);
    IR2 = digitalRead(SENSOR_PIN_2); //center
    IR3 = digitalRead(SENSOR_PIN_3); //center
    IR4 = digitalRead(SENSOR_PIN_4);

    int wall = digitalRead(SENSOR_PIN_WALL);
    int depth = digitalRead(SENSOR_PIN_CENTER);


    Serial.print(IR1);
    Serial.print("-");
    Serial.print(IR2);
    Serial.print("-");
    Serial.print(IR3);
    Serial.print("-");
    Serial.print(IR4);
    Serial.print("-");
    Serial.print(wall);
    Serial.print("-");
    Serial.print(depth);  

    if (wall == 1 || depth == 0 ){
      off(); //Parar
      delay(1000);
      back(); //Ré
      delay(500);
      left(); //Iniciar giro
      delay(600);

      //Girar até achar IR2 ou IR3
      while(true) {
        
        IR2 = digitalRead(SENSOR_PIN_2); //center
        IR3 = digitalRead(SENSOR_PIN_3); //center
        
        if (IR2 == BLACK || IR3 == BLACK) {
            centralizing = false;
            break;
        }      
      }
    }
    
    if (centralizing) {
      if (IR2 == BLACK || IR3 == BLACK) {
          centralizing = false;
      }
    } else {
        if (IR1 == BLACK ) {
           left();
        } else if (IR4 == BLACK) {             
            right();
        } else {
            forward();
        }
    }

     Serial.println("*");
}
