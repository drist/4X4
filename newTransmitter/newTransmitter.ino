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
  //Serial.println(joystickX);
  //Serial.println(joystickY);
  if (joystickY>510)
  {
    //joystickY /= 130;
    joystickY -=512; // joystick forward is 512-1024 so we subtract 512 to get a number similar to the reverse which is 0-512
    joystickY /= 57;//512 divided by 9 rounded up
    joystickY +=1; // this one starts at 1 which is nothing and never makes it to 9.
    if (joystickX > 550) //Joystick is also pointing Right
    {
      Serial.print("|G");
    }
    else if (joystickX<200) //Joystick is also pointing Left
    {
      Serial.print("|H");
    }
    else
    {
      Serial.print("|F");// Joystick is pointing Forward & Center (straight)
    }
    Serial.print(joystickY);
  }
  else if(joystickY<400) // we don't do steering backward yet
  {
    joystickY /= 57; //512 divided by 9 rounded up
    joystickY -= 9; // to get the opposite since we are going backwared
    joystickY *= -1; // make positive integer
    Serial.print("|B");
    Serial.print(joystickY);
  }
  else if(joystickX>750) // spin Righ
  {
    Serial.print("|R6");// right now is a static controllable speed
  }
  else if(joystickX<300) 
  {
    Serial.print("|L6");// right now is a static controllable speed
  }
  delay(15);
}
