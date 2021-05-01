#include "ncurses.h"
#include "Eroe.hpp"
// questa classe crea una finestra 1x1 stampando ">" come proiettile
class Bullet : public Oggetto{
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
    position getPos();
};