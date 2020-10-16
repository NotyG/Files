#include <QTRSensors.h>

#define PWMB 7
#define BIN2 8
#define BIN1 9


#define PWMA 12
#define AIN2 11
#define AIN1 10

#define BUTTON 48

#define DIR 5
#define PWM 4

#define NUM_SENSORS   8     
#define TIMEOUT       2500    
#define EMITTER_PIN 41

#include "Servo.h"

QTRSensors qtr((unsigned char[]) {25 ,27, 29 , 31 , 33 , 35 , 37 , 39},
NUM_SENSORS, TIMEOUT); 

Servo hand;


float values[8];


void setup() {


  pinMode(BUTTON, INPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);

  pinMode(DIR, OUTPUT);
  pinMode(PWM, OUTPUT);

  Serial.begin(9600);

}

void loop() {
getValues();
printValues();

}

void getValues(){
  qtr.read(values);
}

void printValues(){
  for(int i; i<8; i++){
    Serial.print(values[i]);
    Serial.print('\t');
  }
  Serial.println(" ");
}

void servo(){
  hand.attach(3);
  hand.write(90);
  hand.detach();
}

void motors(){
    forward();
    delay(1000);
    stopMotors();
    delay(2000);
}

void balka(){
  if (digitalRead(BUTTON) == 0) {
    digitalWrite(DIR, 0);
    analogWrite(PWM, 100);
  }
  else {
    digitalWrite(DIR, 1);
    analogWrite(PWM, 100);
    delay(1500);
    analogWrite(PWM, 0);
  }
}

void forward() {
  digitalWrite(AIN1, 0);
  digitalWrite(AIN2, 1);
  analogWrite(PWMA, 255);

  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 0);
  analogWrite(PWMB, 255);
}

void stopMotors() {
  digitalWrite(AIN1, 1);
  digitalWrite(AIN2, 1);
  analogWrite(PWMA, 0);

  digitalWrite(BIN1, 0);
  digitalWrite(BIN2, 0);
  analogWrite(PWMB, 0);
}
