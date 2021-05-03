#include <ncurses.h>
#include "ClasseOggetto.hpp"
class Eroe:public Oggetto {
    protected:
    int life;
    
    public:
    Eroe();
    Eroe(position pos, int life);
    void go_up();
    void go_down();
    int getlife();

    void damage(int danno);
    void bonus_life();
    void setlife(int n);
};