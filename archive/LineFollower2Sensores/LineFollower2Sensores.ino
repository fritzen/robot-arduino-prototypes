#define mot1 6
#define mot2 7
#define mot3 8
#define mot4 9

#define LEFT_PIN A1  
#define RIGHT_PIN A0

int Left, Right = 0;

short left_sensor;
short right_sensor;

void setup()
{
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);

  pinMode(LEFT_PIN,INPUT);
  pinMode(RIGHT_PIN,INPUT);


  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);


  Serial.begin(9600);
}

void readSensors() {
    left_sensor = digitalRead(LEFT_PIN);
    right_sensor = digitalRead(RIGHT_PIN);
    Serial.print(left_sensor);
    Serial.print(" - ");
    Serial.println(right_sensor); 
}


void loop() 
{
 //Branco = 0, Preto = 1
readSensors();

int turnCount = 0;

if (left_sensor == 1 && right_sensor == 0){   
            turnCount = 0;
            while(true) {            
                readSensors();
                RIGHT2();
                turnCount++;
                //Limitador frente... Sempre andar um pouco para frente, caso contrário o robô ira ficar parado..             
                if (turnCount > 1 && (left_sensor == 0 && right_sensor == 0)) {                       
                      turnCount = 0;
                      FORWARD();
                 }
                if (right_sensor == 1) {
                    LEFT2(); //Aquela endireitada...
                    FORWARD2(); //E manda bala
                    delay(1);                 
                    break;
                }
            }
 } else if (left_sensor == 0 && right_sensor == 1)  {
            turnCount = 0;
            while(true) {
              readSensors();
              LEFT2();
              turnCount++;
              //Limitador frente... Sempre andar um pouco para frente, caso contrário o robô ira ficar parado..             
              if (turnCount > 1 && (left_sensor == 0 && right_sensor == 0)) {                       
                  turnCount = 0;
                  FORWARD();
              }
              // Ficar no While true até o sensor do outro lado tocar a linha preta
              if (left_sensor == 1) {
                    RIGHT2(); //Aquela endireitada...
                    FORWARD2(); //E manda bala
                    delay(1);                 
                 break;
              }
            }
 } else {
    FORWARD();
 }
     
}

void FORWARD() {
  analogWrite(mot1,255);
  analogWrite(mot2,0);
  analogWrite(mot3,255);
  analogWrite(mot4,0);
  delayMicroseconds(4000);
  STOP();
  delayMicroseconds(1);
  Serial.println("FORWARD"); 
}


void FORWARD2() {
  analogWrite(mot1,255);
  analogWrite(mot2,0);
  analogWrite(mot3,255);
  analogWrite(mot4,0);
  delayMicroseconds(8000);
  STOP();
  delayMicroseconds(1);
  Serial.println("FORWARD"); 
}

void LEFT2 (void)
{
   Serial.println("LEFT2"); 
   analogWrite(mot1,255); 
   analogWrite(mot2,0);
   analogWrite(mot3,0);
   analogWrite(mot4,255);

   delayMicroseconds(5000);
   STOP();
   delayMicroseconds(1);
        

}

void RIGHT2 (void)
{
   Serial.println("RIGHT2"); 
   analogWrite(mot1,0);
   analogWrite(mot2,255);
   analogWrite(mot3,255);
   analogWrite(mot4,0);
   
   delayMicroseconds(5000);
   STOP();
   delayMicroseconds(1);
}

void STOP (void)
{
  analogWrite(mot1,0);
  analogWrite(mot2,0);
  analogWrite(mot3,0);
  analogWrite(mot4,0);
}

void BREAK (void)
{
  analogWrite(mot1,255);
  analogWrite(mot2,255);
  analogWrite(mot3,255);
  analogWrite(mot4,255);
}
