#include <iostream>
#include "Skin.h"
#include "World.h"


int main()
{
    //пользователь вводит вариант оформления
    int n;
    std::cin >> n;
    Skin skin(n % 2 + 1);

    //собираем мир и отрисовываем его
    World world;
    skin.Show_World_Console(world.Get_Copy());

    //цикл на каждый ход с отрисовкой
    while (world.Next_Turn())
        skin.Show_World_Console(world.Get_Copy());
}
