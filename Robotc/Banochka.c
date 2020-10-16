
task main()
{
	int(A, B)
	A=50;
	B=-50;
	while(SensorValue[S1]==1){ //нажатие=1
		setmotorspeed(motorA, A);
		setmotorspeed(motorB, A);
	}
	SetMotorspeed(MotorA,0);
	Setmotorspeed(MotorB,0);
	delay(500);
	setmotorspeed(motorA,B);
	setmotorspeed(motorB,B); //otexal
	delay(600)
	SetMotorspeed(MotorA,0);
	Setmotorspeed(MotorB,0);
	SetMotorSpeed(MotorB,A);
	Delay(895);
	Setmotorspeed(MotorB,0); //povernulsa
	setmotorspeed(motorA, A);
	setmotorspeed(motorB, A);
	delay(300);
	SetMotorspeed(MotorA,0);
	Setmotorspeed(MotorB,0);
	SetMotorSpeed(MotorB,-A);
	Delay(895);
	Setmotorspeed(MotorB,0);
	setmotorspeed(motorA,B);
	setmotorspeed(motorB,B);
	delay(1200);
	SetMotorspeed(MotorA,0);
	Setmotorspeed(MotorB,0);
	SetMotorspeed(MotorB,A);
	delay(895);
	SetmotorSpeed(MotorB,0);
	setmotorspeed(motorA, A);
	setmotorspeed(motorB, A);
	delay(300);
	SetMotorspeed(MotorA,0);
	Setmotorspeed(MotorB,0);
	SetMotorSpeed(MotorB,-A);
	Delay(895);
	Setmotorspeed(MotorB,0);
}
