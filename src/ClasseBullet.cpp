#include "ClasseBullet.hpp"

Bullet::Bullet(){}

Bullet::Bullet(position pos) {
    this->pos = pos;
    
}

void Bullet::set_name(char name) {
    this->name = name;
}
WINDOW* Bullet::create_win(){
	win = newwin(1, 1, pos.y, pos.x);
    wprintw(win,"%c",name);
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