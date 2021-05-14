
//Definicoes pinos Arduino ligados a entrada da Ponte H
#define IN1  4
#define IN2  5
#define IN3  6
#define IN4  7

#define SENSOR_POWER_PIN 2


#define SPEED 160
#define MAX_SPEED 130
#define MIN_SPEED 80

#define STATE_LEFT 1
#define STATE_RIGHT 2
#define STATE_FORWARD 3

#define BLACK LOW
#define WHITE HIGH

unsigned short state = 3;

long lastSendTime = 0; //timestamp
int interval = 10;   // Intervalo em ms (default 500ms)                              

bool centralizing = false;

void setup() {

  Serial.begin(9600);                   
  while (!Serial);


  //Define os pinos como saida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  //Sensores
  pinMode(8,INPUT); 
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  
  pinMode(SENSOR_POWER_PIN, OUTPUT);
  digitalWrite(SENSOR_POWER_PIN, HIGH);
}


void forward() {
  state = STATE_FORWARD;
  
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
    
  //Gira o Motor B no sentido horario
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);//SPEED
  
  delay(15);
  breakMotor();
  delay(30);
  
}


void slow_forward() {
  state = STATE_FORWARD;
  
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
    
  //Gira o Motor B no sentido horario
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);//SPEED
  
  delay(15);
  breakMotor();
  delay(60);
  
}

void left() {
    centralizing = true;
    state = STATE_LEFT;
    //Gira o Motor A no sentido anti-horario
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Gira o Motor B no sentido horario
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    delay(50);
}





void right() {
    centralizing = true;
    state = STATE_RIGHT;
          //Gira o Motor B no sentido anti-horario
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
     //Gira o Motor A no sentido horario
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);

     delay(50);
}

void left2() {
    centralizing = true;
    state = STATE_LEFT;
    //Gira o Motor A no sentido anti-horario
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(15);
    //Gira o Motor B no sentido horario
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(15);
}


void right2() {
    centralizing = true;
    state = STATE_RIGHT;
          //Gira o Motor B no sentido anti-horario
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
     delay(15);
     //Gira o Motor A no sentido horario
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     
     delay(15);
}

void breakMotor() {
 //Para o motor A
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 //Para o motor B
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
}


void testMotors()
{
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 delay(2000);
 //Para o motor A
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 delay(500);
 //Gira o Motor B no sentido horario
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
 delay(2000);
 //Para o motor B
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
 delay(500);
 
 //Gira o Motor A no sentido anti-horario
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 delay(2000);
 //Para o motor A
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 delay(500);
 //Gira o Motor B no sentido anti-horario
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
 delay(2000);
 //Para o motor B
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
 delay(500);
}






void loop() {

  int s_right=digitalRead(8);//sensor1 (canto direito)
  int s_center_right=digitalRead(9);//sensor2
  int s_center=digitalRead(10);//sensor3 (centro)
  int s_center_left=digitalRead(11);//sensor4
  int s_left=digitalRead(12);//sensor5 (canto esquerdo)

    //HIGH white, LOW black

     if (s_center == BLACK) {
        forward();
     } else {      
        slow_forward();
     }

     if (s_center_left == BLACK) {  
        left2();
     }

     if (s_center_right == BLACK) {  
        right2();
     }

     if (s_left == BLACK){
        left();
     }


     if (s_right == BLACK){
        right();
     }

}
