#include <Ultrasonic.h> //https://github.com/ErickSimoes/Ultrasonic


#define in1 8
#define in2 9
#define in3 6
#define in4 7

Ultrasonic ultrasonic1(12, 13);  // An ultrasonic sensor HC-04 (TRIG,ECHO)
Ultrasonic ultrasonic2(4, 5);  // An ultrasonic sensor HC-04 (TRIG,ECHO)
Ultrasonic ultrasonic3(2, 3);  // An ultrasonic sensor HC-04 (TRIG,ECHO)

int ABS = 200;
int Left_Distance = 0, Right_Distance = 0, Middle_Distance = 0 ;
void _mForward()
{

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.print("ROBOT_MOVING_FORWARD");
}
void _mBack()
{

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.print("ROBOT_MOVING_BACKWARD");
}
void _mleft()
{

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  Serial.print("ROBOT_MOVING_LEFT");
}
void _mright()
{

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.print("ROBOT_MOVING_RIGHT");
}
void _mStop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  Serial.print("ROBOT_STOP");
}

int intMiddle_Distance_test() 
{
  digitalWrite(A0, LOW); 
  delayMicroseconds(2);
  digitalWrite(A0, HIGH); 
  delayMicroseconds(20);
  digitalWrite(A0, LOW); 
  float Fdistance = pulseIn(A1, HIGH);
  delay(10);
  Fdistance= Fdistance/ 29 / 2; 
  return (int)Fdistance;
} 
void setup()
{
  Serial.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

// setup maximum range of approximately 5m.
ultrasonic1.setTimeout(30000UL);
//ultrasonic2.setTimeout(30000UL);
ultrasonic3.setTimeout(30000UL);

  _mStop();
}





void loop()
{
  Left_Distance = ultrasonic1.distanceRead();
  delay(50);
  Middle_Distance = ultrasonic2.distanceRead(); // intMiddle_Distance_test(); //ultrasonic2.distanceRead();
  delay(10);
  Right_Distance = ultrasonic3.distanceRead();
  delay(50);
  
  Serial.print("Left_Distance: ");
  Serial.print(Left_Distance);
  Serial.print(" cm, Middle_Distance: ");
  Serial.print(Middle_Distance);
  Serial.print(" cm, Right_Distance: ");
  Serial.print(Right_Distance);
  Serial.print(" cm, Status: ");
  
  //delay(100);
  //return;
  if (Middle_Distance <= 50)
  {
    /*  _mStop();
      delay(1000);*/

    if (Right_Distance > Left_Distance)
    {
      if ((Right_Distance <= 30) && (Left_Distance <= 30))
      { _mStop();
        delay(100);
        _mBack();
        delay(200);

      }
      else {
        //   _mBack();
        //  delay(3000);
        _mright();
        delay(200);
      }

    }
    else if (Right_Distance < Left_Distance)
    {
      if ((Right_Distance <= 30) && (Left_Distance <= 30))

      { _mStop();
        delay(100);
        _mBack();
        delay(200);
      }
      else {
        //      _mBack();
        //   delay(3000);
        _mleft();
        delay(200);
      }
    }
  }
  else if (Right_Distance <= 15)
  {
    _mleft();
    delay(200);
  }

  else if (Left_Distance <= 15)
  {
    _mright();
    delay(200);
  }
  else {
    _mForward();
  }
  //delay(500);

  Serial.println("");
}

