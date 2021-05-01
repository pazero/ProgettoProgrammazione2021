#include <ncurses.h>
#include "Oggetto.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>
class Eroe : public Oggetto
{
protected:
    int life;

public:
    Eroe();
    Eroe(position pos, int life);
    void go_up();
    void go_down();
    int damage(int danno);
    int get_life(int life);
};