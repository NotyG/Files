#include "Arduino.h"
#include "Chess.h"
//pls x >= 0 
// y >= 0
Figure::Figure(std::int x, std::int code){
	_x = x;
	_y = 0;
	_xStart = x;
	_yStart = 0;
	_code = code;
	_xOld = x;
	_yOld = y;
}	
Figure::getX(){
	return _x;
}
	
Figure::getY(){
	return _y;
}

Figure::setX(int x){
	_xOld = _x;
	_x = x;
}

Figure::setY(int y){
	_yOld = _y;
	_y = y;
}

Figure::setXStart(int x){
	if(_xStart < 0){ 
	_xStart = x;
	_x = x;
	}
	else{ throw "Cannot set _xStart, _xStart was declared before, if you want to change _xStart it must be negative earlier";}
}
Figure::backToOld(){
	x = _xOld;
	y = _yOld;
}
////Rook////
Rook::Rook(int x){
	Figure(x, 4);
}
Rook::areMove(int y, int x){
	if(_xStart == x || _yStart == y){
		return true;
	}
	else: return false;
}
////Bishop////
Bishop::Bishop(int x){
	Figure(x, 2);
}
Bishop::areMove(int y, int x){
	if(abs(_xStart - x) == abs(_yStart - y)){
		return true;
	}
	else: return false;
}
////Queen//////
Queen::Queen(int x){
	Figure(int x, 1);
	
}
Queen::areMove(int y, int x){
	if( (abs(_xStart - x) == abs(_yStart - y)) || (_xStart == x || _yStart == y) ){
		return true;
	}
	else: return false;
}
////Knight/////
Knight::Knight(int x){
	Figure(x, 3);
}
Knight::areMove(int y, int x){
	if( (abs(_xStart - x) == 2 && abs(_yStart - y) == 1) ||
		(abs(_xStart - x) == 1 && abs(_yStart - y) == 2) ){
		return true;
	}
	else{
		return false;
	}
}