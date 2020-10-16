#include <Ultrasonic.h>
Ultrasonic ultrasonic (14, 15);
int dist;
void setup() {
  Serial.begin(9600);
}

void loop() {

  dist = ultrasonic.distanceRead();
  Serial.println(dist);
  delay(100);

}
