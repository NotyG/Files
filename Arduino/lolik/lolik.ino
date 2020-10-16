#define PWMB 6
#define DIRB 7
#define DIRA 8
#define PWMA 9

char incomingByte;

void forward();
void backward();
void left();
void right();
void stop();

void setup() {
  Serial.begin(9600);
  pinMode(PWMB , OUTPUT);
  pinMode(DIRB , OUTPUT);
  pinMode(DIRA , OUTPUT);
  pinMode(PWMA , OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == '8') {
      forward();
    }
    else if (incomingByte == '2') {
      backward();
    }
    else if (incomingByte == '4') {
      left();
    }
    else if (incomingByte == '6') {
      right();
    }
    else if (incomingByte == '5') {
      stop();
    }
  }
}
void forward() {
  digitalWrite(DIRA, 1);
  digitalWrite(DIRB, 1);
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
}
void backward() {
  digitalWrite(DIRA, 0);
  digitalWrite(DIRB, 0);
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
}
void left() {
  digitalWrite(DIRA, 0);
  digitalWrite(DIRB, 1);
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
}
void right() {
  digitalWrite(DIRA, 1);
  digitalWrite(DIRB, 0);
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
}
void stop() {
  digitalWrite(DIRA, 0);
  digitalWrite(DIRB, 0);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}
