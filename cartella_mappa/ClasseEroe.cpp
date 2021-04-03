#include "ClasseEroe.hpp"

Eroe::Eroe(position pos, int life ){
    this->pos = pos;
    this->life = life;
}

void Eroe::Move(int Move, bool up_plat){
    if(Move == KEY_UP && up_plat){
        mvprintw(pos.y, pos.x, " ");//cleen old 
        pos.y -=2;
        show();
    }
    /*
    if(Move == KEY_DOWN && empty(pos.y+1,pos.x)){
        mvprintw(pos.y, pos.x, " ");//cleen old
        pos.y ++;
    }*/
}

position Eroe::getPos(){
    return(pos);
}
void Eroe::show(){
    mvprintw(pos.y, pos.x, "%c",name);
}