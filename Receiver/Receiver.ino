#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *Motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *Motor4 = AFMS.getMotor(4);

char buff;
int spd=0;//Max=250

void setup() 
{
  Serial.begin(9600);  
  //mySerial.begin(9600);  
  AFMS.begin();
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
}


void loop()
{
  if (Serial.available())
  {
    buff=Serial.read(); //  header
    if (buff=='*')
    {
      digitalWrite(4,!digitalRead(4));
      digitalWrite(7,!digitalRead(7));
      buff='\0';
    }
    else
    {
      if (buff == '|')
      {
        buff=Serial.read(); // direction
        //spd = Serial.parseInt();
        spd = Serial.read();
        spd = (int)spd-48;
        Serial.println(spd);
        //spd /= 4;
        spd *=28;
       
        switch(buff)
        {
          case 'F':
            Forward(spd);
            break;
          case 'B': 
            Backward(spd);
            break;
          case 'L':
            Left(spd);
            break;
          case 'R':
            Right(spd);
            break;
          default:
            Stop();
        }
      }
      else
      {
        Stop();
      }
    }
  }
  else if (buff=='*') // header for headlight message
  {
    digitalWrite(4,!digitalRead(4));
    digitalWrite(7,!digitalRead(7));
    buff='\0';
  }
  else
  {
    Stop();
  }
  delay(9);
}

void Forward(int Speed)
{
  Motor1->run(FORWARD); //Rt Front
  Motor2->run(FORWARD); // Lt Front
  Motor3->run(FORWARD); //Lt Rear
  Motor4->run(FORWARD);//Rt Rear
  Motor1->setSpeed(Speed);  
  Motor2->setSpeed(Speed);
  Motor3->setSpeed(Speed);  
  Motor4->setSpeed(Speed);
  //Serial.println("Forward");
}

void Backward(int Speed)
{
  Motor1->run(BACKWARD);
  Motor2->run(BACKWARD);
  Motor3->run(BACKWARD);
  Motor4->run(BACKWARD);
  Motor1->setSpeed(Speed/2);  
  Motor2->setSpeed(Speed/2);
  Motor3->setSpeed(Speed/2);  
  Motor4->setSpeed(Speed/2);
  //Serial.println("Backward");
}

void Left(int Speed)
{
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  Motor3->run(FORWARD);
  Motor4->run(FORWARD);
  Motor1->setSpeed(Speed); 
  Motor2->setSpeed(Speed/2);
  Motor3->setSpeed(Speed/2);  
  Motor4->setSpeed(Speed);
  //Serial.println("Left");
}

void Right(int Speed)
{
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  Motor3->run(FORWARD);
  Motor4->run(FORWARD);
  Motor1->setSpeed(Speed/2);  
  Motor2->setSpeed(Speed);
  Motor3->setSpeed(Speed);  
  Motor4->setSpeed(Speed/2);
  //Serial.println("Right");
}

void Stop()
{
  Motor1->setSpeed(0);  
  Motor2->setSpeed(0);
  Motor3->setSpeed(0);  
  Motor4->setSpeed(0);
  Motor1->run(RELEASE);  
  Motor2->run(RELEASE);  
  Motor3->run(RELEASE);  
  Motor4->run(RELEASE); 
}
