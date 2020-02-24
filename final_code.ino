
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9,10);
char msg;
char call;
int buttonpin=12;

const int solButtonPin = 2;
const int solPin = 7;
int solButtonState = 0;

void setup()
{
  pinMode(solButtonPin,INPUT);
  pinMode(solPin,OUTPUT);
  pinMode(buttonpin,INPUT);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);// Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("press button");
}

void loop()
{
  solButtonState = digitalRead(solButtonPin);
  if(solButtonState == HIGH) {
    delay(10000);
    digitalWrite(solPin, LOW);
    delay(1000);
    digitalWrite(solPin, HIGH);
  } else {
    digitalWrite(solPin, HIGH);
  }
  
  if(digitalRead(buttonpin)==HIGH)
  {
    
    Serial.println("button pressed");
    delay(2000);
    SendMessage();  
  }

 if (mySerial.available()>0)
 Serial.write(mySerial.read());
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+18577535327\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("Rat Captured");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
