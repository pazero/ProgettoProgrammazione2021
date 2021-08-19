#include "ClasseMotore.hpp"

Motore::Motore(int rect_lines, int rect_cols) {
    infinita = BigMap();

    if(start_menu()) {
        clear();
        this->rect_lines = rect_lines;
        this->rect_cols = rect_cols;
        refresh();

        dead = false;
        infinita = BigMap(rect_lines, rect_cols);

        time = 100;
        cicli_for_bonus = -1;
        nodi = 0;
        bonus_time = 0;
        
        go_game();
    }
    else {
        clear();
        endwin();
    }
}

void Motore::go_game(){
    while(!dead) {
        timeout(time + bonus_time);
        refresh();
        ch = getch();
        if(!move_all()) {
            dead = true;
        }
        if(ch==KEY_F(1)) {
            pause_menu();
        }
        update_time();
        if(cicli_for_bonus>-1) {
            check_cicli();
        }
        if(ch == KEY_F(1)) {
            pause_menu();
        }
        if(ch == KEY_F(2)) {
            death_menu();
            dead = true;
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
    if(ch == 'd') {
        infinita.shoot();
    }
    if(ch == 'a') {
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
        //attron(COLOR_PAIR(2));
        //mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2 +25, " BONUS    NO ");
        mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2 +25, "             ");
        //attroff(COLOR_PAIR(2));
        infinita.set_killer_prize(1);
        bonus_time = 0;
        cicli_for_bonus = -1;
    }
}

void Motore::death_menu() {
    clear();
    bool fine = false;;
    ////bool pari = false;

    while(!fine) {/*
        print_gameOver();
        timeout(90);
        
        if(pari) {
            for(int i=0;i<LINES; i++) {
                attron(A_BOLD);
                if(i%4 == 0) {
                    attron(COLOR_PAIR(2));
                    for(int j=0; j<COLS; j++) {
                        if(j%2 == 0) {
                            mvprintw(i,j, ">");
                        }
                        else {
                            mvprintw(i,j, " ");
                        }
                    }
                    print_gameOver();
                }
                else {
                    if(i%2 == 0) {
                        attron(COLOR_PAIR(6));
                        for(int j=0; j<COLS; j++) {
                            if(j%2 != 0) {
                                mvprintw(i,j, "<");
                            }
                            else {
                                mvprintw(i,j, " ");
                            }
                        }
                    }
                    print_gameOver();
                }
            }
            refresh();
            pari = false;
        }
        else {
            print_gameOver();
            for(int i=0;i<LINES; i++) {
                attron(A_BOLD);
                if(i%4 == 0) {
                    attron(COLOR_PAIR(2));
                    for(int j=0; j<COLS; j++) {
                        if(j%2 != 0) {
                            mvprintw(i,j, ">");
                        }
                        else {
                            mvprintw(i,j, " ");
                        }
                    }
                    print_gameOver();
                }
                else {
                    if(i%2 == 0) {
                        attron(COLOR_PAIR(6));
                        for(int j=0; j<COLS; j++) {
                            if(j%2 == 0) {
                                mvprintw(i,j, "<");
                            }
                            else {
                                mvprintw(i,j, " ");
                            }
                        }
                    }
                    print_gameOver();
                }
                print_gameOver();
                attroff(COLOR_PAIR(2));
                attroff(COLOR_PAIR(6));
            }
            refresh();
            pari = true;
        }*/
        print_gameOver();
        
        ch = getch();
        //esci con ESC (27 in ASCII)
        if(ch == 27) {
            fine = true;
        }
    }
}
void Motore::print_gameOver() {
    attroff(A_BOLD);
    WINDOW* death_win;
        int lines_win = 9+4;
        int cols_win = 90+4;
        int starty = (LINES - lines_win)/2;
        int startx = (COLS - cols_win)/2;

        death_win = newwin(lines_win, cols_win, starty, startx);
        refresh();
        //wprintw(death_win, "CIAO");
        wattron(death_win,COLOR_PAIR(3));
        mvwprintw(death_win,2,2, " $$$$$$\\   $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\         $$$$$$\\ $$\\    $$\\  $$$$$$\\   $$$$$$\\");
        mvwprintw(death_win,3,2, "$$  __$$\\  \\____$$\\ $$  _$$  _$$\\ $$  __$$\\       $$  __$$\\\\$$\\  $$  |$$  __$$\\ $$  __$$\\");
        mvwprintw(death_win,4,2, "$$ /  $$ | $$$$$$$ |$$ / $$ / $$ |$$$$$$$$ |      $$ /  $$ |\\$$\\$$  / $$$$$$$$ |$$ |  \\__|");
        mvwprintw(death_win,5,2, "$$ |  $$ |$$  __$$ |$$ | $$ | $$ |$$   ____|      $$ |  $$ | \\$$$  /  $$   ____|$$ |");
        mvwprintw(death_win,6,2, "\\$$$$$$$ |\\$$$$$$$ |$$ | $$ | $$ |\\$$$$$$$\\       \\$$$$$$  |  \\$  /   \\$$$$$$$\\ $$ |");
        mvwprintw(death_win,7,2, " \\____$$ | \\_______|\\__| \\__| \\__| \\_______|       \\______/    \\_/     \\_______|\\__|");
        mvwprintw(death_win,8,2, "$$\\   $$ |");
        mvwprintw(death_win,9,2, "\\$$$$$$  | ");
        mvwprintw(death_win,10,2, " \\______/                                       YOU TOTALIZED %d POINTS", infinita.get_points());
        wattroff(death_win, COLOR_PAIR(3));

        wrefresh(death_win);
        refresh();
}
void Motore::pause_menu(){
    clear();
    bool end_pause = false;
    mvwprintw(stdscr, LINES/2, (COLS-9)/2, "P A U S E");
    while(!end_pause){
        ch = getch();
        if(ch== KEY_F(1)) {
            end_pause = true;
        }
    }
    go_game();
}

bool Motore::start_menu(){
    struct node {
        char voce_menu[20];
        int y;
        int x;
        node *next;
        node *prev;
    };
    typedef node* p_list;
    p_list head = NULL;
    //inizializza la lista
    p_list tmp = new node;
    tmp->y = 7;
    tmp->x = 1;
    strcpy(tmp->voce_menu, "EXIT");
    tmp->next = head;
    tmp->prev = NULL;
    head = tmp;

    tmp = new node;
    head->prev = tmp;
    tmp->y = 5;
    tmp->x = 1;
    strcpy(tmp->voce_menu, "CREDITS");
    tmp->next = head;
    tmp->prev = NULL;
    head = tmp;

    tmp = new node;
    head->prev = tmp;
    tmp->y = 3;
    tmp->x = 1;
    strcpy(tmp->voce_menu, "TUTORIAL");
    tmp->next = head;
    tmp->prev = NULL;
    head = tmp;

    tmp = new node;
    head->prev = tmp;
    tmp->y = 1;
    tmp->x = 1;
    strcpy(tmp->voce_menu, "START");
    tmp->next = head;
    tmp->prev = NULL;
    head = tmp;

    p_list tail = head;
    while(tail->next != NULL) {
      tail = tail->next;
    }
    tail->next = head;
    head->prev = tail;
    
    p_list aux = head;
    int choice = 1;
    bool finish_menu = false;

    while(!finish_menu) {        
      for(int i=1; i<=4; i++) {
        if(i==choice) {
          attron(COLOR_PAIR(9));
        }
        mvprintw(aux->y, aux->x, "%s", aux->voce_menu);
        aux = aux->next;
        attroff(COLOR_PAIR(9));
      }
      ch = getch();
      //aggiorniamo scelta con frecce su e giu
      if(ch==KEY_UP) {
        choice--;
        if(choice==0) {
          choice = 4;
        }
      }
      if(ch==KEY_DOWN) {
        choice++;
        if(choice==5) {
          choice = 1;
        }
      }
      //ENTER
      if(ch==10) {
        if(choice==1) {
            clear();
            finish_menu = true;
        }
        if(choice==2) {
          tutorial_page();
        }
        if(choice==3){
          credit_page();
        }
        if(choice==4){
            return false;
        }
      }
      refresh();
    }
    return true;
}

void Motore::tutorial_page(){
//K , {[A]} , o , movimenti, spari ,| , # , & , $ , * , F1
/*
    "Hello, there. Here's how the game works!"
    
    "Y  this is you"
    "if you have a platform above you, you can go up with the up arrow, the same down"
    "you can shoot with D and backshooting with A"

    "ENEMIES:"
    "K  is immortal and it moves above the platform and on the ground"
    "A  is mortal and it can't move but sometimes it put its armor {[A]} on"
    "you get points going on in the map and killing A-enemies and their armors"

    "BONUS:"
    "*  the rarest bonus that heal lots of your lost life"
    "#  the time go slower for 20 seconds, so everything moves slowly"
    "&  you get double points killing anything for 20 seconds"
    "$  you immediately get 1000 extra-points"
*/
    while(ch!=27) {
        ch = getch();
    }
    clear();
}
void Motore::credit_page(){
    clear();
    int larghezza = 33;
    int altezza = 11;
    int starty = (LINES-altezza)/2;
    int startx = (COLS-larghezza)/2;
    WINDOW* credit_win = newwin(altezza,larghezza,starty,startx);
    refresh();
    mvwprintw(credit_win,1,1,"A.A. 2020/21");
    mvwprintw(credit_win,2,1,"ALMA MATER STUDIORUM");
    mvwprintw(credit_win,3,1,"LAUREA TRIENNALE IN INFORMATICA");
    mvwprintw(credit_win,5,1,"SVILUPPATORI:");
    mvwprintw(credit_win,7,1,"SIMONE FOLLI");
    mvwprintw(credit_win,8,1,"ANDREA VENTUROLI");
    mvwprintw(credit_win,9,1,"PAOLO CERONI");
    wrefresh(credit_win);
    
    //esci con ESC (27 in ASCII)
    while(ch!=27) {
        ch = getch();
    }
    clear();
}
