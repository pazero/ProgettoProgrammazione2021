#include <ncurses.h>
#include "ClasseOggetto.hpp"
class Eroe:public Oggetto {
    protected:
    int life;   //vita dell'eroe
    
    public:
    Eroe();
    Eroe(position pos, int life);
    void go_up();   //metodo per saltare
    void go_down(); //metodo per scendere dalle piattaforme
    int getlife();  //ritorna la vita dell'eroe

    void damage(int danno); //infligge danni alla vita dell'eroe
    void bonus_life();  //metodo necessario al bonus "*": aumenta la vita dell'eroe
    void setlife(int n);    //imposta "life" come il parametro passato
};