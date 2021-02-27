#pragma once
#include <ctime>
#include <conio.h>

//размер игрового мира
const int W_Size = 20;

//стили игрового мира
const char Styles[2][7] = { "X0 HST","*| AWY" };
//возможные состояния клеток 
enum state { FOOD, BORDER, EMPTY, HEAD, BODY, TAIL };

//мув лист
const char Move_List_Keys[5] = { "wasd" };
//возможные ноправления движения
enum direction { UP, LEFT, DOWN, RIGHT };

//время на ход
const int Step_Time = 1000;




