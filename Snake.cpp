#include "Snake.h"



//������ ������ ����



//������������ ����� ����
//��������� ������� ����� ����
Body_Part::Body_Part(int* pos) {

	//������������ ����������
	place[0] = *pos++;
	place[1] = *pos;

	//�� ��������� ���������� �����
	//�� ����� ���� �� ��������
	prev_dir = RIGHT;
	type = TAIL;
}

//��������� �������, ��� ����� ���� � ����������� �� ���������� ����� ���� � ���� �����
Body_Part::Body_Part(int* pos, state new_type, direction dir) {

	//������������ ����������
	place[0] = *pos++;
	place[1] = *pos;

	//��� ����� ���� � ����������� ��� � ���������� ������������
	prev_dir = dir;
	type = new_type;
}

//���������� ����� ����
Body_Part::~Body_Part() {
	//delete place;
}


//������ ��� �� ����� ����
state Body_Part::Which() { return type; }

//������ ����������� ���������� ��������
direction Body_Part::Last_Move() { return prev_dir; }

//������ ��������� ����� ����
int* Body_Part::Position() {

	//������� ����� ������ � �������� � ���� ���������� ����� ����
	int* coords = new int[2];
	coords[0] = place[0];
	coords[1] = place[1];

	return coords;
}

//����������� ����� ���� � �������� �����������
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

	//���������� ������������
	prev_dir = new_dir;
}

//���� ����� ����� � ������ ���� �����
void Body_Part::Change(state new_type)
{
	type = new_type;
}



//������ ����



//����������� ���� �� ������������ ������� (1:1) �������� ������
Snake::Snake(int len)
{
	//���� � ����� ������ ������� �� �������
	if (len > 1) {
		//������� ������ ����
		int pos[2] = { 1,1 };

		//������� ����� � ����
		body.push_back(Body_Part(pos));

		//������� ���� ������ �����
		while (++pos[1] < len)
			body.push_back(Body_Part(pos, BODY, RIGHT));
		
		//������ ������ �� �����
		body.push_back(Body_Part(pos, HEAD, RIGHT));
	}
}

Snake::Snake()
{
	int pos[2] = { 1,1 };

	//������� ����� � ����
	body.push_back(Body_Part(pos));

	//�������� ����� ����� ���� ������
	pos[1]++;

	//������ ������ �� �����
	body.push_back(Body_Part(pos, HEAD, RIGHT));
}

Snake::~Snake()
{
	
}

//������ � ������������ ����� ���� 
Body_Part* Snake::Get_Part(int n)
{
	if (n >= 0 && n < Lenght())
		return &body[n];
	return nullptr;
}

//������ ���� 
//������������ ���������� � �����
bool Snake::Move(direction dir, state next_place)
{
	switch (next_place) {
	case FOOD: {
		//���� ��� - ���� ������
		score++;

		//���� ����� ���������� ��� �����, �� ������
		if (score % score_to_grow == 0)
			this->Grow(dir);
		else
			//����� ������� ��������
			this->Std_Move(dir);

		//�������� �� ������� ������������
		return true;
	}
	case EMPTY: {
		//������� ��������
		this->Std_Move(dir);

		//�������� �� ������� ������������
		return true;
	}
	case TAIL: {
		//������� ��������
		//����� �� ���������
		this->Std_Move(dir);

		//�������� �� ������� ������������
		return true;
	}
	default: {//��� �� ����� �� ��� � ������ �� ����������
		return false;
	}
	}
	return true;
}

//������� ����������� ���� �� ����������� ��� �����
void Snake::Std_Move(direction dir)
{
	//���������� ��� ������� �� ������� ������ ���� � �������������� ��������� � ��������� ����� ����
	int i = 0;

	//������� ��� ����� ������
	for (; i < body.size() - 1; i++)
		//����������� �������� ������ ����� ���� ����� �� ���������� �������� ���� ����� � ������
		body[i].Move(body[i + 1].Last_Move());

	//������� ������
	body[i].Move(dir);
}

//������ � �����
void Snake::Grow(direction dir)
{
	//����� �� ������� ��� ���� � ���������� �����
	//������ ����������� � ����, � ����� �������� � ������� ���
	body[body.size() - 1].Change(BODY);

	//������ ������� ������ ������
	int* pos = new int[2];
	pos = body[body.size() - 1].Position();
	//����� ����� ������ �� ����� ������
	Body_Part new_head(pos, HEAD, dir);
	//����� ������ �������� � ���
	new_head.Move(dir);

	//����� ������ �������������� � ����
	body.push_back(new_head);

	//������� ��������� ���������
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
