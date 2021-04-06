#include "ClasseEroe.hpp"

Eroe::Eroe(position pos, int life){
    this->pos = pos;
    this->life = life;
}

void Eroe::go_up(){
    //quando chiamiamo la funzione siamo già nel caso ch==KEY_UP (vedi ClasseBigMap->slideMap)
    mvprintw(pos.y, pos.x, " ");
    pos.y -=2;
    show();
}

void Eroe::go_down(){
    mvprintw(pos.y, pos.x, " ");
    pos.y +=2;
    show();
}

int Eroe::getPosy(){
    return(pos.y);
}
int Eroe::getPosx(){
    return(pos.x);
}
void Eroe::show(){
    mvprintw(pos.y, pos.x, "%c",name);
    refresh();
}