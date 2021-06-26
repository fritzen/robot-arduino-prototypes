#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "70007";


#include <Servo.h>
#include <Wire.h>

#define LEFTSERVOPIN  3
#define RIGHTSERVOPIN  5 

Servo leftServo;  
Servo rightServo;


#define SPEED_LEFT_FORWARD 180
#define SPEED_LEFT_STOP 90
#define SPEED_LEFT_BACKWARD 0



#define SPEED_RIGHT_FORWARD 180
#define SPEED_RIGHT_STOP 90
#define SPEED_RIGHT_BACKWARD 0


#define CENTER 0
#define UP 30 // 30 = MOVER 30% STICK. 100 = SIGNIFICA QUE SO IRA SE MOVIMENTAR SE MOVER TOTALMENTE
#define DOWN -30
#define LEFT -30
#define RIGHT 30

long lastPrint; //a long variable to store the time the wiimote state was last printed 
#define PRINTINTERVAL 1000  //the number of milliseconds between outputting the nunchuck state over the usb port 
#define DEADBAND 20         //A percentage away from center that is interpretted as still being zero  

#define TRIG_PIN A1
#define ECHO_PIN A2


int ping() //functon used to calculate sonar distance in cm and create an integer called "distance" for other functions
{ 
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  int distance = (duration/2) / 29.1;

  return distance;
}
void setup(){   
  Serial.begin(9600);

  Serial.println("BEGIN.");


  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
  
  
  pinMode(LEFTSERVOPIN, OUTPUT);     //sets the left servo signal pin 
                                     //to output
  pinMode(RIGHTSERVOPIN, OUTPUT);    //sets the right servo signal pin 
                                     //to output
  leftServo.attach(LEFTSERVOPIN);    //attaches left servo
  rightServo.attach(RIGHTSERVOPIN);  //attaches right servo
  goStop();

  
  lastPrint = millis(); 

 Serial.println("DONE.");


}


int GetFormated3Bytes(char payload[], int offset){
  char buffer[3];
  buffer[0] = payload[offset];
  buffer[1] = payload[offset + 1];
  buffer[2] = payload[offset + 2];

  int result = atol(buffer);

  return result;
}

void loop(){

    if (radio.available()) {

         Serial.println("RADIO-RX");
       
        char payload[22] = "";
        radio.read(&payload, sizeof(payload));

        int joyX = GetFormated3Bytes(payload, 0);
        int joyY = GetFormated3Bytes(payload, 3);
        int accelX = GetFormated3Bytes(payload, 6);
        int accelY = GetFormated3Bytes(payload, 9);
        int accelZ = GetFormated3Bytes(payload, 12);
        int zButton = GetFormated3Bytes(payload, 15);
        int cButton = GetFormated3Bytes(payload, 18);
    
        if(zButton == 1){     
           // moveWiiAcelerometer(accelX, accelY);            //moves the wii deoending on the nunchucks acceleration values

          //moveWiiJoystick(joyX, joyY);
           
        }else{ 

//            int dist = ping();
//            Serial.println(dist);
//            if (dist < 5 && dist > 0)  {
//              goBackward();
//              delay(300);
//              goStop();
//              delay(2000);
//            } else {
              moveWiiJoystick(joyX, joyY);  
  //          }
            
        }
        
       //Serial.println(payload);
       delay(30);
    }
    if((millis() - lastPrint) > PRINTINTERVAL){  //If a second has passed since last printing nunchuck values print them   
       // printData();          //print nunchuck values 
       // Serial.println();     //add an enter
        lastPrint = millis(); //store current time as lastPrint  
    }
}  
        
void moveWiiAcelerometer(int accelX, int accelY){  
  //moveDifferential(getYGs() * (float)100,getXGs()*(float)100); // 300 a 900
  //moveDifferential(accelY,accelX);  //deve estar no tange -100 100
}  


bool centered(int pos){

  if ((pos <= CENTER + DEADBAND) && (pos >= CENTER - DEADBAND) ) {
      return true;
    } else {
      return false;
      }
  
  
}

void moveWiiJoystick(int joyX, int joyY){
  
int left_right = map(joyX,0,255,-100,100);
int up_down = map(joyY,0,255,-100,100);


//Serial.print("up_down=");
//Serial.print(up_down);
//Serial.print(" - left_right=");
//Serial.println(left_right);


if (centered(up_down) && centered(left_right)) {
  goStop();
  //  Serial.println("STOP");
}


if (up_down > UP && centered(left_right)) {
  goForward();
    Serial.println("goForward");
}

if (up_down < DOWN && centered(left_right)) {
  goBackward();
  Serial.println("goBackward");
}




if (centered(up_down) && left_right > RIGHT) {
  goRight();
  Serial.println("goRight");
}

if (centered(up_down) && left_right < LEFT) {
  goLeft();
  Serial.println("goLeft");
}


 // moveDifferential();
  //moveDifferential(joyY,joyX);
}


/*
 * sends the robot forwards
 */
void goForward(){
   leftServo.write(SPEED_LEFT_FORWARD);
 rightServo.write(SPEED_RIGHT_BACKWARD);

}

/*
 * sends the robot backwards
 */
void goBackward(){
     leftServo.write(SPEED_LEFT_BACKWARD);
 rightServo.write(SPEED_RIGHT_FORWARD);


}

/*
 * sends the robot right
 */
void goRight(){
 leftServo.write(SPEED_LEFT_FORWARD);
 rightServo.write(SPEED_RIGHT_FORWARD);
}

/*
 * sends the robot left
 */
void goLeft(){
 leftServo.write(SPEED_LEFT_BACKWARD);
 rightServo.write(SPEED_RIGHT_BACKWARD);
}

/*
 * stops the robot
 */
void goStop(){
 leftServo.write(SPEED_LEFT_STOP);
 rightServo.write(SPEED_RIGHT_STOP);
} 

void printData(){
  Serial.print("-");
}
