 /* ---------------------------------------------------------------------------------------
 * Autor / Author: Eduardo Fritzen - eduardo@fritzen.io
 * Não é permitido o uso para fins comerciais deste código sem a autorização por escrito do autor
 * Use of this code for commercial purposes is not permitted without written authorization from the author
 * ---------------------------------------------------------------------------------------
 */
#include "FioSensorDistance.h"
#include <Arduino.h>

FioSensorDistance::FioSensorDistance()
{

}

void FioSensorDistance::attach(uint8_t sensorType)
{       
  _sensorType = sensorType;   
  if (sensorType == TYPE_LASER) {
        Wire.begin();
        _laser.setTimeout(500);
        if (!_laser.init())
        {
          Serial.println("Failed to detect and initialize sensor!");
          while (1)
          {
          }
        }
        _laser.startContinuous();
  } else if (sensorType == TYPE_ULTRASONIC) {
      pinMode(TRIG_PIN, OUTPUT);
      pinMode(ECHO_PIN, INPUT);
  }else if (sensorType == TYPE_DIGITAL_DISTANCE) {
      pinMode(DIGITAL_DISTANCE_PIN,INPUT_PULLUP);
  }
}

int FioSensorDistance::ping() //functon used to calculate sonar distance in cm and create an integer called "distance" for other functions
{ 
    float temperatura = 19.307;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    unsigned long durationus = pulseIn(ECHO_PIN, HIGH);

    double speedOfSoundInCmPerMs = 0.03313 + 0.0000606 * temperatura;
    double distanceCm = durationus / 2.0 * speedOfSoundInCmPerMs;
    if (distanceCm == 0 || distanceCm > 400) {
        return -1.0 ;
    } else {
        return distanceCm;
    }

  return distanceCm;
}

bool FioSensorDistance::isCollision()
{
    int mm = 2500;
    if (_sensorType == TYPE_LASER) {
        if (_laser.timeoutOccurred())
        {
            Serial.print(" TIMEOUT");
        }
        mm = _laser.readRangeContinuousMillimeters();
    } else if (_sensorType == TYPE_DIGITAL_DISTANCE) {
        if (digitalRead(DIGITAL_DISTANCE_PIN)==LOW) {
            mm = 0;
        }
    } else if (_sensorType == TYPE_ULTRASONIC) {
      mm = ping();
    }
    Serial.print("distancia: ");
    Serial.println(mm);
    return (mm < COLLISION_DIST);
}
