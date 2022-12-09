
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
RH_ASK driver;
char *paquet;
const int echoPin = 3; // Echo Pin of Ultrasonic Sensor
const int pingPin = 4; // Trigger Pin of Ultrasonic Sensor

//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
       Serial.println("init failed");
    pinMode(pingPin, OUTPUT); // initialising pin 3 as output
    pinMode(echoPin, INPUT); // initialising pin 2 as input    
    paquet="AH-000"; //paquet initialization
    paquet[0]='S';
    paquet[1]='2'; 
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------

void loop()
{
    long duration, cm;
    int num;
    char *temp;
    while(1)
    {
        delay(150);       
        digitalWrite(pingPin, LOW);
        delayMicroseconds(2);
        digitalWrite(pingPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(pingPin, LOW);
        duration = pulseIn(echoPin, HIGH); // using pulsin function to determine total time
        cm = duration / 29 / 2 ;
        temp = toArray (cm);
        num  = strlen(temp) ;
        if      (num==3) {paquet[3]=temp[0];paquet[4]=temp[1];paquet[5]=temp[2];}
        else if (num==2) {paquet[4]=temp[0];paquet[5]=temp[1];}
        else if (num==1) {paquet[5]=temp[0];}
    
        driver.send((uint8_t *)paquet, strlen(paquet));
        driver.waitPacketSent();
        Serial.println(paquet); 
        delay(200);    
    } 
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------

char * toArray(int number)
{
    int n = log10(number) + 1;
    int i;
    char *numberArray = calloc(n, sizeof(char));
    for (i = n-1; i >= 0; --i, number /= 10)
        numberArray[i] = (number % 10) + '0';
    return numberArray;
}


