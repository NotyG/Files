#include <PMotor.h>

PMotor motorR(8, 9, 7);
PMotor motorL(10, 11, 12);



void setup() {
  motorR.run(FORWARD);
  motorL.run(FORWARD);

  motorL.setSpeed(100);
  motorR.setSpeed(100);

  delay(8000);

  motorR.run(RELEASE);
  motorL.run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:

}
