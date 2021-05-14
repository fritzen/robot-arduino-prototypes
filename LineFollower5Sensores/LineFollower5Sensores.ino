#define mot1 A2
#define mot2 A3
#define mot3 A4
#define mot4 A5

//ok
// EFEITO FADE IN / OUT NO MOTOR ATIVO NO MOMENTO.
#define LED_1 5
#define LED_2 6


short left_sensor;
short right_sensor;
short center_left_sensor;
short center_right_sensor;
short center_sensor;

short led_fade_value = 0;
bool  led_fade_somando = true;
short led_fade_incremento = 5;

void setup()
{


  pinMode(8,INPUT); 
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  pinMode(3,INPUT); 
  pinMode(4,INPUT);

  
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);
  
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);

  Serial.begin(9600);
}



void fadeLed(bool left, bool right){
  
    if (led_fade_somando) {
      led_fade_value = led_fade_value + led_fade_incremento;  
    } else {
      led_fade_value = led_fade_value - led_fade_incremento;
    }    
    
    if (led_fade_value >= 240) {
      led_fade_somando = false;
      led_fade_value = 255;
    }

    if (led_fade_value <= 10) {
      led_fade_somando = true;
      led_fade_value = 0;
    }
    
    if (left) {
        analogWrite(LED_1, led_fade_value);
    } else {
       analogWrite(LED_1, 0);
    }

    if (right) {
      analogWrite(LED_2, led_fade_value);
    } else {
      analogWrite(LED_2, 0);
    }    
}

void readSensors() {

    right_sensor=digitalRead(8);//sensor1 (canto direito)    
    center_right_sensor=digitalRead(9);//sensor2    
    center_sensor=digitalRead(10);//sensor3 (centro)    
    center_left_sensor=digitalRead(11);//sensor4   
    left_sensor=digitalRead(12);//sensor5 (canto esquerdo)



    int ir_proximity_sensor = digitalRead(3); // parede preta
    int bumper_sensor = digitalRead(4);


    Serial.print(left_sensor);
    Serial.print(" - ");
    Serial.print(center_left_sensor);
    Serial.print(" - ");
    Serial.print(center_sensor);
    Serial.print(" - ");
    Serial.print(center_right_sensor);
    Serial.print(" - ");
    Serial.print(right_sensor);
    Serial.print(" :::: ");
    Serial.print(bumper_sensor);
    Serial.print(" - ");
    Serial.println(ir_proximity_sensor);


    if (ir_proximity_sensor == 0) {
        led_fade_incremento = 5;
    } else {
        led_fade_incremento  = 20;
    }
    
    if (left_sensor == 0 || right_sensor == 0 || bumper_sensor == 1) {
      delay(5);
    }

    if (center_right_sensor == 0) {
      right_sensor == 0;
    }

    if (center_left_sensor == 0) {
        left_sensor = 0;
    }
}


void loop() 
{
 //Branco = 1, Preto = 0
readSensors();

int turnCount = 0;
   
if (left_sensor == 1 && right_sensor == 0){   
            fadeLed(false, true);
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
                if (right_sensor == 1 || center_sensor == 0) {
                    LEFT2(); //Aquela endireitada...
                    FORWARD2(); //E manda bala
                    delay(1);                 
                    break;
                }
            }
 } else if (left_sensor == 0 && right_sensor == 1)  {
            fadeLed(true, false);
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
              if (left_sensor == 1 || center_sensor == 0) {
                    RIGHT2(); //Aquela endireitada...
                    FORWARD2(); //E manda bala
                    delay(1);                 
                 break;
              }
            }
 } else {
    fadeLed(true, true);
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
   analogWrite(mot1,255); //(255 + 0 ) = ligar // (255, 255 DESLIGAR)
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
