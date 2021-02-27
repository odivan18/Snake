#include "World.h"
#include "Globals.h"



//вспомогательные функции



//управление с клавиатуры
//ввод направления согласно мувлисту
//если игрок не успел выбрать направление движения, змея поползет в прежнем направлении
char Vvod(direction prev_dir)
{
    //таймер на ход
    int timer = clock();
    //кнопка последнего хода
    char temp = Move_List_Keys[prev_dir];

    //пока не вышло время на ход
    while (clock() - timer < Step_Time)
        //если была нажата кнопка
        if (_kbhit()) {
            //считываем нажатую клавишу
            temp = _getch();

            //проверяем, есть ли эта клавиша в управлении
            for (int i = 0; i < 4; i++)
                if (Move_List_Keys[i] == temp)
                    //возвращаем ее, если есть
                    return temp;
        }

    //если не было выбора за отведенное время, возвращаем прежнее направление
    return Move_List_Keys[prev_dir];
}

//переводим из символа в направление согласно мувлисту
direction char2dir(char ch)
{
    int i = -1;
    while (Move_List_Keys[++i] != ch);
    return (direction)i;
}



//методы мира



World::World()
{
    //выделяем место под игровое поле
    world = new state*[W_Size];
    for (int i = 0; i < W_Size; i++)
        world[i] = new state[W_Size];

    //определение поля
    for (int i = 0; i < W_Size; i++)
        for (int j = 0; j < W_Size; j++)
            //если клетка на границе, то так ее и называем
            if (i == 0 || j == 0 || i == W_Size - 1 || j == W_Size - 1)
                world[i][j] = BORDER;
            //иначе это просто пустая клетка
            else
                world[i][j] = EMPTY;

    //ставим змейку
    Put_Snake();
}

World::~World()
{

}

//функция на каждый ход
//возвращает истину, если еще можно играть
bool World::Next_Turn()
{
    //ввод игроком направления движения
    direction step = char2dir(Vvod(snake.Last_Move()));

    //перемещение змейки в заданном направлении
    //истина, если все хорошо
    bool temp = snake.Move(step, this->Next_Place(step));

    //запись нового положения змеи на поле
    Put_Snake();

    //спаун еды, если необходимо
    this->Food_Spawn();   

    //возвращаем истину, если все прошло хорошо и еще можно ходить
    return temp;
}

//спаун еды, если съедена
//применять после передвижения змеи
void World::Food_Spawn()
{
    //обновляем статус еды
    this->Food_Check();

    if (!is_food) 
        //крутим пока не заспаунится еда
        while (1) {
            //случайные новые координаты еды
            int n = rand() % (W_Size - 2) + 1,
                m = rand() % (W_Size - 2) + 1;

            //если на координатах ничего нет
            if (world[n][m] == EMPTY) {
                //ставим там еду и выходим из функции
                world[n][m] = FOOD;
                is_food = true;
                return;
            }
        }    
}

//проверяем, на месте ли еда
void World::Food_Check()
{
    //пробегаем по полю
    for(int i=1;i<W_Size-1;i++)
        for(int j=1;j<W_Size;j++)
            //если нашли еду - хорошо
            if (world[i][j] == FOOD) {
                is_food = true;
                return;
            }

    //не нашли - тоже хорошо
    is_food = false;
}

//удалить все упоминания о змее на карте
void World::Clear_Snake()
{
    //проходя по всему полю
    for (int i = 1; i < W_Size - 1; i++)
        for (int j = 1; j < W_Size - 1; j++)
            //если нашли часть тела змеи - стираем
            if (world[i][j] == HEAD || world[i][j] == BODY || world[i][j] == TAIL)
                world[i][j] = EMPTY;
}

//добавляем змейку на поле
void World::Put_Snake()
{
    //убираем старую змейку
    Clear_Snake();

    //временный указатель на часть тела змеи для удобного вывода
    Body_Part* temp;

    //проходим по всей длинне змеи
    for (int i = 0; i < snake.Lenght(); i++) {
        //от каждой части тела
        temp = snake.Get_Part(i);
        //по координатам записываем тип части тела
        world[temp->Position()[0]][temp->Position()[1]] = temp->Which();
    }
}

//тип клетки по заданному направлению от головы змеи
state World::Next_Place(direction dir)
{
    //задаем координаты для поиска
    int i = 0, j = 0;

    //проходим по всему полю
    for (i = 0; i < W_Size - 1; i++)
        for (j = 0; j < W_Size - 1; j++)
            if (world[i][j] == HEAD) {//если нашли голову, возвращаем статус клетки в нужном направлении
                switch (dir) {
                case UP:
                    return world[--i][j];
                case DOWN:
                    return world[++i][j];
                case LEFT:
                    return world[i][--j];
                case RIGHT:
                    return world[i][++j];
                default:
                    return world[i][j];
                }
            }
}

//создаем и выдаем копию мира
state** World::Get_Copy()
{
    //выделяем место
    state** copy = new state * [W_Size];
    for (int i = 0; i < W_Size; i++)
        copy[i] = new state[W_Size];

    //копируем
    for (int i = 0; i < W_Size; i++)
        for (int j = 0; j < W_Size; j++)
            copy[i][j] = world[i][j];

    //выдаем
    return copy;
}
