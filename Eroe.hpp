#include <ncurses.h>
#include "Lista.hpp"

class Eroe : public Oggetto
{
protected:
    int life;
    List colpo;

public:
    Eroe();
    Eroe(position pos, int life);
    void go_up();
    void go_down();
    void add_bullet(position pos);
    void update_shoot(int stacco, int rect_cols);
    //void count_bullet();
};