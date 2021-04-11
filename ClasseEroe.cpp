#include "ClasseEroe.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>
Eroe::Eroe():Oggetto(){}
Eroe::Eroe(position pos, int life):Oggetto(pos){
    this->life = life;
    this->gun = NULL;
    this->name = 'Y'
;}

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

void Eroe::add_bullet(position pos) {
    colpi tmp = new colpo;
    tmp->curr = Bullet(pos);
    tmp->next = gun;
    gun = tmp;
}

void Eroe::shoot(int player_x, int limit_dx){
    colpi aux = gun;
    colpi prec = NULL;
    while(aux!=NULL) {
        if(aux->curr.getPosx() == player_x) {
            aux->curr.go_dx();
        }
        else {
            if(aux->curr.getPosx()<limit_dx) {
                aux->curr.destroy_win();
                aux->curr.go_dx();
            }
            //if(aux->curr.getPosx()==limit_dx) {
            else {
                aux->curr.destroy_win();
                colpi tmp;
                if(prec == NULL){
                    tmp = aux;
                    aux = aux->next;
                    delete(tmp);
                    tmp = NULL;
                }
                else{
                    tmp = aux;
                    aux = aux->next;
                    prec->next = aux;
                    delete (tmp);
                    tmp = NULL;
                }
            }
        }
        prec = aux;
        aux = aux->next;
    }
}

void Eroe::count_bullet(){
    colpi aux = gun;
    int i=0;
    while(aux!=NULL) {
        aux=aux->next;
        i++;
    }
    mvprintw(0,COLS/2,"nbullet: %d ", i);
}