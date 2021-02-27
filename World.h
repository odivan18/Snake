#pragma once
#include "Globals.h"
#include "Snake.h"

class World {
public:
	World();
	~World();

	//���� ���� �������� ������
	//���� ��� ������ � ����� ������ ������, ������ true
	bool Next_Turn();

	//������� ���, ���� �� ���
	void Food_Spawn();
	//���������, ���� �� �� ����� ���
	void Food_Check();

	//������� ���� � ����
	void Clear_Snake();
	//������ ����� ���� �� ����
	void Put_Snake();

	//��� ������ �� ��������� ����������� �� ������ ����
	state Next_Place(direction dir);

	//���������� ����� ���� ���, ��������, ��� ��������� 
	state** Get_Copy();

protected:
	state** world;//��� ������� ���
	Snake snake;//����
	bool is_food;//���� �� �� ����� ���
};