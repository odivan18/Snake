#include "Skin.h"
#include<iostream>

void Skin::Show_World_Console(state** world)
{
    system("cls");

    for (int i = 0; i < W_Size; i++)
    {
        for (int j = 0; j < W_Size; j++)
            std::cout << Style(world[i][j]);

        std::cout << '\n';
    }
}