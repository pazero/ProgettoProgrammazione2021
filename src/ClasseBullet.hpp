#include <ncurses.h>
#include "ClasseEroe.hpp"
class Bullet:public Oggetto{
    protected:
    WINDOW* win;

    public:
    Bullet();
    Bullet(position pos);
    void set_name(char name);
    WINDOW* create_win(); //crea una finestra per un proiettile
    void destroy_win(); //distrugge la finestra di un proiettile
    void go_dx(); //sposta a destra una finestra
    void go_sx(); //sposta a sinistra una finestra
};