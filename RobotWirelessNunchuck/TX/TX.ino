/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//https://github.com/datacute/WiiChuck
//#include <WiiChuck.h>
#include <Wire.h>

#include "ArduinoNunchuk.h"


//Nunchuck nunchuck(SDA, SCL);

ArduinoNunchuk nunchuk = ArduinoNunchuk();

 //EM USO 
RF24 radio(7, 8); // CE, CSN 
const byte address[6] = "70007";

char payload[22];

void setup() {
  payload[0] = '\0' ;
  Serial.begin(9600);
  delay(100);

   
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

  Serial.println("RADIO-INIT");

  if (!radio.isChipConnected()) {
    Serial.println("RADIO-NOT-CONNECTED");
  } else {
    Serial.println("RADIO-CONNECTED");
  }
  Serial.println("NUNCHUCK-INIT");
  nunchuk.init();
  Serial.println("NUNCHUCK-INIT-OK");
  
  delay(100);
}

void GetFormated3Bytes(int value, int offset){
//void GetFormated3Bytes(int value, char payload[], int offset){
  char tmp[3];
  sprintf(tmp, "%03d", value);
  payload[offset] = tmp[0];
  payload[offset + 1] = tmp[1];
  payload[offset + 2] = tmp[2];
}


void loop() {
  nunchuk.update();
  
  payload[0] = '\0'; // terminate the buffer
  
  // Armazenha as variáveis de X e Y do controle.
  int joyX = nunchuk.analogX;
  int joyY = nunchuk.analogY;
  int accelX = nunchuk.accelX;
  int accelY = nunchuk.accelY;
  int accelZ = nunchuk.accelZ;
  int zButton = nunchuk.zButton;
  int cButton = nunchuk.cButton;


  GetFormated3Bytes(joyX, 0);  
  GetFormated3Bytes(joyY, 3);
  GetFormated3Bytes(accelX, 6);
  GetFormated3Bytes(accelY, 9);
  GetFormated3Bytes(accelZ, 12);
  GetFormated3Bytes(zButton, 15);
  GetFormated3Bytes(cButton, 18);
  
  payload[21] = '\0'; // terminate the buffer

  

  //Serial.println(payload);
  if (!radio.isChipConnected()) {
    Serial.println(payload);
    Serial.println("NOT-CONNECTED");
    delay(1000);
  } else {
    Serial.println(payload);
    radio.write(&payload, sizeof(payload));
  }
  
  delay(1);


  //atoi na volta http://www.cplusplus.com/reference/cstdlib/itoa/

  
}
