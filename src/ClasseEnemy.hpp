#include <string.h>
#include <iostream>
#include <ncurses.h>
#include <ctime>
using namespace std;

#include "ClasseBonus.hpp"

//posizione assegnata rispetto al pad e non allo stdscr
class Enemy:public Oggetto{
    protected:
    int delay;  //intero usato per lo spawn delle corazze dei nemici "A"

    public:
    Enemy();
    Enemy(char name);
    
    void update_pos(position pos);  //aggiorna la posizione del nemico
    int get_delay();    //ritorna la variabile "delay"
};