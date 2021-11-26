#include<Wire.h> 
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


#define trigPin 4
#define echoPin 5
#define LDR A0
#define Buzz 6

void Beep(){
  digitalWrite(Buzz, HIGH);
  delay(200);
  digitalWrite(Buzz, LOW);
  delay(200);
  digitalWrite(Buzz, HIGH);
  delay(200);
  digitalWrite(Buzz, LOW);
  delay(200);
  digitalWrite(Buzz, HIGH);
  delay(200);
  digitalWrite(Buzz, LOW);
  delay(200);
  
  
  }


void setup() {
  pinMode(Buzz, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LDR,INPUT);
  dht.begin();
  Wire.begin(0x08); 
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
//  Serial.begin(9600);
 
}
int distance, duration;
int t,x;
int ldr;
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;  
  if (distance>255){distance=254;}

  t = (int)dht.readTemperature();
  
  if(t>35){Beep();}
  if(distance<35){Beep();}


  ldr=analogRead(LDR);
  ldr=map(ldr,0,1023,0,100);
    
//  Serial.print(" Temp = ");
//  Serial.print(t);
//  Serial.print(" Dist = ");
//  Serial.print(distance);
//  Serial.print(" LDR = ");
//  Serial.print(ldr);
//  Serial.println();
  delay(500);

}

void receiveEvent(){
  x = Wire.read();
  }

void requestEvent() {
  if(x==0)
    {Wire.write(distance);}
   else if(x==1)
   {Wire.write(t);}
   else if(x==2)
   {Wire.write(ldr);}
   else
   {Wire.write(255);}
 }
