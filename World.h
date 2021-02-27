#pragma once
#include "Globals.h"
#include "Snake.h"

class World {
public:
	World();
	~World();

	//один цикл движения змейки
	//если все хорошо и можно дальше играть, вернет true
	bool Next_Turn();

	//спаунит еду, если ее нет
	void Food_Spawn();
	//проверяет, есть ли на карте еда
	void Food_Check();

	//стирает змею с поля
	void Clear_Snake();
	//ставит новую змею на поле
	void Put_Snake();

	//тип клетки по заданному направлению от головы змеи
	state Next_Place(direction dir);

	//возвращает копию мира для, например, его отрисовки 
	state** Get_Copy();

protected:
	state** world;//сам игровой мир
	Snake snake;//змея
	bool is_food;//есть ли на карте еда
};