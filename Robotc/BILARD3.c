
task main()
{
	int A, B, Gm;
	A=20;
	B=35;
	while(true){
		motor[motorA]=5;
		motor[motorD]=-5;
		while(sensorvalue[S1]<=B){ //ultarsonik
			motor[motorA]=A;
			motor[motorD]=A;
			if(sensorvalue[S3]<=45){ //g\perdniy dantchik
				motor[motorA]=0;
				motor[motorD]=0;
				Gm=getMotorEncoder(motorA);
				moveMotorTarget(MotorA, Gm, B);
				moveMotorTarget(MotorD Gm, B);
				waituntilmotorstop(motorA);
				resetmotorencoder(motorA);
				if(sensorvalue[S2]<=45){
					motor[motorA]=0;
					motor[motorD]=0;
					Gm=getMotorEncoder(motorA);
					moveMotorTarget(MotorA, Gm, -B);
					moveMotorTarget(MotorD Gm, -B);
					waituntilmotorstop(motorA);
					resetmotorencoder(motorA);

				}
			}
		}
