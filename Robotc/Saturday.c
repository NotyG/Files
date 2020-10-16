
task main()
{
int A=50;
float C=986, B=107;
moveMotorTarget(motorA, B, A);
moveMotorTarget(motorB, B,-A);
waitUntilMotorStop(motorA);
//turn
moveMotorTarget(motorA, C, A);
moveMotorTarget(motorB, C, A);
waitUntilMotorStop(motorA);
//drive to
moveMotorTarget(motorA, C, -A);
moveMotorTarget(motorB, C, -A);
waitUntilMotorStop(motorA);
//drive out
B=B*2.3;
C=1160;
moveMotorTarget(motorA, B, -A);
moveMotorTarget(motorB, B, A);
waitUntilMotorStop(motorA);
//turn
moveMotorTarget(motorA, C, A);
moveMotorTarget(motorB, C, A);
waitUntilMotorStop(motorA);
}
