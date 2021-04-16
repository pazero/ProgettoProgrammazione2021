#include "Oggetto.hpp"

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
void Oggetto::show(){
    mvprintw(pos.y, pos.x, "%c",name);
    refresh();
}