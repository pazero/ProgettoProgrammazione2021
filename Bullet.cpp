#include "Bullet.hpp"

Bullet::Bullet():Oggetto(){}

Bullet::Bullet(position pos):Oggetto(pos) {
    this->pos = pos;
}

WINDOW* Bullet::create_win(){
	win = newwin(1, 1, pos.y, pos.x);
    wprintw(win,">");
	wrefresh(win);
	return win;
}

void Bullet::destroy_win(){
	wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(win);
	delwin(win);
}

void Bullet::go_dx() {
    this->pos.x++;
    win = create_win();
}

void Bullet::go_sx() {
    this->pos.x--;
    win = create_win();
}
int Bullet::getPosx() {
    return pos.x;
}
