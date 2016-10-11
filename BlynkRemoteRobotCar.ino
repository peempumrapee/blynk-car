#define BLYNK_PRINT Serial    // Prints to serial
#include <ESP8266WiFi.h>      //Calls Blynk ESP8266 Wifi Libary
#include <BlynkSimpleEsp8266.h> //Calls Blynk ESP8266 Library

//Variables are declared at this point before void setup to make variables public and thus accessible throughout the entire code if needed.
int CarSpeed = 0;
int foward = 0;
int back = 0;
int left = 0;
int right = 0;
int CarStop = 0;
int SensorLeft = 0;
int SensorRight = 0;
int SensorEnable = 0;
int CarBreak = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Your Project Token"; 

void setup()
{
  // Set console baud rate
 Serial.begin(9600);


 Blynk.begin(auth,"SSID","Password"); // Signs into home wifi. 

 pinMode(D0, INPUT);//sensor left
 pinMode(D1, INPUT);//sensor right

 pinMode(D2, OUTPUT);//dir1PinA
 pinMode(D4, OUTPUT);//dir2PinA
 pinMode(D3, OUTPUT);//speedPinA
 pinMode(D5, OUTPUT);//dir1PinB
 pinMode(D7, OUTPUT);//dir2PinB
 pinMode(D6, OUTPUT);//speedPinB

}

 BLYNK_WRITE(V0)
{
  foward = param.asInt();
 
}
 BLYNK_WRITE(V1)
{
  back = param.asInt();
 
}
 BLYNK_WRITE(V2)
{
  left = param.asInt();
 
} 
 BLYNK_WRITE(V3)
{
  right = param.asInt();
 
}
 BLYNK_WRITE(V4)
{
 CarSpeed = param.asInt(); 
}
 BLYNK_WRITE(V5)
{
 SensorEnable = param.asInt(); 
}
 BLYNK_WRITE(V6)
{
 CarBreak = param.asInt(); 
}

void CarStopRun(){
  //SR
  //______________Motor 1______________
  analogWrite(D3, 0);//Sets speed variable via PWM
  digitalWrite(D2, LOW);
  digitalWrite(D4, HIGH);
  //______________Motor 2______________
  analogWrite(D6, 0);
  digitalWrite(D5, LOW);
  digitalWrite(D7, HIGH);
  Serial.println("Stop");
}
void CarFoward(){
  //F
  //______________Motor 1______________
  analogWrite(D3, CarSpeed);//Sets speed variable via PWM
  digitalWrite(D2, HIGH);
  digitalWrite(D4, LOW);
  //______________Motor 2______________
  analogWrite(D6, CarSpeed);
  digitalWrite(D5, HIGH);
  digitalWrite(D7, LOW);
  Serial.println("Foward");
}
void CarBack(){
  //F
  //______________Motor 1______________
  analogWrite(D3, CarSpeed);//Sets speed variable via PWM
  digitalWrite(D2, LOW);
  digitalWrite(D4, HIGH);
  //______________Motor 2______________
  analogWrite(D6, CarSpeed);
  digitalWrite(D5, LOW);
  digitalWrite(D7, HIGH);
  Serial.println("Reverse");
}
void CarLeft(){
  //L
  //______________Motor 1______________
  analogWrite(D3, CarSpeed-CarBreak);//Sets speed variable via PWM
  digitalWrite(D2, HIGH);
  digitalWrite(D4, LOW);
  
    //______________Motor 2______________
  analogWrite(D6, CarSpeed-CarBreak);
  digitalWrite(D5, LOW);
  digitalWrite(D7, HIGH); 
  Serial.println("Left");
}
void CarRight(){
  //R
  //______________Motor 1______________
  analogWrite(D3, CarSpeed-CarBreak);//Sets speed variable via PWM
  digitalWrite(D2, LOW);
  digitalWrite(D4, HIGH);
  //______________Motor 2______________
  analogWrite(D6, CarSpeed-CarBreak);
  digitalWrite(D5, HIGH);
  digitalWrite(D7, LOW);
  Serial.println("Right");
}
void ShortLeft(){
  //L
  //______________Motor 1______________
  analogWrite(D3, CarSpeed-CarBreak);//Sets speed variable via PWM
  digitalWrite(D2, HIGH);
  digitalWrite(D4, LOW);
  
    //______________Motor 2______________
  analogWrite(D6, 0);
  digitalWrite(D5, LOW);
  digitalWrite(D7, HIGH); 
  Serial.println("FLeft");
}
void ShortRight(){
  //R
  //______________Motor 1______________
  analogWrite(D3, 0);//Sets speed variable via PWM
  digitalWrite(D2, LOW);
  digitalWrite(D4, HIGH);
  //______________Motor 2______________
  analogWrite(D6, CarSpeed-CarBreak);
  digitalWrite(D5, HIGH);
  digitalWrite(D7, LOW);
  Serial.println("FRight");
}
void FowardLeft(){
  //F
  //______________Motor 1______________
  analogWrite(D3, CarSpeed);//Sets speed variable via PWM
  digitalWrite(D2, HIGH);
  digitalWrite(D4, LOW);
  //______________Motor 2______________
  analogWrite(D6, CarSpeed-(CarBreak*3));
  digitalWrite(D5, HIGH);
  digitalWrite(D7, LOW);
  Serial.println("Foward");
}
void FowardRight(){
  //F
  //______________Motor 1______________
  analogWrite(D3, CarSpeed-(CarBreak*3));//Sets speed variable via PWM
  digitalWrite(D2, HIGH);
  digitalWrite(D4, LOW);
  //______________Motor 2______________
  analogWrite(D6, CarSpeed);
  digitalWrite(D5, HIGH);
  digitalWrite(D7, LOW);
  Serial.println("Foward");
}
void BackLeft(){
  //F
  //______________Motor 1______________
  analogWrite(D3, CarSpeed);//Sets speed variable via PWM
  digitalWrite(D2, LOW);
  digitalWrite(D4, HIGH);
  //______________Motor 2______________
  analogWrite(D6, CarSpeed-(CarBreak*3));
  digitalWrite(D5, LOW);
  digitalWrite(D7, HIGH);
  Serial.println("Reverse");
}
void BackRight(){
  //F
  //______________Motor 1______________
  analogWrite(D3, CarSpeed-(CarBreak*3));//Sets speed variable via PWM
  digitalWrite(D2, LOW);
  digitalWrite(D4, HIGH);
  //______________Motor 2______________
  analogWrite(D6, CarSpeed);
  digitalWrite(D5, LOW);
  digitalWrite(D7, HIGH);
  Serial.println("Reverse");
}
void loop()
{
  if(SensorEnable == 1){  
    SensorLeft = digitalRead(D0);
    SensorRight = digitalRead(D1);
  }
  if(SensorEnable == 0){
    SensorLeft = 1;
    SensorRight = 1;
  }
  if(foward == 1){
    if(SensorLeft == 0 && SensorRight == 1){
       ShortLeft();
    }
    else if(SensorLeft == 1 && SensorRight == 0){
      ShortRight();
    }
    else if(left == 1){
      FowardLeft();
    }
    else if(right == 1){
      FowardRight();
    }
    else{
      CarFoward();  
    }
  }
  else if(back == 1){
    if(left == 1){
      BackLeft();
    }
    else if(right == 1){
      BackRight();
    }
    else{
      CarBack();  
    }  
  }
  else if(left == 1){
    CarLeft();  
  }
  else if(right == 1){
    CarRight();  
  }
  else{
    CarStopRun();  
  }
  Blynk.run();
}
