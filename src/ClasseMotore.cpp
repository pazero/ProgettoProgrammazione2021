#include "ClasseMotore.hpp"

Motore::Motore(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    infinita = BigMap(rect_lines, rect_cols);
    time = 100;
    cicli_for_bonus = -1;
    aux_nodi = 0;
    bonus = 0;
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
    if(ch == KEY_DOWN) {
        infinita.go_down();
    }
    if(ch == 'e') {
        infinita.shoot();
    }
    infinita.routine_fineciclo(right);
    refresh();
    check_bonus();
    right = false;
}

void Motore::go_game(){
    
    while(!pause) {
        mvprintw(10,0,"time: %d  ", time+bonus);
        mvprintw(11,0,"aux_nodi: %d  ", aux_nodi);
        mvprintw(12,0,"nodi: %d  ", infinita.n_map());
        refresh();
        ch = getch();
        
        move_all();
        if(ch==KEY_F(1)) pause = true;
        timeout(time + bonus);
        update_time();
    }
    endwin();
}

void Motore::update_time(){
    if(aux_nodi<infinita.n_map()) {
        aux_nodi = infinita.n_map();
        if(infinita.n_map()%10 == 0) {
            time -= 2;
        }
    }
    count_n_cicli(100);
}

bool Motore::check_bonus() {
    if(infinita.is_bonus()) {
        cicli_for_bonus++;
        bonus = 100;
        return true;
    }
    return false;
}

void Motore::count_n_cicli(int n){
    if(cicli_for_bonus>-1) {
        cicli_for_bonus++;
        if(cicli_for_bonus>n) {
            cicli_for_bonus = -1;
            bonus = 0;
        }
    }
}

//NEMICI:
//movimento
//spari
//se colpiti spariscono