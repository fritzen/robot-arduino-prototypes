#include "Stepper.h"
#include <Servo.h>

#define STEPS  32
#define THRESHOLD  750 //(0=branco 1023=preto)


bool centralizandoEsquerda = false;

bool centralizandoDireita = false;


Stepper stepper1(STEPS, 2, 4, 3, 5);
Stepper stepper2(STEPS, 6, 8, 7, 9);
Servo myservo; 


void setup() {
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  pinMode(11,INPUT_PULLUP);

  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  
  Serial.begin(9600);
}

void virarEsquerda() {
 myservo.write(35);
 
 stepper1.step(1); //manter

 delay(10);
}

void virarDireita() {
 myservo.write(110);

 stepper2.step(-1); //manter
 delay(10); 
}

void avancar() {
 myservo.write(65);
 stepper1.step(1);
 stepper2.step(-1);
 delay(10); 
}



void loop() {



 int IR1, IR2, IR3; // sensor values


IR1 = analogRead(A0);
IR2 = digitalRead(11); //center
IR3 = analogRead(A2);


if (IR1 > THRESHOLD) {
  IR1 = 1;
} else {
  IR1 = 0;  
}

if (IR3 > THRESHOLD) {
  IR3 = 1;
} else {
  IR3 = 0;  
}

if (centralizandoEsquerda || centralizandoDireita) {
  if (IR2 == 1) {
    centralizandoDireita = false;
    centralizandoEsquerda = false;
  } else if (centralizandoEsquerda) {
    virarEsquerda();
   } else if (centralizandoDireita) {
     virarDireita();
   }
} else {

    if (IR1 == 1) {       
        virarEsquerda();
        Serial.println("virarEsquerda");
        centralizandoEsquerda = true;
    } else if (IR3 == 1 ) {
       virarDireita();
       Serial.println("virarDireita");
       centralizandoDireita = true;
    } else { 
      avancar();
      
      }
}



}
