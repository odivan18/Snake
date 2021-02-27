#pragma once
#include "Globals.h"
#include <string.h>

class Skin {
public:
    Skin(int n) { strcpy_s(current_style, Styles[n - 1]); };
    //~Skin() { delete current_style; };

    char Head() { return current_style[HEAD]; };
    char Body() { return current_style[EMPTY]; };
    char Tail() { return current_style[TAIL]; };
    char Empty() { return current_style[EMPTY]; };
    char Border() { return current_style[BORDER]; };
    char Food() { return current_style[FOOD]; };

    char Style(state place) { return current_style[place]; };

    void Show_World_Console(state** world);
protected:
    char current_style[7];
};