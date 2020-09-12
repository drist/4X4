#include <SoftwareSerial.h>

//SoftwareSerial mySerial(2,3);

int joystickX=0;
int joystickY=0;
String motorCmd;

void setup() {
  Serial.begin(9600);
  //mySerial.begin(9600);
  pinMode(4,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
}

void loop() {
  if (digitalRead(4) == LOW) 
  {
    //mySerial.print('*');
    Serial.print('*');
    delay(250);//pevent bouncing
  }
  joystickX = analogRead(0);
  joystickY = analogRead(1);
  if (joystickY>510)
  {
    //joystickY /= 130;
    joystickY -=512; // joystick reversive is 512-1024 so we subtract 512 to get a number similar to the reverse which is 0-512
    joystickY /= 57;//512 divided by 9 rounded up
    joystickY +=1; // this one starts at 1 which is nothing and never makes it to 9.
    Serial.print("|F");
    Serial.print(joystickY);
  }
  else if(joystickY<450)
  {
    joystickY /= 57; //512 divided by 9 rounded up
    joystickY -= 9; // to get the opposite since we are going backwared
    joystickY *= -1; // make positive integer
    Serial.print("|B");
    Serial.print(joystickY);
  }
  else if(joystickX>550) 
  {
    Serial.print("|R7");// right now just going at a controllable speed
  }
  else if(joystickX<450) 
  {
    Serial.print("|L7");// right now just going at a controllable speed
  }
  delay(15);
}
