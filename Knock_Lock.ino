//Import Servo library and his instance
#include <Servo.h>
Servo myServo;

//VARIABLES
const int piezo = A0;
const int switchPin = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int redLed = 5;

int knockVal;
int switchVal;

const int quietKnock = 10;
const int loudKnock = 100;

boolean locked = false;
int numberOfKnocks = 0;

//Setup
void setup() {
  //Initialization
  myServo.attach(9);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(switchPin, INPUT);

  Serial.begin(9600);
  digitalWrite(greenLed, HIGH);
  myServo.write(0);
  Serial.println("The door is unlocked!");
}

//Main code
void loop() {
 
  if(locked == false){
    switchVal = digitalRead(switchPin);
    
    if(switchVal == HIGH){
      locked = true;
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      myServo.write(90);
      Serial.println("The door is locked!");
      delay(1000);
    }
  }

  if(locked == true){
    knockVal = analogRead(piezo);

    if(numberOfKnocks < 15 && knockVal > 0){
      if(checkForKnock(knockVal) == true){
        numberOfKnocks++;
      }
      Serial.print(15-numberOfKnocks);
      Serial.println(" more knocks to go... ");
    }
    
    if(numberOfKnocks >= 15){
      locked == false;
      myServo.write(0);
      delay(20);
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
      Serial.println(" The door is unlocked!");
    }
  }
}

//METHODE
boolean checkForKnock(int value){
  if(value > quietKnock && value < loudKnock){

   digitalWrite(yellowLed, HIGH);
   delay(50);
   digitalWrite(yellowLed, LOW); 
   Serial.print("Valid knock of value ");
   Serial.println(value);

   return true;
  } else{
      Serial.print("Bad knock value ");
      Serial.println(value);
      return false;
  }
}

