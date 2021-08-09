#include <string.h>
#include <iostream>
#include <ncurses.h>
using namespace std;

#include "ClasseBonus.hpp"

//posizione rispetto a PAD
class Enemy:public Oggetto{
    protected:
    int n;
    int life;

    int rect_lines;
    int rect_cols;

    public:
    Enemy();
    Enemy(char name);
    //Enemy(int rect_lines, int rect_cols);
    bool empty (int y, int x);
    void Move(Enemy *tmp);
    position getPos();
    void reposition(Enemy *tmp);
    void show(Enemy *tmp);   
    void routine(int ch,Enemy nemici);

    void update_pos(position pos);
};