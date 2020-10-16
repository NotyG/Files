

void Sms(int A, float C){
C=C/17.6*360;
moveMotorTarget(motorA, C, A);
moveMotorTarget(motorB, C, A);
waitUntilMotorStop(motorA);
waitUntilMotorStop(motorB);
}
void turn(A, B, C){
moveMotorTarget(motorA, C, A);
moveMotorTarget(motorA, C, B);
waitUntilMotorStop(motorA);
waitUntilMotorStop(motorB);
}
task main()
{

Sms(50,50,36);

Sms(50,50,36);
Sms(50,50,36);
Sms(50,50,36);
}
