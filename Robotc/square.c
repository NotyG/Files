   task main()
{int A,B,C,D,E,F,G;
	A=50;
	B=0;
	C=2000;
	D=1000;
	E=0;
	F=784;
	G=50
	while(E<8){
		setMotorSpeed(motorA,A); //89174825947
		setMotorSpeed(motorB,A);
		wait1Msec(C);
		setMotorSpeed(motorA,B);
		setMotorSpeed(motorB,B);
		wait1Msec(D);
		setMotorSpeed(motorA,G);
		wait1Msec(F);
		if(E==3)
		{setmotorspeed(motorA,A);
			setmotorspeed(motorB,A);
			wait1Msec(C);
			setMotorSpeed(motorA,B);
		  setMotorSpeed(motorB,B);}
		  if(E>=3)
	{G=-50}
			if(E==7)
			{setmotorspeed(motorA,A);
			setmotorspeed(motorB,A);
			wait1Msec(C);
			setMotorSpeed(motorA,B);
		  setMotorSpeed(motorB,B);}
		E=E+1;}

}
