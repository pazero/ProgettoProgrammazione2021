#include "Comandi.hpp"

Comandi::Comandi() {
        initscr(); //fa partire la modalità ncurses
        noecho(); //fa in modo che l'input da tastiera non venga mai stampato a schermo 
        keypad(stdscr, TRUE); //attiva l'utilizzo della tastiera
        curs_set(FALSE); //rende invisibile il cursore
        start_color(); //attiva la modalità a colori
    }