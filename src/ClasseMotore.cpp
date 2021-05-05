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

bool Motore::move_all() {
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
    if(ch == 'w') {
        infinita.back_shoot();
    }
    if(infinita.routine_fineciclo(right)){
        refresh();
        check_bonus();
        right = false;
        return true;
    }
    else
        return false;
}

void Motore::go_game(){
    
    while(!pause) {
        mvprintw(10,0,"time: %d  ", time+bonus);
        refresh();
        ch = getch();
        
        if(!move_all()) {
            pause = true;
        }
        if(ch==KEY_F(1)) pause = true;
        timeout(time + bonus);
        update_time();
    }
    death_menu();
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

void Motore::death_menu()
{
    clear();
    WINDOW *box_win;

    int altezza = 20;
    int larghezza = 20;
    int starty = (LINES - altezza) / 2;
    int startx = (COLS - larghezza) / 2;
    box_win = newwin(altezza,larghezza, starty, startx);
    refresh();
    box(box_win,0,0);
    mvwprintw(box_win,1,(larghezza-3)/2, "RIP");
    mvwprintw(box_win,3,(larghezza-6)/2, "ciccio");
    mvwprintw(box_win, (altezza-9) / 2, (larghezza-9) / 2, "SEI MORTO");
    wrefresh(box_win);
    bool fine;
    while(!fine) {
        ch = getch();
        //esci con o
        if(ch == 'o') fine = true;
    }
}

//NEMICI:
//movimento
//spari

//EROE:
//caduta dx e sx NON su nemico
//uccisione nemici bugga