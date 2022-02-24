#ifndef Chess_h
#define Chess_h

#include <Arduino.h>
//#include <WProgram.h>
//pls y >= 0 
// x >= 0

class Figure{
	protected:
		virtual bool areMove(std::int y, int x) = 0;
		Figure(std::int x, std::int code);
		int getX();
		int getY();
		int getXStart();
		int getYStart();
		int getCode();
		void backToOld();
		void setX(int x);
		void setY(int y);
		void setXStart(int x);
	private:
		std::int _x;
		std::int _y;
		std::int _xOld;
		std::int _yOld;
		std::int _xStart;
		std::int _yStart;
		std::int _code;
};
class Queen: public Figure{
	public:
		Queen(int x);
		virtual bool areMove(int y, int x);
	
};

class Rook: public Figure{
	public:
		Rook(int x);
		virtual bool areMove(int y, int x);
};

class Bishop: public Figure{
	public:
		Bishop(int x);
		virtual bool areMove(int y, int x);
};

class Knight: public Figure{
	public:
		Knight(int x);
		virtual bool areMove(int y, int x);
};
#endif
