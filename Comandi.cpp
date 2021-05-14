#include "Comandi.hpp"

Comandi::Comandi() {
        initscr();
        start_color(); 
        noecho();
        keypad(stdscr, TRUE);
        curs_set(FALSE);
    }