#include "Eroe.hpp"
Eroe::Eroe() : Oggetto() {}
Eroe::Eroe(position pos, int life) : Oggetto(pos)
{
    this->life = life;
    this->name = 'Y';
}

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
