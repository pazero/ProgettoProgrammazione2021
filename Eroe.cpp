#include "Eroe.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>
Eroe::Eroe() : Oggetto() {}
Eroe::Eroe(position pos, int life) : Oggetto(pos)
{
    this->life = life;
    this->colpo = NULL;
    this->name = 'Y';
}
//quando chiamiamo la funzione siamo già nel caso ch==KEY_UP (vedi WorldGen->slideMap)
void Eroe::go_up()
{
    mvprintw(pos.y, pos.x, " ");
    pos.y -= 2;
    show();
}
void Eroe::go_down()
{
    mvprintw(pos.y, pos.x, " ");
    pos.y += 2;
    show();
}
void Eroe::add_bullet(position pos) {
    List tmp = new Node;
    tmp->curr = Bullet(pos);
    tmp->next = colpo;
    colpo = tmp;
}
void Eroe::update_shoot(int player_x, int limit_dx){
    List aux = colpo;
    List prec = NULL;
    while(aux!=NULL) {
        if(aux->curr.getPosx() == player_x) {
            aux->curr.go_dx();
        }
        else {
            if(aux->curr.getPosx()<limit_dx-1) {
                aux->curr.destroy_win();
                aux->curr.go_dx();
            }
            //if(aux->curr.getPosx()==limit_dx) {
            else {
                aux->curr.destroy_win();
                List tmp;
                if(prec == NULL){
                    tmp = aux;
                    aux = aux->next;
                    delete(tmp);
                    tmp = NULL;
                    colpo = aux;
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
        if(aux!=NULL)
            aux = aux->next;
    }
}
/*
void Eroe::count_bullet(){
    colpi aux = gun;
    int i=0;
    while(aux!=NULL) {
        aux=aux->next;
        i++;
    }
    mvprintw(0,COLS/2,"nbullet: %d ", i);
}*/