#include <ncurses.h>
#include "ClasseEroe.hpp"
//sottoclasse di Oggetto
class Bullet:public Oggetto{
    protected:
    //i proiettili sono implementati come delle finestre
    WINDOW* win;

    public:
    Bullet();
    Bullet(position pos);
    void set_name(char name);   //imposta il nome come il parametro passato
    WINDOW* create_win();   //crea una nuova finestra proiettile
    void destroy_win(); //distrugge la finestra proiettile
    void go_dx();   //sposta il proiettile a destra
    void go_sx();   //sposta il proiettile a sinistra
};