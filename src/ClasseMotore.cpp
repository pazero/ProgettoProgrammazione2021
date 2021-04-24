#include "ClasseMotore.hpp"

Motore::Motore(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    this->infinita = BigMap(rect_lines, rect_cols);
    go_game();
}

void Motore::move_all() {
    infinita.update();
    
    if(ch == KEY_LEFT){
        infinita.go_left();
    }
    if(ch == KEY_RIGHT){
        infinita.go_right();
        right = true;
    }
    if(ch == KEY_UP) {
        infinita.go_up();
    }
    if(ch == 'e') {
        infinita.shoot();
    }
    infinita.routine_fineciclo(right);
    refresh();
    mvprintw(0,COLS/2,"%d", right);
    right = false;
}

void Motore::go_game(){
    infinita.set_count(3);
    while(!pause) {
        ch = getch();
        refresh();
        move_all();
        if(ch==KEY_F(1)) pause = true;
        timeout(50);
        
    }
    endwin();
}