#include "Chess.h"

using namespace std;

Rook *rook = new Rook(-1); //это x координаты
Bishop *bishop = new Bishop(-1);
Queen *queen = new Queen(-1);
Knight *knight = new Knight(-1); //после считывания переопределить координату х

distance = 0;

vector< Figure* > figures;

int field[4][4]{
	{1, 1, 1, 1}, // x = 0 // слева сверху (0;0), но доска перевёрнута
	{0, 0, 0, 0}, // x = 1
	{0, 0, 0, 0}, // x = 2
	{0, 0, 0, 0}  // x = 3
}

bool isFree(int y, int x){
	if(field[y][x] == 0){return true;}
	else{return false;}
}
bool isAnswered(){
	int count = 0;
	for(int i = 0; i <= 3; i++){
	if( ((*figures[i]).getX() != (*figures[i]).getXStart()) ||
		((*figures[i]).getY() != (*figures[i]).getYStart())){
		distance += sqrt( ((*figures[i]).getX() - (*figures[i]).getXStart()) ** 2 + 
		((*figures[i]).getY() - (*figures[i]).getYStart()) ** 2 )
			
		count++;
		}
	if(count == 4){return true;}
	else{return false;}
  }
}
bool isSameParity(int object, int y, int x){
	if((*figures[object]).getCode() == 3){return true}
	if( (*figures[object]).getXStart() - x) % 2 == object % 2 || (*figures[object]).getYStart() - y) % 2 == object % 2){return true;}
	else{return false;}
}

void findPlace(int a){
	for(int currentFigure = a; currentFigure <= 3 ; i++){
	//	for(int toNextFigure = 1; toNextFigure <= 3 - currentFigure; toNextFigure++){
		for(int x = 0; x <= 3; x++){
			for(int y = 0; y <= 3; y++){
				if( (*figures[currentFigure]).areMove(y, x) == true && isSameParity(currentFigure, y, x) && isFree(y, x) == true){
					(*figures[currentFigure]).setX(x);
					(*figures[currentFigure]).setY(y);
 					// if(currentFigure <= 3){
						// findPlace(currentFigure+toNextFigure); //1 заменяется toNextFigure, порядок перемещения задан
					// } порядок определён всегда, дополнительный перебор не требуется
				}
			}
		}
	}
}

//когда увидел цвет элемента штрихкода добавил такую фигуру в вектор или лучше создавать объекты
void doSomething(){
figures.push_back(*rook);
figures.push_back(*bishop);
figures.push_back(*queen);
figures.push_back(*knight);}
