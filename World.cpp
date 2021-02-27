#include "World.h"
#include "Globals.h"



//��������������� �������



//���������� � ����������
//���� ����������� �������� ��������
//���� ����� �� ����� ������� ����������� ��������, ���� �������� � ������� �����������
char Vvod(direction prev_dir)
{
    //������ �� ���
    int timer = clock();
    //������ ���������� ����
    char temp = Move_List_Keys[prev_dir];

    //���� �� ����� ����� �� ���
    while (clock() - timer < Step_Time)
        //���� ���� ������ ������
        if (_kbhit()) {
            //��������� ������� �������
            temp = _getch();

            //���������, ���� �� ��� ������� � ����������
            for (int i = 0; i < 4; i++)
                if (Move_List_Keys[i] == temp)
                    //���������� ��, ���� ����
                    return temp;
        }

    //���� �� ���� ������ �� ���������� �����, ���������� ������� �����������
    return Move_List_Keys[prev_dir];
}

//��������� �� ������� � ����������� �������� ��������
direction char2dir(char ch)
{
    int i = -1;
    while (Move_List_Keys[++i] != ch);
    return (direction)i;
}



//������ ����



World::World()
{
    //�������� ����� ��� ������� ����
    world = new state*[W_Size];
    for (int i = 0; i < W_Size; i++)
        world[i] = new state[W_Size];

    //����������� ����
    for (int i = 0; i < W_Size; i++)
        for (int j = 0; j < W_Size; j++)
            //���� ������ �� �������, �� ��� �� � ��������
            if (i == 0 || j == 0 || i == W_Size - 1 || j == W_Size - 1)
                world[i][j] = BORDER;
            //����� ��� ������ ������ ������
            else
                world[i][j] = EMPTY;

    //������ ������
    Put_Snake();
}

World::~World()
{

}

//������� �� ������ ���
//���������� ������, ���� ��� ����� ������
bool World::Next_Turn()
{
    //���� ������� ����������� ��������
    direction step = char2dir(Vvod(snake.Last_Move()));

    //����������� ������ � �������� �����������
    //������, ���� ��� ������
    bool temp = snake.Move(step, this->Next_Place(step));

    //������ ������ ��������� ���� �� ����
    Put_Snake();

    //����� ���, ���� ����������
    this->Food_Spawn();   

    //���������� ������, ���� ��� ������ ������ � ��� ����� ������
    return temp;
}

//����� ���, ���� �������
//��������� ����� ������������ ����
void World::Food_Spawn()
{
    //��������� ������ ���
    this->Food_Check();

    if (!is_food) 
        //������ ���� �� ����������� ���
        while (1) {
            //��������� ����� ���������� ���
            int n = rand() % (W_Size - 2) + 1,
                m = rand() % (W_Size - 2) + 1;

            //���� �� ����������� ������ ���
            if (world[n][m] == EMPTY) {
                //������ ��� ��� � ������� �� �������
                world[n][m] = FOOD;
                is_food = true;
                return;
            }
        }    
}

//���������, �� ����� �� ���
void World::Food_Check()
{
    //��������� �� ����
    for(int i=1;i<W_Size-1;i++)
        for(int j=1;j<W_Size;j++)
            //���� ����� ��� - ������
            if (world[i][j] == FOOD) {
                is_food = true;
                return;
            }

    //�� ����� - ���� ������
    is_food = false;
}

//������� ��� ���������� � ���� �� �����
void World::Clear_Snake()
{
    //������� �� ����� ����
    for (int i = 1; i < W_Size - 1; i++)
        for (int j = 1; j < W_Size - 1; j++)
            //���� ����� ����� ���� ���� - �������
            if (world[i][j] == HEAD || world[i][j] == BODY || world[i][j] == TAIL)
                world[i][j] = EMPTY;
}

//��������� ������ �� ����
void World::Put_Snake()
{
    //������� ������ ������
    Clear_Snake();

    //��������� ��������� �� ����� ���� ���� ��� �������� ������
    Body_Part* temp;

    //�������� �� ���� ������ ����
    for (int i = 0; i < snake.Lenght(); i++) {
        //�� ������ ����� ����
        temp = snake.Get_Part(i);
        //�� ����������� ���������� ��� ����� ����
        world[temp->Position()[0]][temp->Position()[1]] = temp->Which();
    }
}

//��� ������ �� ��������� ����������� �� ������ ����
state World::Next_Place(direction dir)
{
    //������ ���������� ��� ������
    int i = 0, j = 0;

    //�������� �� ����� ����
    for (i = 0; i < W_Size - 1; i++)
        for (j = 0; j < W_Size - 1; j++)
            if (world[i][j] == HEAD) {//���� ����� ������, ���������� ������ ������ � ������ �����������
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

//������� � ������ ����� ����
state** World::Get_Copy()
{
    //�������� �����
    state** copy = new state * [W_Size];
    for (int i = 0; i < W_Size; i++)
        copy[i] = new state[W_Size];

    //��������
    for (int i = 0; i < W_Size; i++)
        for (int j = 0; j < W_Size; j++)
            copy[i][j] = world[i][j];

    //������
    return copy;
}
