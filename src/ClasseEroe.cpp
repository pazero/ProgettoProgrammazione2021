#include "ClasseEroe.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>
Eroe::Eroe():Oggetto(){}

Eroe::Eroe(position pos, int life):Oggetto(pos){
    this->life = life;
    this->name = 'Y';
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

void Eroe::damage(int danno)
{
    life -= danno;
}

void Eroe::bonus_life()
{
    if(life<=50) life += 50;
    else life = 100;    
}

void Eroe::setlife(int n){
    life = n;
}