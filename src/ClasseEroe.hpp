#include <ncurses.h>
#include "ClasseBullet.hpp"

struct colpo {
    Bullet curr{};
    colpo *next;
};
typedef colpo* colpi;
class Eroe:public Oggetto {
    protected:
    int life;
    colpi gun;

    public:
    Eroe();
    Eroe(position pos, int life);
    void go_up();
    void go_down();
    void add_bullet(position pos);
    void update_shoot(int stacco,int rect_cols);
    //void count_bullet();
};