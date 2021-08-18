#include <ncurses.h>
#include "ClasseEroe.hpp"
class Bullet:public Oggetto{
    protected:
    WINDOW* win;

    public:
    Bullet();
    Bullet(position pos);
    void set_name(char name);
    WINDOW* create_win();
    void destroy_win();
    void go_dx();
    void go_sx();
};