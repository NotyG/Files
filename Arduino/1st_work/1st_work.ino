#include <Ultrasonic.h>
#include <AFMotor.h>
Ultrasonic ultrasonic (14, 15);
int dist;
AF_DCMotor motorL(4);
AF_DCMotor motorR(1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  motorL.setSpeed(70);
  motorR.setSpeed(70);
}

void loop() {
  // put your main code here, to run repeatedly:
  dist = ultrasonic.distanceRead();
  Serial.println(dist);
  if (dist > 20) {
    motorR.run(BACKWARD);
    motorL.run(BACKWARD);
  }
  else {
    motorL.run(RELEASE);
    motorR.run(RELEASE);
  }
}
