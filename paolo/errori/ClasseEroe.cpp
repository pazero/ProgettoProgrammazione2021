#include "ClasseEroe.hpp"

Eroe::Eroe(position pos, int life):Oggetto(pos){
    this->life = life;
    this->gun = NULL;
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
position Eroe::getPos(){
    return pos;
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

void Eroe::add_bullet(position pos) {
    colpi tmp = new Bullet;
    tmp->pos = pos;
    tmp->next = gun;
    gun = tmp;
}