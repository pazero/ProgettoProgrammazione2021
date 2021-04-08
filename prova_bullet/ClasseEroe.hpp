#include <ncurses.h>
#include "ClasseOggetto.hpp"

struct Bullet {
    position pos;
    Bullet *next;
};
typedef Bullet* colpi;
class Eroe:public Oggetto {
    protected:
    int life;
    char name = 'Y';
    colpi gun;

    public:
    Eroe(position pos, int life);
    void go_up();
    void go_down();
    position getPos();
    int getPosy();
    int getPosx();
    void show();
    void add_bullet(position pos);
};
