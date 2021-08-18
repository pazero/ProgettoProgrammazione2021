#include "ClasseMotore.hpp"

Motore::Motore(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    refresh();

    dead = false;
    //pause = false;
    infinita = BigMap(rect_lines, rect_cols);

    time = 100;
    cicli_for_bonus = -1;
    nodi = 0;
    bonus_time = 0;
    
    go_game();
}

void Motore::go_game(){
    while(!dead) {
        refresh();
        ch = getch();
        if(!move_all()) {
            dead = true;
        }
        if(ch==KEY_F(1)) {
            pause_menu();
        }
        timeout(time + bonus_time);
        update_time();
        if(cicli_for_bonus>-1) {
            check_cicli();
        }
        
    }
    death_menu();
    endwin();
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
        check_bonus();
        right = false;
        return true;
    }
    else
        return false;
}

void Motore::update_time(){
    if(infinita.n_map() > nodi) {
        nodi = infinita.n_map();
        if(nodi%5 == 0)
        time -= 2;
    }
}

void Motore::check_bonus() {
    char tmp = infinita.is_bonus();
    if(tmp == '#') {
        cicli_for_bonus++;
        bonus_time = 200;
        attron(COLOR_PAIR(8));
        mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2 +25, " BONUS    # ");
        attroff(COLOR_PAIR(8));
    }
    if(tmp == '&') {
        cicli_for_bonus++;
        attron(COLOR_PAIR(8));
        mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2 +25, " BONUS    & ");
        attroff(COLOR_PAIR(8));
    }
}

void Motore::check_cicli(){
    cicli_for_bonus++;
    if(cicli_for_bonus>200) {
        attron(COLOR_PAIR(2));
        mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2 +25, " BONUS    NO ");
        attroff(COLOR_PAIR(2));
        infinita.set_killer_prize(1);
        bonus_time = 0;
        cicli_for_bonus = -1;
    }
}

void Motore::death_menu()
{
    clear();
    WINDOW *box_win;

    int altezza = 10;
    int larghezza = 19;
    int starty = (LINES - altezza) / 2;
    int startx = (COLS - larghezza) / 2;
    box_win = newwin(altezza,larghezza, starty, startx);
    refresh();
    wborder(box_win, '|', '|', ' ', '-', '/', '\\', '+', '+');
    for (int j = 1; j < 12; j++) {
        mvprintw((LINES - altezza)/2 - 4, (COLS - larghezza)/2 + 3 + j, "_");
    }
    for (int n = 1; n < 4; n++) {
    mvprintw((LINES - altezza)/2 - n, (COLS - larghezza)/2 + n, "/");
    }
    for (int i = 2; i < 5; i++) {
    mvprintw((LINES - altezza)/2 - (i-1), (COLS + larghezza)/2 - i, "\\");
    }
    mvwprintw(box_win,1,(larghezza-5)/2, "R.I.P.");
    mvwprintw(box_win,3,(larghezza-6)/2, "%s", "braghira");
    mvprintw(15, (COLS - 9)/2, "SEI MORTO");
    wrefresh(box_win);
    refresh();
    int punteggio = infinita.get_points();
    mvwprintw(stdscr, 10, (COLS-16)/2, " your score:  %d", punteggio );
    refresh();
    bool fine;
    while(!fine) {
        ch = getch();
        //esci con ESC (27 in ASCII)
        if(ch == 27) fine = true;
    }
}

void Motore::pause_menu(){
    clear();
    bool end_pause = false;
    mvwprintw(stdscr, LINES/2, (COLS-9)/2, "P A U S A");
    while(!end_pause){
        ch = getch();
        if(ch== KEY_F(1)) {
            end_pause = true;
        }
    }
    go_game();
}
