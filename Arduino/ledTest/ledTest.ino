#define RED 36
#define BLUE 42
#define GREEN 40
void setup() {
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  digitalWrite(RED, 1);
  delay(1000);
  digitalWrite(RED, 0);
  delay(1000);
  digitalWrite(BLUE, 1);
  delay(1000);
  digitalWrite(BLUE, 0);
  delay(1000);
  digitalWrite(GREEN, 1);
  delay(1000);
  digitalWrite(GREEN, 0);
//  delay(1000);

}
