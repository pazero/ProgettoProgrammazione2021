#include "ClasseOggetto.hpp"

Oggetto::Oggetto(position pos) {
    this->pos = pos;
}
Oggetto::Oggetto(){}

position Oggetto::getPos(){
    return pos;
}
int Oggetto::getPosy(){
    return(pos.y);
}
int Oggetto::getPosx(){
    return(pos.x);
}
//stampo l'oggetto sullo stdscr (schermo intero)
void Oggetto::show(){
    mvprintw(pos.y, pos.x, "%c",name);
    refresh();
}

char Oggetto::get_name() {
    return name;
}