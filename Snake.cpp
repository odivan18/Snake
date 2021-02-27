#include "Snake.h"



//методы частей тела



//конструкторы части тела
//принимает позицию части тела
Body_Part::Body_Part(int* pos) {

	//переписываем координаты
	place[0] = *pos++;
	place[1] = *pos;

	//по умолчанию появляется хвост
	//не важно куда он двигался
	prev_dir = RIGHT;
	type = TAIL;
}

//принимает позицию, тип части тела и направление от предыдущей части тела к этой новой
Body_Part::Body_Part(int* pos, state new_type, direction dir) {

	//переписываем координаты
	place[0] = *pos++;
	place[1] = *pos;

	//тип части тела и направление как в аргументах конструктора
	prev_dir = dir;
	type = new_type;
}

//деструктор части тела
Body_Part::~Body_Part() {
	//delete place;
}


//узнаем что за часть тела
state Body_Part::Which() { return type; }

//узнаем направление последнего движения
direction Body_Part::Last_Move() { return prev_dir; }

//узнаем положение части тела
int* Body_Part::Position() {

	//создаем новый массив и копируем в него координаты части тела
	int* coords = new int[2];
	coords[0] = place[0];
	coords[1] = place[1];

	return coords;
}

//передвигаем часть тела в заданном направлении
void Body_Part::Move(direction new_dir) 
{
	switch (new_dir)
	{
	case UP: {
		place[0]--;
		break;
	}
	case DOWN: {
		place[0]++;
		break;
	}
	case LEFT: {
		place[1]--;
		break;
	}
	case RIGHT: {
		place[1]++;
		break;
	}
	default:
		break;
	}

	//запоминаем передвижение
	prev_dir = new_dir;
}

//если хвост отрос и старый стал телом
void Body_Part::Change(state new_type)
{
	type = new_type;
}



//методы змеи



//конструктор змеи из стандартоной позиции (1:1) движется вправо
Snake::Snake(int len)
{
	//змея с одной только головой не годится
	if (len > 1) {
		//позиции частей тела
		int pos[2] = { 1,1 };

		//создаем хвост в углу
		body.push_back(Body_Part(pos));

		//создаем тело нужной длины
		while (++pos[1] < len)
			body.push_back(Body_Part(pos, BODY, RIGHT));
		
		//ставим голосу на место
		body.push_back(Body_Part(pos, HEAD, RIGHT));
	}
}

Snake::Snake()
{
	int pos[2] = { 1,1 };

	//создаем хвост в углу
	body.push_back(Body_Part(pos));

	//сдвигаем спаун части тела вправо
	pos[1]++;

	//ставим голосу на место
	body.push_back(Body_Part(pos, HEAD, RIGHT));
}

Snake::~Snake()
{
	
}

//доступ к определеннйо части тела 
Body_Part* Snake::Get_Part(int n)
{
	if (n >= 0 && n < Lenght())
		return &body[n];
	return nullptr;
}

//двигем змею 
//передвижение начинается с конца
bool Snake::Move(direction dir, state next_place)
{
	switch (next_place) {
	case FOOD: {
		//есть еда - счет растет
		score++;

		//если очков достаточно для роста, то растем
		if (score % score_to_grow == 0)
			this->Grow(dir);
		else
			//иначе обычное движение
			this->Std_Move(dir);

		//сообщаем об удачном передвижении
		return true;
	}
	case EMPTY: {
		//обычное движение
		this->Std_Move(dir);

		//сообщаем об удачном передвижении
		return true;
	}
	case TAIL: {
		//обычное движение
		//хвост то сдвинется
		this->Std_Move(dir);

		//сообщаем об удачном передвижении
		return true;
	}
	default: {//что то пошло не так и змейка не справилась
		return false;
	}
	}
	return true;
}

//обычное перемещение тела по направлению без роста
void Snake::Std_Move(direction dir)
{
	//переменная для прохода по массиву частей тела и одновременного обращения к следующей части тела
	int i = 0;

	//двигаем все кроме головы
	for (; i < body.size() - 1; i++)
		//направление движения каждой части тела берем из последнего движения чати ближе к голове
		body[i].Move(body[i + 1].Last_Move());

	//двигаем голову
	body[i].Move(dir);
}

//наелся и вырос
void Snake::Grow(direction dir)
{
	//чтобы не двигать все тело и отращивать хвост
	//голова превратится в тело, а новыя отрастет в сторону еды
	body[body.size() - 1].Change(BODY);

	//узнаем позицию старой головы
	int* pos = new int[2];
	pos = body[body.size() - 1].Position();
	//спаун новой головы на месте старой
	Body_Part new_head(pos, HEAD, dir);
	//новая голова движется к еде
	new_head.Move(dir);

	//новая голова присоединяется к телу
	body.push_back(new_head);

	//удаляем временное хранилище
	delete[] pos;
}

int** Snake::Get_Coords()
{
	int** coords = new int* [body.size()];
	for (int i = 0; i < body.size();i++) 
		coords[i] = new int[2];
	
	for (int i = 0; i < body.size(); i++) {
		coords[i][0] = body[i].Position()[0];
		coords[i][1] = body[i].Position()[1];
	}

	return coords;
}
