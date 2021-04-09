#include "ClasseEroe.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>
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
    //srand(time(0));
    //int c= rand()%100;
    //mvprintw(0,c,"o");
    colpi tmp = new Bullet;
    tmp->pos = pos;
    tmp->next = gun;
    gun = tmp;
}

void Eroe::shoot(int player_pos, int limit_dx){
    colpi aux = gun;
    while(aux!=NULL) {
        if(aux->pos.x == player_pos) {
            aux->pos.x++;
            mvprintw(aux->pos.y, aux->pos.x, "%c",aux->name);
        }
        else {
            if(aux->pos.x<limit_dx) {
                mvprintw(aux->pos.y, aux->pos.x," ");
                aux->pos.x++;
                mvprintw(aux->pos.y, aux->pos.x, "%c",aux->name);
            }
            if(aux->pos.x==limit_dx) {
                mvprintw(aux->pos.y, aux->pos.x," ");
            }
        }
        aux=aux->next;
    }
}