int A=0, B=0, C=0;
void seeyou()
{
	if(SensorValue[S1]<=20)
	{
		C=C+1;
		playSound(soundBeepBeep);
		motor(motorA)=0;
		motor(motorB)=0;
		wait1Msec(300);
			moveMotorTarget(motorA,470.45, -25);
			moveMotorTarget(motorB,470.45, -25);
			waitUntilMotorStop(motorA);
			waitUntilMotorStop(motorB);
			moveMotorTarget(motorA,70, 25);
			moveMotorTarget(motorB,-70, 25); //!
			waitUntilMotorStop(motorA);
			waitUntilMotorStop(motorB);
			//
			moveMotorTarget(motorA,276.91, 25);
			moveMotorTarget(motorB,276.91, 25);
			waitUntilMotorStop(motorA);
			waitUntilMotorStop(motorB);
		//
		moveMotorTarget(motorD, 1200, -25);
		waitUntilMotorStop(motorD);
		delay(500);
		moveMotorTarget(motorA,276.91, -25);
		moveMotorTarget(motorB,276.91, -25);
		waitUntilMotorStop(motorA);
		waitUntilMotorStop(motorB);
		moveMotorTarget(motorA,-70, 25);
		moveMotorTarget(motorB, 70, 25); //!
		waitUntilMotorStop(motorA);
			waitUntilMotorStop(motorB);
		moveMotorTarget(motorA, 420, 25);
		moveMotorTarget(motorB, -420, 25); //!
		waitUntilMotorStop(motorA);
			waitUntilMotorStop(motorB);
		moveMotorTarget(motorA,40, 25);
		moveMotorTarget(motorB,40, 25);
	  waitUntilMotorStop(motorA);
		waitUntilMotorStop(motorB);
    B=A;
    A=0;

	}
}
void line(int G, int T){
	int grey1=30;
	while(A==B){
		if(A==9){
			motor(motorA)=0;
			motor(motorB)=0;
			moveMotorTarget(motorA, 420, 25);
		  moveMotorTarget(motorB, -420, 25); //!
		  }
		//seeyou();
		if(SensorValue[S2]>grey1) //2L 3R AL BR
		{
			if(SensorValue[S3]>grey1)
			{
				setMotorSync(motorA, motorB,0, G);   // |

			}
			else
			{
				setMotorSync(motorA, motorB, T, G);  // v leva kosit
		}}
		else{
			if(SensorValue[S3]>grey1)
			{
				setMotorSync(motorA, motorB, -T, G); // /
			}else
			{setMotorSync(motorA, motorB,0, G); // -|-*/
				//seeyou();
				A=A+1;
					moveMotorTarget(motorA,40, 25);
					moveMotorTarget(motorB,40, 25);
					waitUntilMotorStop(motorA);
					waitUntilMotorStop(motorB);
	}}}
}
task main()
{
	moveMotorTarget(motorA,7.1591, 25);
	moveMotorTarget(motorB,7.1591, 25);
	line(25, 40);
	moveMotorTarget(motorA,7.1591, 25);
	moveMotorTarget(motorB,7.1591, 25);
	//
	moveMotorTarget(motorD, 1200, 25);
	moveMotorTarget(motorA, 420, 25);
	moveMotorTarget(motorB, -420,25); //!
	while(E<C){
	line(25, 40);
	E=E+1;
	}
}
