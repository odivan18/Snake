#pragma once
#include <ctime>
#include <conio.h>

//������ �������� ����
const int W_Size = 20;

//����� �������� ����
const char Styles[2][7] = { "X0 HST","*| AWY" };
//��������� ��������� ������ 
enum state { FOOD, BORDER, EMPTY, HEAD, BODY, TAIL };

//��� ����
const char Move_List_Keys[5] = { "wasd" };
//��������� ����������� ��������
enum direction { UP, LEFT, DOWN, RIGHT };

//����� �� ���
const int Step_Time = 1000;




