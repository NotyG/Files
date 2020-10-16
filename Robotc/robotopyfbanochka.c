void line(int G){
	int grey1=30;

	while(true){
		if(SensorValue[S1]<=20){
			playSound(soundBeepBeep);
		if(SensorValue[S2]>grey1) //2L 3R BL CR
		{if(SensorValue[S3]>grey1)
			{setMotorSync(motorB, motorC,0, G);
				}
			else{
				setMotorSync(motorB, motorC, 50, G);
				}}
		else{if(SensorValue[S3]>grey1){
				setMotorSync(motorB, motorC, -50, G);
			}else
			{setMotorSync(motorB, motorC,0, G);
			playSound(soundLowBuzz);
				}}}}}
task main()
{line(25);
	}
