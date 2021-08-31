#include "Comandi.hpp"

Comandi::Comandi() {
        initscr();  //fa partire la modalità curses
        noecho();   
        keypad(stdscr, TRUE);   //attiva la tastiera
        curs_set(FALSE);    //rende invisibile il cursore
        start_color();  //attiva la modalità a colori
    }