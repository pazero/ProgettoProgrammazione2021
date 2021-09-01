#include "ClasseMotore.hpp"

Motore::Motore(int rect_lines, int rect_cols) {
    infinita = BigMap(); //inizializzo infinita con il costruttore per inzializzare le color pairs
    //faccio partire il menu iniziale, se parte il gioco inizializzo alcuni campi
    if(start_menu()) {        
        clear(); //pulisco lo schermo
        this->rect_lines = rect_lines;
        this->rect_cols = rect_cols;
        refresh();

        dead = false; //se dead è true il gioco va in gameover
        infinita = BigMap(rect_lines, rect_cols); //inizializzo la mappa infinita richiamando il secondo costruttore di BigMap 

        time = 100; //ogni 100 ms il gioco si aggiorna automaticamente
        cicli_for_bonus = -1; //quando non ci sono bonus attivi deve essere -1
        nodi = 0; //numero di pezzi di mappa esplorati, ovvero numero di nodi della bilista infinita
        bonus_time = 0; //se non c'è il bonus "#" attivo, resta 0
        
        go_game(); //faccio partire il gioco
    }
    else {
        clear();
        endwin();
    }
}
//gestisce l'intero gioco e controlla se l'eroe è morto
void Motore::go_game(){
    while(!dead) {
        //la funzione timeout prende come argomento un intero che rappresenta il tempo in ms
        //che passa tra un ciclo e l'altro, senza che lo user prema tasti. Quindi maggiore è questo parametro,
        //maggiore è il tempo tra un ciclo e l'altro
        timeout(time + bonus_time);
        refresh();
        ch = getch();
        //controllo dell'eroe(vita e movimento)
        if(!move_all()) {
            dead = true;
        }
        //si preme F1 per mettere in pausa
        if(ch==KEY_F(1)) {
            if(!pause_menu()) {
                dead = true;
            };
        }
        update_time(); //aggiorno il tempo che passa tra un ciclo e l'altro
        //se ci sono bonus attivi richiamo il metodo che gestisce la loro durata
        if(cicli_for_bonus>-1) {
            check_cicli();
        }
    }
    //se dead = true chiudo il ciclo e la finestra
    death_menu();
    endwin();
}
//gestisce il movimento dell'eroe in base all'input dell'user
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
    if(ch == 'd') { //sparo a destra con "d"
        infinita.shoot();
    }
    if(ch == 'a') { //sparo a sinistra con "a"
        infinita.back_shoot();
    }
    //eseguo la routine di fine ciclo passando "right"
    //questa variabile serve ai metodi di BigMap che controllano le collisioni
    if(infinita.routine_fineciclo(right)){
        check_bonus();
        right = false;
        return true;
    }
    else
        return false;
}
//diminuisce la variabile "time" mano a mano che avanzo nel gioco, in modo
//da aumentare la velocità e, di conseguenza, la difficoltà del gioco
void Motore::update_time(){
    if(infinita.n_map() > nodi) {
        nodi = infinita.n_map();
        if(nodi%5 == 0)
        time -= 2;
    }
}
//controlla se ci sono bonus attivi e aggiorna "cicli_for_bonus"
void Motore::check_bonus() {
    char tmp = infinita.is_bonus();
    if(tmp == '#') {
        cicli_for_bonus++;
        bonus_time = 200; //il tempo bonus è 200ms, da sommare a "time"
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
//disattiva i bonus se sono attivi da più di 200 cicli
void Motore::check_cicli(){
    cicli_for_bonus++;
    if(cicli_for_bonus>200) {
        mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2 +25, "             ");
        infinita.set_killer_prize(1);
        bonus_time = 0;
        //se il bonus si disattiva, torna al valore di default -1
        cicli_for_bonus = -1;
    }
}
//menu del gameover
void Motore::death_menu() {
    clear();
    bool fine = false;;

    while(!fine) {
        print_gameOver();
        mvprintw(0,0, "Press ESC to exit");
        ch = getch();
        //esci con ESC (27 in ASCII)
        if(ch == 27) {
            fine = true;
        }
    }
}
//crea una finestra e stampa il gameover
void Motore::print_gameOver() {
    attroff(A_BOLD);
    WINDOW* death_win;
        int lines_win = 9+4;
        int cols_win = 90+4;
        int starty = (LINES - lines_win)/2;
        int startx = (COLS - cols_win)/2;

        death_win = newwin(lines_win, cols_win, starty, startx);
        refresh();
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
//menu della pausa
bool Motore::pause_menu(){
    clear();
    bool end_pause = false;
    mvwprintw(stdscr, LINES/2, (COLS-9)/2, "P A U S E");
    while(!end_pause){
        ch = getch();
        //con F1 riprendo il gioco
        if(ch== KEY_F(1)) {
            end_pause = true;
            return true;
        }
        //con ESC esco dal gioco
        if(ch== 27) {
            end_pause = true;
            return false;
        }
    }
    return false; 
}
//menu iniziale
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
    //inizializzo i 4 nodi della lista
    p_list tmp = new node;
    tmp->y = LINES/2 +3;
    tmp->x = COLS/2 - 4;
    strcpy(tmp->voce_menu, "EXIT");
    tmp->next = head;
    tmp->prev = NULL;
    head = tmp;

    tmp = new node;
    head->prev = tmp;
    tmp->y = LINES/2 +1;
    tmp->x = COLS/2 - 4;
    strcpy(tmp->voce_menu, "CREDITS");
    tmp->next = head;
    tmp->prev = NULL;
    head = tmp;

    tmp = new node;
    head->prev = tmp;
    tmp->y = LINES/2 -1;
    tmp->x = COLS/2 - 4;
    strcpy(tmp->voce_menu, "TUTORIAL");
    tmp->next = head;
    tmp->prev = NULL;
    head = tmp;

    tmp = new node;
    head->prev = tmp;
    tmp->y = LINES/2 -3;
    tmp->x = COLS/2 - 4;
    strcpy(tmp->voce_menu, "START");
    tmp->next = head;
    tmp->prev = NULL;
    head = tmp;
    //inizializzo la coda della lista
    p_list tail = head;
    while(tail->next != NULL) {
      tail = tail->next;
    }
    //creo una lista circolare
    tail->next = head;
    head->prev = tail;
    
    p_list aux = head;
    int choice = 1; //numero voce del menu
    bool finish_menu = false;
    //apro la finestra e la chiudo se "finish_menu == true"
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
      //aggiorniamo la scelta dell'user con frecce su e giù
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
      //si sceglie una voce del menu premendo invio (10 in ASCII)
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
//pagina del tutorial
void Motore::tutorial_page(){
    clear();
    int larghezza = 72;
    int altezza = 32;
    int starty = (LINES-altezza)/2;
    int startx = (COLS-larghezza)/2;
    WINDOW* tutorial_win = newwin(altezza,larghezza,starty,startx);
    refresh();
    mvwprintw(tutorial_win,0,0,"Hello, there. Here's how the game works!");
    
    mvwprintw(tutorial_win,2,0,"Y  this is you.");

    mvwprintw(tutorial_win,4,0,"Use arrows on your keyboard to move rightside and leftside,");
    mvwprintw(tutorial_win,5,0,"you can go up and down only if there is a platform above or under you");
    mvwprintw(tutorial_win,6,0,"or you can fall if the platform ends.");

    mvwprintw(tutorial_win,8,0,"You can shoot with D and backshooting with A.");
    
    mvwprintw(tutorial_win,10,0,"|  you can't pass through this walls.");

    mvwprintw(tutorial_win,13,0,"LIST OF ENEMIES (DON'T TOUCH THEM OR YOU'LL LOOSE LOTS OF YOUR LIFE!):");

    mvwprintw(tutorial_win,15,0,"K  is immortal and moves above the platform and on the ground");
    mvwprintw(tutorial_win,16,0,"A  is mortal and can't move but sometimes it puts its armor {[A]} on");
    mvwprintw(tutorial_win,17,0,"o  is a dangerous bubble that nothing can stop and deals little damage");
    

    mvwprintw(tutorial_win,20,0,"LIST OF BONUS:");

    mvwprintw(tutorial_win,22,0,"*  the rarest bonus that heals lots of your lost life");
    mvwprintw(tutorial_win,23,0,"#  the time goes slower for some time, so everything moves slowly");
    mvwprintw(tutorial_win,24,0,"&  you get double points killing anything for a range of time");
    mvwprintw(tutorial_win,25,0,"$  you immediately get 1000 extra-points");

    mvwprintw(tutorial_win,27,0,"You get points exploring the map and killing A-enemies and their armors.");

    mvwprintw(tutorial_win,29,0,"If you go back, you'll find everything as you left it.");

    mvwprintw(tutorial_win,31,0,"Press F1 to pause the game.");
    wrefresh(tutorial_win);
    mvprintw(0,0, "Press ESC to exit");
    while(ch!=27) {
        ch = getch();
    }
    clear();
}
//pagina dei crediti
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
    mvprintw(0,0, "Press ESC to exit");
    
    //esci con ESC (27 in ASCII)
    while(ch!=27) {
        ch = getch();
    }
    clear();
}