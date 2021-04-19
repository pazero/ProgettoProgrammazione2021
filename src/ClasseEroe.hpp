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
};