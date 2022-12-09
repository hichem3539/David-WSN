#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

const int ledT1 = 4; // Echo Pin of Ultrasonic Sensor
const int ledT2 = 3; // Echo Pin of Ultrasonic Sensor
const int ledT3 = 2; // Echo Pin of Ultrasonic Sensor

void setup()
{
    Serial.begin(9600);	// Debugging only
    if (!driver.init())
         Serial.println("init failed");
    pinMode(ledT1, OUTPUT);
    pinMode(ledT2, OUTPUT);
    pinMode(ledT3, OUTPUT);
}

void loop()
{
  uint8_t buf[6];
  uint8_t buflen = sizeof(buf);
  int cm; 

  while(1)
  {    
    if (driver.recv(buf, &buflen)) // Non-blocking
    if  (buf[0]=='S')
    {  
      if (buf[1]=='1')
      { 
        cm = toNumber(buf[3])*100 + toNumber(buf[4])*10 + toNumber(buf[5]) ; 
        if(cm<500) digitalWrite(ledT1,HIGH);
        else digitalWrite(ledT1,LOW);
      }
      else if (buf[1]=='2')
      { 
        cm = toNumber(buf[3])*100 + toNumber(buf[4])*10 + toNumber(buf[5]) ;
        if(cm<500) digitalWrite(ledT2,HIGH);
        else digitalWrite(ledT2,LOW);
      }    
      else if (buf[1]=='3')
      { 
        cm = toNumber(buf[3])*100 + toNumber(buf[4])*10 + toNumber(buf[5]) ;
        if(cm<500) digitalWrite(ledT3,HIGH);
        else digitalWrite(ledT3,LOW);
      } 
      Serial.print("Received from Slave ");
      Serial.print((char)buf[1]);
      Serial.print(" : ");
      Serial.println((char *)buf) ;           
    }
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------

int toNumber(char c)
{
  if (c=='0') return 0;
  if (c=='1') return 1;
  if (c=='2') return 2;
  if (c=='3') return 3;
  if (c=='4') return 4;
  if (c=='5') return 5;
  if (c=='6') return 6;
  if (c=='7') return 7;
  if (c=='8') return 8;
  if (c=='9') return 9;
}

