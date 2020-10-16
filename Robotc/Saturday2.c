
task main()
{
int A=50;
float C=429.55, B=107;
B=B*2;
moveMotorTarget(motorA, B, A); //AL BR
moveMotorTarget(motorB, B,-A);
waitUntilMotorStop(motorA);
//turn
moveMotorTarget(motorA, C, A);
moveMotorTarget(motorB, C, A);
waitUntilMotorStop(motorA);
//drive to
moveMotorTarget(motorA, B,-A); //AL BR
moveMotorTarget(motorB, B, A);
waitUntilMotorStop(motorA);
//turn brown
B=B/2/4*3;
moveMotorTarget(motorA, C, A); //AL BR
moveMotorTarget(motorB, C, A);
waitUntilMotorStop(motorA);
}
