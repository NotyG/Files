#define enc  //0-2, 1-3, 2-21, 3 - 20,  4 -19, 5-18
long val
void setup(){
	Serial.begin(9600);
	attach.interrupt(enc, prval, CHANGE)
}

void loop(){
	;
}

void prval(){
	val++
	Serial.print(val)
}