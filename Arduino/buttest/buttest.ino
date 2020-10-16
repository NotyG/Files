#define GREEN 40
#define RED 36
#define BLUE 42
#define BUTTONL 50
#define BUTTONR 48
void setup() {
 pinMode(BUTTONL, OUTPUT);
 pinMode(48, OUTPUT);
 pinMode(RED, OUTPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(BLUE, OUTPUT);

}

void loop() {
  if(digitalRead(BUTTONL)==HIGH && digitalRead(BUTTONR)==HIGH){
    digitalWrite(RED, 0); //123. 123. 123
    digitalWrite(GREEN, 0);
    digitalWrite(BLUE, 1);
  }
  else if (digitalRead(BUTTONL)==HIGH){
    digitalWrite(GREEN, HIGH);
  }
  else if (digitalRead(BUTTONR)==HIGH){
    digitalWrite(RED, 1);
    
  }
  else{
    digitalWrite(RED, 0); //123. 123. 123
    digitalWrite(GREEN, 0);
    digitalWrite(BLUE, 0);
  }
}
