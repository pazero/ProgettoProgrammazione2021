#include <string.h>
#include <iostream>
#include <ncurses.h>
#include <ctime>
using namespace std;

#include "ClasseBonus.hpp"

//posizione rispetto a PAD
class Enemy:public Oggetto{
    protected:
    int n;
    int life;

    int rect_lines;
    int rect_cols;
    int delay;

    public:
    Enemy();
    Enemy(char name);
    
    void update_pos(position pos);
    int get_delay();
};