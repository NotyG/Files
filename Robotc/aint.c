task main{
int A=50, B=100, C=200, S=680, M=720;
while(true){
	//lay(5000)
moveMotorTarget(motorA, B, 70);
moveMotorTarget(motorB,-B, -A);
waitUntilMotorStop(motorA); //Prava
		//
		//movemotortarget(motorA, 700, A);
		 // movemotortarget(motorB, 700, A);
		//
 //movemotortarget(motorA, 500, A);
 //movemotortarget(motorB, 500, A);
		//
 //movemotortarget(motorA, 660, A);
 //movemotortarget(motorB, 660, A);
		//
moveMotorTarget(motorA,S,A);
moveMotorTarget(motorB, S, A);
waitUntilMotorStop(motorA);
delay(1000);
moveMotorTarget(motorA, -45,-70); //LA RB
moveMotorTarget(motorB,45,70); //Leva
waitUntilMotorStop(motorA);
//
moveMotorTarget(motorA, M, A);
moveMotorTarget(motorB, M, A);
waitUntilMotorStop(motorA);
delay(1000);
//
moveMotorTarget(motorA, 500, A);
moveMotorTarget(motorB, 500, A);
waitUntilMotorStop(motorA);
delay(1000);
moveMotorTarget(motorA, -B,-A);
moveMotorTarget(motorB, B, A);
waitUntilMotorStop(motorA);
// S=720;
moveMotorTarget(motorA, S, A);
moveMotorTarget(motorB, S, A);
waitUntilMotorStop(motorA);
//
moveMotorTarget(motorA, -B,-70);
moveMotorTarget(motorB, B, 70);
waitUntilMotorStop(motorA);
moveMotorTarget(motorA, -B,-70);
moveMotorTarget(motorB, B, 70);
waitUntilMotorStop(motorA);
//
moveMotorTarget(motorA, S, A);
moveMotorTarget(motorB, S, A);
waitUntilMotorStop(motorA);
// S=660;
moveMotorTarget(motorA, -B,-70);
moveMotorTarget(motorB, B, 70);
waitUntilMotorStop(motorA);
//
moveMotorTarget(motorA, 500, A);
moveMotorTarget(motorB, 500, A);
waitUntilMotorStop(motorA);
//
moveMotorTarget(motorA, M, A);
moveMotorTarget(motorB, M, A);
waitUntilMotorStop(motorA);
//
moveMotorTarget(motorA, -C,-A);
moveMotorTarget(motorB, C, A);
waitUntilMotorStop(motorA);
//
moveMotorTarget(motorA, 960, A);
moveMotorTarget(motorB, 960, A); //128
waitUntilMotorStop(motorA);
//
}
}
