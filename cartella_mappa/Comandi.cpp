#include "Comandi.hpp"

Comandi::Comandi() {
        initscr();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(FALSE);
    }