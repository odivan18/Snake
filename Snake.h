#pragma once
#include <vector>
#include "Globals.h"

using namespace std;

class Body_Part {
public:
	//������������ ������ ���� �� ������ ����� �����
	Body_Part(int* pos);//�� ��������� ������������� �����
	Body_Part(int* pos, state new_type, direction dir);//������ �����������

	~Body_Part();

	//������ ��� �� ����� ����
	state Which();

	//������ ����������� ���������� �������� ����� ����
	direction Last_Move();



	//������ ��� ����� ���� �����������
	int* Position();

	//������� ����� � �������� �����������
	void Move(direction new_dir);
	//����� ���� ���� ������ ���. ��������, ����� ������ � ������ ����� ������ � ����
	void Change(state new_type);

protected:
	int place[2];//���������� ����� ����
	state type;//��� ����� ����
	direction prev_dir;//���� ����� ���� ��������� � ��������� ���
};


class Snake {
public:
	//����������� ���� �� ������������ ������� (1:1) �������� ������
	Snake(int len);
	//� ������� (1:1) ����� ���� ������ 2 � �������� ������
	Snake();

	~Snake();

	//���� ��������� �� ����� ���� n
	Body_Part* Get_Part(int n);

	//���� ������ � �������� �����������
	//���� ���������� � ����������� ������ false
	bool Move(direction dir, state next_place);
	//��� �����
	void Std_Move(direction dir);
	//������ �����
	void Grow(direction dir);

	//���� ���������� ���� ����������
	int** Get_Coords();
	//������ ��������� ����������� �������� ������
	direction Last_Move() { return body[body.size() - 1].Last_Move(); }
	//������ ����� ����
	int Lenght() { return body.size(); };

	//������ ����
	int Score() { return score; };

protected:
	vector<Body_Part> body;//���� ����
	int score = 0;//��������� ����
	int score_to_grow = 2;//������� ����� ���� ������� ��� ����� ����
};