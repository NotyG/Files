#include <AFMotor.h>
int A = 100;
AF_DCMotor motorR(1);
AF_DCMotor motorL(2);
unsigned int countL = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(4, countleft, RISING);
  motorR.run(RELEASE);
  motorL.run(RELEASE);

}


void loop() {

  turn90();
  delay(2000);
}
void countleft() {
  countL++;
}

void  turn90() {
  motorR.setSpeed(0);
  motorL.setSpeed(0);
  motorR.run(FORWARD);
  motorL.run(BACKWARD);
  countL = 0;
  while (countL <= 250) {
    motorR.setSpeed(A);
    motorL.setSpeed(A);
      Serial.println(countL);
  }
  motorR.run(RELEASE);
  motorL.run(RELEASE);

}
