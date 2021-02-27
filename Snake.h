#pragma once
#include <vector>
#include "Globals.h"

using namespace std;

class Body_Part {
public:
	//конструкторы частей тела на разные слчаи жизни
	Body_Part(int* pos);//по умолчанию пририсовываем хвост
	Body_Part(int* pos, state new_type, direction dir);//полное определение

	~Body_Part();

	//Узнаем что за часть тела
	state Which();

	//узнаем направление последнего движения части тела
	direction Last_Move();



	//узнаем где часть тела расположена
	int* Position();

	//двигаем часть в заданном направлении
	void Move(direction new_dir);
	//часть тела вруг сменет тип. Например, хвост подрос и старый хвост теперь в теле
	void Change(state new_type);

protected:
	int place[2];//координаты части тела
	state type;//тип части тела
	direction prev_dir;//куда часть тела двигалась в последний раз
};


class Snake {
public:
	//конструктор змеи из стандартоной позиции (1:1) движется вправо
	Snake(int len);
	//в позиции (1:1) стоит змея длиной 2 и движется вправо
	Snake();

	~Snake();

	//дает указатель на часть тела n
	Body_Part* Get_Part(int n);

	//змея ползет в заданном направлении
	//если воткнулись в препятствие вернет false
	bool Move(direction dir, state next_place);
	//без роста
	void Std_Move(direction dir);
	//растет пацан
	void Grow(direction dir);

	//змея раскрывает свои координаты
	int** Get_Coords();
	//узнаем последнее направление движения головы
	direction Last_Move() { return body[body.size() - 1].Last_Move(); }
	//узнаем длину змеи
	int Lenght() { return body.size(); };

	//выдаем счет
	int Score() { return score; };

protected:
	vector<Body_Part> body;//тело змеи
	int score = 0;//набранные очки
	int score_to_grow = 2;//сколько очков надо набрать для роста змеи
};