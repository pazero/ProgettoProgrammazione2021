#include "ClasseEroe.hpp"

Eroe::Eroe():Oggetto(){}

Eroe::Eroe(position pos, int life):Oggetto(pos){
    this->life = life;
    this->name = 'Y';   //eroe rappresentato da una "Y"
}

void Eroe::go_up(){
    mvprintw(pos.y, pos.x, " ");
    pos.y -=2;
    show();
}
void Eroe::go_down(){
    mvprintw(pos.y, pos.x, " ");
    pos.y +=2;
    show();
}

int Eroe::getlife(){
    return life;
}

void Eroe::damage(int danno){
    life -= danno;
}
//se la vita è sotto ai 50 punti, allora fa una somma, altrimenta la setta a 100
void Eroe::bonus_life(){
    //il bonus "*" dona 50 punti vita
    if(life<=50) life += 50;
    else life = 100;
}

void Eroe::setlife(int n){
    life = n;
}