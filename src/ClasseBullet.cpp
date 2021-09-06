#include "ClasseBullet.hpp"

Bullet::Bullet() {}

Bullet::Bullet(position pos) {
    this->pos = pos;
}

void Bullet::set_name(char name) {
    this->name = name;
}

//crea una finestra proiettile e la colora se è un nemico di tipo o
WINDOW* Bullet::create_win() {
	win = newwin(1, 1, pos.y, pos.x);
    if(name == 'o') {
        wattron(win, COLOR_PAIR(5));
        wprintw(win,"%c",name);
        wattroff(win, COLOR_PAIR(5));
    }
    else {
        wattron(win, COLOR_PAIR(2));
        wprintw(win,"%c",name);
        wattroff(win, COLOR_PAIR(2));
    }
	wrefresh(win);
	return win;
}
//svuota la finestra per poi distruggerla
void Bullet::destroy_win() {
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