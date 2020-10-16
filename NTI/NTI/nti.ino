void A=, B=, C=, D=;
void setup() {
  // put your setup code here, to run once:
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
}
//move function
void up (void speed){
  analogWrite(A, speed);        //     A
  analogWrite(B, speed);        //
  analogWrite(C, -speed);       //C         D
  analogWrite(D, -speed);       //      
}                               //     B 
void to(void AC, BD);{
  analogWrite(A, AC);
  analogWrite(B, BD); //back
  analogWrite(C, -AC);
  analogWrite(D, -BD);
}
 void right(void AD, BC){
  analogWrite(A, AD);
  analogWrite(B, BC); //left
  analogWrite(C, -BC);
  analogWrite(D, -AD);
 }
//prgramm
void loop() {
  up(600);
  delay(1000)
  test
  up(300); //we fate in this
  /*to()
                                                 
*/}
