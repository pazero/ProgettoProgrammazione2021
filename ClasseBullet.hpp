#include "ClasseOggetto.hpp"
#include <ncurses.h>
class Bullet{
    protected:
    position pos;
    char name = '>';

    WINDOW* win;
    
    public:
    Bullet();
    Bullet(position pos);
    WINDOW* create_win();
    void destroy_win();
    void go_dx();
    void go_sx();
    int getPosx();
};