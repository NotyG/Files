#include <AFMotor.h>
 AF_DCMotor motorL(4);
 AF_DCMotor motorR(1);
int S = 70;
void setup() {
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  motorL.setSpeed(S);
  motorR.setSpeed(S);
  motorL.run(BACKWARD);
  motorR.run(BACKWARD);
}
void loop() {
}
