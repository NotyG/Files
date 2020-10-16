#define enc 		//0-2, 1-3, 2-21, 3 - 20,  4 -19, 5-18
#define AIN1 11
#define AI2  12 
#define PWMA 13
long val;


void setup(){
pinMode(AIN1,OUTPUT);
pinMode (AI2,OUTPUT);
pinMode (PWMA,OUTPUT);
attach.interrupt(enc, rval, change);
}

void loop(){
	forward();
	while(val!=1000){
		
	}
	robotStop
}

void forward{
	digitalWrite(AIN1, HIGH);
	digitalWrite(AIN2, LOW);
	analogWrite(PWMA, 100);
}

void robotStop(){
	igitalWrite(AIN1, HIGH);
	digitalWrite(AIN2,HIGH);
	analogWrite(PWMA, 0);
}

void rval(){
	val++
}
