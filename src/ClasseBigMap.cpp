#include "ClasseBigMap.hpp"
BigMap::BigMap(){
    //inizializzazione delle coppie di colori che si utilizzeranno
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_GREEN);
    init_pair(8, COLOR_RED, COLOR_YELLOW);
}
BigMap::BigMap(int rect_lines, int rect_cols) {
    //dimensione della finestra di gioco
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    //numero di mappe, ovvero numero di nodi della lista bidirezionale, che formano la grande mappa infinita
    nodi = 1;
    //contatori per gestire gli spari
    count_Bullet=3;
    count_backBullet=3;
    count_ghostBullet=3;
    //posizione fissa del personaggio che ha un certo stacco dal margine sinistro della finestra
    stacco = 30;
    //inizializzazione primo nodo della mappa infinita
    curr->piece = new Map(rect_lines, rect_cols, nodi, true);
    curr->piece->build();
    curr->piece->show();
    curr->n = 1;
    curr->next = NULL;
    curr->prev = NULL;
    //inizializzazione Eroe
    position MarioPos = {(LINES+rect_lines)/2 -3, (COLS-rect_cols)/2 +stacco};
    int life = 100;
    Mario = Eroe(MarioPos, life);
    Mario.show();
    gun = NULL;
    backGun = NULL;
    ghostGun = NULL;

    points = 0;
    //setta la variabile che serve a gestire il bonus &
    set_killer_prize(1);

    attron(COLOR_PAIR(6));
    mvprintw((LINES - rect_lines)/2 - 4, (COLS-rect_cols)/2 + 10, "LIFE");
    attroff(COLOR_PAIR(6));
    //inizializzazione barra della vita
    health_bar();
    attron(COLOR_PAIR(3));
    mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2, "POINTS    %d", points);
    attroff(COLOR_PAIR(3));
    //variabile per sapere se colorare di rosso l'Eroe dopo che ha subito danno
    warning = false;
}

bool BigMap::get_warning() {
    return warning;
}
//funzione per aggiungere un nodo alla bilista allungando così la mappa
void BigMap::addMap() {
    nodi++;
    if(nodi>2) {
        points = points +  50;
    }
    MapList aux = curr;
    MapList prec = NULL;
    while(aux->next!=NULL) {
        aux = aux->next;
    }
    prec = aux;
    aux->next = new MapNode;
    aux->next->piece = new Map(rect_lines, rect_cols, nodi);
    aux->next->piece->build();

    aux->next->n = nodi;
    aux->next->next = NULL;
    aux->next->prev = prec;
    
    prec = NULL;
    delete(prec);
}

void BigMap::update() {
    Mario.show();
    //contatori per gli spari
    count_Bullet++;
    count_backBullet++;
    count_ghostBullet++;
    //se il nodo principale (curr) non ha un next, lo si aggiunge per assicurarsi che la mappa sia infinita
    if(curr->next==NULL) {
        addMap();
    }
    //verifica qual è il pezzo di mappa più presente in quel momento nella finestra di gioco e lo si rende curr, ovvero quello principale
    if(curr->piece->how_much() < curr->next->piece->how_much()) {
        curr = curr->next;
    }
    if(curr->prev!=NULL) {
            if(curr->piece->how_much() < curr->prev->piece->how_much()) {
                curr = curr->prev;
            }
        }
    Mario.show();
}
//metodo per spostare tutta la mappa a destra in modo da "spostare" il personaggio a sinistra
void BigMap::go_left(){
    Mario.show();
    //verifica che non ci siano sul percorso nemici o oggetti invalicabili
    if(not_this('|', false, Mario.getPos(), false) && not_this('K', false, Mario.getPos(), false) && not_this('{', false, Mario.getPos(), false) && not_this('}', false, Mario.getPos(), false) && not_this('[', false, Mario.getPos(), false) && not_this(']', false, Mario.getPos(), false)) {
        curr->piece->lslide();
        Mario.show();
        if(curr->next!=NULL) {
            curr->next->piece->lslide();
            Mario.show();
        }
        if(curr->prev!=NULL) {
            //verifica se il nodo prev è attualmente visibile sullo schermo
            if(curr->piece->previous())
                curr->prev->piece->lslide();
            Mario.show();
        }
        Mario.show();
        //se l'Eroe cade da una piattaforma lo si fa scendere finchè non si incontra una pittaforma o il piano terreno
        while (Mario.getPosy()<(LINES+rect_lines)/2 -3 && free_down(Mario.getPosy() - (LINES-rect_lines)/2))
            Mario.go_down();
        Mario.show();
        //si aggiorna il movimento degli spari in avanti dell'Eroe (se presenti)
        update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1, false);
    }
    Mario.show();
}

void BigMap::go_right()
{
    Mario.show();
    //verifica che non ci siano sul percorso nemici o oggetti invalicabili
    if(not_this('|', true, Mario.getPos(), false) && not_this('K', true, Mario.getPos(), false) && not_this('{', true, Mario.getPos(), false) && not_this('}', true, Mario.getPos(), false) && not_this('[', true, Mario.getPos(), false) && not_this(']', true, Mario.getPos(), false)) {
    //if(!not_this(' ', true, Mario.getPos(), false) || !not_this('*', true, Mario.getPos(), false) || !not_this('#', true, Mario.getPos(), false)){
        curr->piece->rslide();
        Mario.show();
        if (curr->next != NULL) {
            //verifica se il nodo next è attualmente visibile sullo schermo
            if (curr->piece->nx()){
                curr->next->piece->rslide();
                Mario.show();
            }
        }
        if (curr->prev != NULL)
            curr->prev->piece->rslide();
        Mario.show();
        //se l'Eroe cade da una piattaforma lo si fa scendere finchè non si incontra una pittaforma o il piano terreno
        while (Mario.getPosy() < (LINES + rect_lines) / 2 - 3 && free_down(Mario.getPosy() - (LINES - rect_lines) / 2)) {
            Mario.go_down();
        }
        Mario.show();
        //si aggiorna il movimento degli spari indietro dell'Eroe (se presenti)
        update_back_shoot((COLS+rect_cols)/2-1 - rect_cols, Mario.getPosx(), right);
        //si aggiorna il movimento dei nemici o
        update_ghost_shoot();
    }
    Mario.show();
}
//si sposta su di uno spazio l'Eroe
void BigMap::go_up(){
    //si trova la coordinata rispetto alla finestra di gioco (anzichè rispetto a tutto lo schermo)
    int y_on_pad = Mario.getPosy() - (LINES-rect_lines)/2;
    //si capisce in che pezzo di mappa è l'Eroe (se prev, curr o next)
    if(curr->prev!=NULL) {
        if(curr->prev->piece->how_much()>=stacco) {
            if(curr->prev->piece->can_pass_through(y_on_pad,stacco + rect_cols - curr->prev->piece->how_much()-1, true)){
                Mario.go_up();
            }
        }
        else {
            if(curr->prev->piece->how_much()>-1) {
                if(curr->piece->can_pass_through(y_on_pad,curr->piece->how_much() - rect_cols + stacco+1, true)){
                    Mario.go_up();
                }
            }
            else {
                if(curr->piece->can_pass_through(y_on_pad,rect_cols - curr->piece->how_much() + stacco-1, true)){
                    Mario.go_up();
                }
            }
        }
    }
}
//si sposta giù di uno spazio l'Eroe
void BigMap::go_down() {
    //si trova la coordinata rispetto alla finestra di gioco (anzichè rispetto a tutto lo schermo)
    int y_on_pad = Mario.getPosy() - (LINES-rect_lines)/2;
    //si capisce in che pezzo di mappa è l'Eroe (se prev, curr o next)
    if(curr->prev!=NULL) {
        if(curr->prev->piece->how_much()>=stacco) {
            if(curr->prev->piece->can_pass_through(y_on_pad,stacco + rect_cols - curr->prev->piece->how_much()-1, false)){
                Mario.go_down();
            }
        }
        else {
            if(curr->prev->piece->how_much()>-1) {
                if(curr->piece->can_pass_through(y_on_pad,curr->piece->how_much() - rect_cols + stacco+1, false)){
                    Mario.go_down();
                }
            }
            else {
                if(curr->piece->can_pass_through(y_on_pad,rect_cols - curr->piece->how_much() + stacco-1, false)){
                    Mario.go_down();
                }
            }
        }
    }
}
//metodo per sparare un colpo > in avanti
void BigMap::shoot(){
    //si spara solo ogni 3 cicli, ovvero quando count_Bullet arriva a 3 per evitare intoppi
    if(count_Bullet/3 > 0) {
        add_bullet(Mario.getPos());
        count_Bullet=0;
    }
}
//metodo per sparare un colpo < indietro
void BigMap::back_shoot(){
    //si spara solo ogni 3 cicli, ovvero quando count_backBullet arriva a 3 per evitare intoppi
    if(count_backBullet/3 > 0) {
        add_backbullet(Mario.getPos());
        count_backBullet=0;
    }
}

//metodo per cancellare un carattere dalla mappa
void BigMap::delete_char(int y, int x){
    Mario.show();
    //si trovano le coordinate rispetto alla finestra di gioco (anzichè rispetto a tutto lo schermo)
    int y_on_pad = y - (LINES-rect_lines)/2;
    int x_on_pad = x - (COLS-rect_cols)/2;
    //si capisce in che pezzo di mappa è l'Eroe (se prev, curr o next)
    if(curr->prev!=NULL) {
        if(curr->prev->piece->how_much() >= x_on_pad) {
            curr->prev->piece->print_space(y_on_pad, x_on_pad + rect_cols - curr->prev->piece->how_much() - 1);
            Mario.show();
            curr->prev->piece->remove_enemy({y_on_pad, x_on_pad + rect_cols - curr->prev->piece->how_much() - 1});
        }
        else{
            if (curr->prev->piece->how_much()>-1) {
                curr->piece->print_space(y_on_pad, curr->piece->how_much() - rect_cols + x_on_pad + 1);
                curr->piece->remove_enemy({y_on_pad, curr->piece->how_much() - rect_cols + x_on_pad + 1});
                Mario.show();
            }
            else {
                if(x_on_pad >= curr->piece->how_much()) {
                    curr->next->piece->print_space(y_on_pad, x_on_pad - curr->piece->how_much()-1);
                    curr->next->piece->remove_enemy({y_on_pad, x_on_pad - curr->piece->how_much()-1});
                }
                else{
                    curr->piece->print_space(y_on_pad, rect_cols - curr->piece->how_much() + x_on_pad - 1);
                    curr->piece->remove_enemy({y_on_pad, rect_cols - curr->piece->how_much() + x_on_pad - 1});
                }
                Mario.show();
            }
        }
        Mario.show();
    }
    else {
        if(x_on_pad >= curr->piece->how_much()) {
            curr->next->piece->print_space(y_on_pad, x_on_pad - curr->piece->how_much()-1);
            curr->next->piece->remove_enemy({y_on_pad, x_on_pad - curr->piece->how_much()-1});
        }
        else{
            curr->piece->print_space(y_on_pad,rect_cols - curr->piece->how_much() + x_on_pad-1);
            curr->piece->remove_enemy({y_on_pad,rect_cols - curr->piece->how_much() + x_on_pad-1});
        }
        Mario.show();
    }
}
//metodo che verifica se la posizione al di sotto dell'Eroe è libera
bool BigMap::free_down(int y_on_pad) {
    Mario.show();
    if(curr->prev!=NULL) {
        if(curr->prev->piece->how_much()>=stacco)
            return curr->prev->piece->can_fall(y_on_pad,stacco + rect_cols - curr->prev->piece->how_much()-1);
        else {
            if (curr->prev->piece->how_much()>-1) {
                return curr->piece->can_fall(y_on_pad,curr->piece->how_much() - rect_cols + stacco+1);
            }
            else {
                return curr->piece->can_fall(y_on_pad,rect_cols - curr->piece->how_much() + stacco-1);
            }
        }
    }
    Mario.show();
    return false;
}
//si aggiunge un nodo alla lista gun che tiene conto degli spari in avanti
void BigMap::add_bullet(position pos) {
    Mario.show();
    colpi tmp = new colpo;
    tmp->curr = Bullet(pos);
    tmp->curr.set_name('>');
    tmp->next = gun;
    gun = tmp;
}
//si aggiunge un nodo alla lista backGun che tiene conto degli spari indietro
void BigMap::add_backbullet(position pos) {
    Mario.show();
    colpi tmp = new colpo;
    tmp->curr = Bullet(pos);
    tmp->curr.set_name('<');
    tmp->next = backGun;
    backGun = tmp;
}
//si aggiunge un nodo alla lista ghostGun che tiene conto degli spari nemici che arrivano da destra
void BigMap::add_ghost_bullet(int y) {
    Mario.show();
    colpi tmp = new colpo;
    tmp->curr = Bullet({y + (LINES - rect_lines)/2,rect_cols + (COLS - rect_cols)/2});
    tmp->curr.set_name('o');
    tmp->next = ghostGun;
    ghostGun = tmp;
}
//si rimuove da una determinata lista di spari un nodo, in quanto quello sparo deve scomparire
void BigMap::remove_bullet(colpi &prec, colpi &aux, int type){
    Mario.show();
    colpi tmp;
    if(prec == NULL){
        tmp = aux;
        aux = aux->next;
        delete(tmp);
        tmp = NULL;
        if(type == 0)
            gun = aux;
        if(type == 1)
            backGun = aux;
        if(type == 2)
            ghostGun = aux;
    }
    else{
        tmp = aux;
        aux = aux->next;
        prec->next = aux;
        delete (tmp);
        tmp = NULL;
    }
}
//metodo per aggiornare il movimento degli spari in avanti
void BigMap::update_shoot(int limit_sx, int limit_dx, bool going_right){
    colpi aux = gun;
    colpi prec = NULL;
    //si scorre tutta lista gun
    while(aux!=NULL) {
        Mario.show();
        //caso in cui lo sparo è appena partito
        if(aux->curr.getPosx()==limit_sx) {
            //verifica che non ci siano | oppure K sul percorso
            if(not_this('|', true, aux->curr.getPos(), going_right) && not_this('K', true, aux->curr.getPos(), going_right)) {
                //verifica se c'è un nemico A sul percorso, in quanto questo va eliminato 
                if(!not_this('A', true, aux->curr.getPos(), going_right)) {
                    if(going_right)
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                    delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                    remove_bullet(prec,aux, 0);
                    Mario.show();
                    points = points +  100*killer_prize;
                }
                else {
                    //verifica che  ci siano { oppure [ oppure ] oppure } sul percorso
                    if(!not_this('{', true, aux->curr.getPos(), going_right) || !not_this('[', true, aux->curr.getPos(), going_right) || !not_this('}', true, aux->curr.getPos(), going_right) || !not_this(']', true, aux->curr.getPos(), going_right)) {
                        if(going_right)
                            delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                        remove_bullet(prec,aux, 0);
                        Mario.show();
                        points = points +  50*killer_prize;
                    }
                    //se non c'è nulla il proiettile avanza
                    else {
                        aux->curr.go_dx();
                        Mario.show();
                    }
                }
            }
            //se ci sono | o K sl percorso, si elimina il proiettile
            else{
                remove_bullet(prec, aux, 0);
            }
            Mario.show();
        }
        else {
            //si verifica che il proiettile non sia arrivato alla fine della finestra di gioco
            if(aux->curr.getPosx()<limit_dx) {
                aux->curr.destroy_win();
                Mario.show();
                //verifica che non ci siano | oppure K sul percorso
                if(not_this('|', true, aux->curr.getPos(), going_right) && not_this('K', true, aux->curr.getPos(), going_right)) {
                    //verifica se c'è un nemico A sul percorso, in quanto questo va eliminato
                    if(!not_this('A', true, aux->curr.getPos(), going_right)){
                        if(going_right)
                            delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                        remove_bullet(prec,aux, 0);
                        Mario.show();
                        points = points +  100*killer_prize;
                    }
                    else {
                        //verifica che  ci siano { oppure [ oppure ] oppure } sul percorso
                        if(!not_this('{', true, aux->curr.getPos(), going_right) || !not_this('[', true, aux->curr.getPos(), going_right) || !not_this('}', true, aux->curr.getPos(), going_right) || !not_this(']', true, aux->curr.getPos(), going_right)) {
                            if(going_right)
                                delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                            delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                            remove_bullet(prec,aux, 0);
                            Mario.show();
                            points = points +  50*killer_prize;
                        }
                        //se non c'è nulla il proiettile avanza
                        else {
                            aux->curr.go_dx();
                            Mario.show();
                        }
                    }
                }
                //se ci sono | o K sl percorso, si elimina il proiettile
                else{
                    remove_bullet(prec, aux, 0);
                }
                Mario.show();
            }
            //se ci sono | o K sl percorso, si elimina il proiettile
            else {
                aux->curr.destroy_win();
                remove_bullet(prec, aux, 0);
            }
            Mario.show();
        }
        prec = aux;
        if(aux!=NULL)
            aux = aux->next;
    }
}
//metodo per aggiornare il movimento degli spari indietro
//funzionamento identico al metodo update_shoot ma per sparare indietro (ovvero a sinistra)
void BigMap::update_back_shoot(int limit_sx, int limit_dx, bool going_right){
    colpi aux = backGun;
    colpi prec = NULL;
    while(aux!=NULL) {
        Mario.show();
        if(aux->curr.getPosx()==limit_dx) {
            if(not_this('|', false, aux->curr.getPos(), going_right) && not_this('K', false, aux->curr.getPos(), going_right)) {
                if(!not_this('A', false, aux->curr.getPos(), going_right)){
                    if(!going_right)
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                    delete_char(aux->curr.getPosy(), aux->curr.getPosx()-1);
                    remove_bullet(prec,aux, 1);
                    points = points +  100*killer_prize;
                }
                else {
                    if(!not_this('}', false, aux->curr.getPos(), going_right) || !not_this(']', false, aux->curr.getPos(), going_right) || !not_this('{', false, aux->curr.getPos(), going_right) || !not_this('[', false, aux->curr.getPos(), going_right)) {
                        if(!going_right)
                            delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx()-1);
                        remove_bullet(prec,aux, 1);
                        points = points +  50*killer_prize;
                    }
                    else {
                        aux->curr.go_sx();
                        Mario.show();
                    }
                }
            }
            else{
                remove_bullet(prec, aux, 1);
            }
            Mario.show();
        }
        else {
            if(aux->curr.getPosx()>limit_sx+1) {
                aux->curr.destroy_win();
                Mario.show();
                if(not_this('|', false, aux->curr.getPos(), going_right) && not_this('K', false, aux->curr.getPos(), going_right)) {
                    if(!not_this('A', false, aux->curr.getPos(), going_right)) { 
                        if(!going_right)
                            delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx()-1);
                        remove_bullet(prec,aux, 1);
                        points = points +  100*killer_prize;
                    }
                    else {
                        if(!not_this('}', false, aux->curr.getPos(), going_right) || !not_this(']', false, aux->curr.getPos(), going_right) || !not_this('{', false, aux->curr.getPos(), going_right) || !not_this('[', false, aux->curr.getPos(), going_right)){
                            if(!going_right)
                                delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                            delete_char(aux->curr.getPosy(), aux->curr.getPosx()-1);
                            remove_bullet(prec,aux, 1);
                            points = points +  50*killer_prize;
                        }

                        else {
                            aux->curr.go_sx();
                        }
                    }
                }
                else{
                    remove_bullet(prec, aux, 1);
                }
                Mario.show();
            }
            else {
                aux->curr.destroy_win();
                remove_bullet(prec, aux, 1);
            }
            Mario.show();
        }
        prec = aux;
        if(aux!=NULL)
            aux = aux->next;
    }
}
//metodo che genera i nemici o incrementando la difficoltà in base all'avanzamento dell'Eroe
void BigMap::free_bullet() {
    int y=1;
    //variabile che indica la distanza tra un nemico o e il suo successivo
    int diff = 7;
    if(curr->piece->get_n() > 5) {
        diff = 6;
    }
    if(curr->piece->get_n() > 10) {
        diff = 5;
    }
    if(curr->piece->get_n() > 15) {
        diff = 4;
    }
    if(curr->piece->get_n() > 20) {
        diff = 3;
    }
    if(curr->piece->get_n() > 25) {
        diff = 2;
    }

    if(nodi>2 && count_ghostBullet/diff > 0) {
        //partono colpi se il numero della mappa corrente è un multiplo di 3
        if(curr->piece->get_n()%3 == 0) {
            //si trova un'altezza random da cui far partire il colpo
            while(y%2 != 0) {
                y = rand()%(rect_lines - 4) +2;
            }
            add_ghost_bullet(y);
            //se il numero della mappa corrente è anche divisibile per 5 partono ulteriori colpi
            if(curr->piece->get_n()%5 == 0) {
                while(y%2 != 0) {
                    y = rand()%(rect_lines - 4) +2;
                }
                add_ghost_bullet(y);
            }
        }
        //solo dal nodo 10 della bilista
        if(nodi>10) {
            //partono colpi anche quando il numero della mappa corrente è pari
            if(curr->piece->get_n()%2 == 0) {
                while(y%2 != 0) {
                    y = rand()%(rect_lines - 4) +2;
                }
                add_ghost_bullet(y);
            }
            //partono colpi anche quando il numero della mappa corrente è divisibile per 4
            if(curr->piece->get_n()%4 == 0) {
                while(y%2 != 0) {
                    y = rand()%(rect_lines - 4) +2;
                }
                add_ghost_bullet(y);
            }
        }
        count_ghostBullet = 0;
    }
    update_ghost_shoot();
}
//metodo per aggiornare il movimento dei nemici o
void BigMap::update_ghost_shoot() {
    colpi aux = ghostGun;
    colpi prec = NULL;
    while(aux!=NULL) {
        Mario.show();
        //se o tocca l'Eroe, il nemico perde punti
        if(aux->curr.getPosx() == Mario.getPosx()+1 && aux->curr.getPosy() == Mario.getPosy()) {
            Mario.damage(5);
            warning = true;
            remove_bullet(prec, aux, 2);
        }
        //in ogni altro caso o va avanti indisturbato
        else {
            if(aux->curr.getPosx() > (COLS - rect_cols)/2){
                aux->curr.go_sx();
                Mario.show();
            }
            else {
                remove_bullet(prec, aux, 2);
            }
        }
        Mario.show();
        prec = aux;
        if(aux!=NULL)
            aux = aux->next;
    }
}
//ritorna il numero di che ha la bilista
int BigMap::n_map() {
    return nodi;
}
//verifica se l'Eroe ha preso un bonus e, nel caso, ritorna quale bonus ha preso
char BigMap::is_bonus(){
    Mario.show();
    position tmp = {Mario.getPosy(), Mario.getPosx()-1};
    if(!not_this('&', true, tmp, false)) {
        delete_char(tmp.y, tmp.x+1);
        //se si uccide un nemico si prende il doppio dei punti
        set_killer_prize(2);
        Mario.show();
        return '&';
    }
    if(!not_this('#', true, tmp, false)) {
        delete_char(tmp.y, tmp.x+1);
        Mario.show();
        return '#';
    }
    if(!not_this('*', true, tmp, false)) {
        delete_char(tmp.y, tmp.x+1);
        //si aumenta la vita dell'Eroe
        Mario.bonus_life();
        Mario.show();
        return '*';
    }
    
    if(!not_this('$', true, tmp, false)) {
        delete_char(tmp.y, tmp.x+1);
        //si vincono 1000 punti extra
        points = points +  1000;
        Mario.show();
        return '$';
    }
    return 'X';
}

//metodo per gestire la barra della vita
void BigMap::health_bar() {
    attron(COLOR_PAIR(6));
    mvprintw((LINES - rect_lines)/2 - 4, (COLS-rect_cols)/2 + 10, "LIFE");
    attroff(COLOR_PAIR(6));
    //stampa una barra ogni 5 punti vita
    int n_vita = Mario.getlife() / 5;
    char barra_salute[n_vita];
    WINDOW *health_win;
    health_win = newwin(3, 22, (LINES - rect_lines)/2 - 5, (COLS-rect_cols)/2 +17);
    refresh();
    box(health_win, 0, 0);
    
    if (n_vita <= 20 && n_vita > 15 ) {
        wattron(health_win, COLOR_PAIR(1));
    }
    if (n_vita <= 15 && n_vita > 10) {
        wattron(health_win, COLOR_PAIR(2));
    }
    if (n_vita <= 10 && n_vita > 5) {
        wattron(health_win, COLOR_PAIR(3));
    }
    if (n_vita <= 5) {
        wattron(health_win, COLOR_PAIR(4));
    }
    for (int n=0; n < n_vita; n++)
    {
        barra_salute[n] = '|';
    }
    for (int n=0; n < n_vita; n++)
    {
        mvwaddch(health_win, 1, n+1, barra_salute[n]);
    }
    if (n_vita < 20)
    {
        for (int n=0; n < (20 - n_vita); n++)
        {
            mvwprintw(health_win, 1, 20 - n, " ");
        }
    }
    wrefresh(health_win);
}
//si ristampano a schermo tutti i pezzi di mappa visibili in quel momento. Serve a evitare bug per via di sovrapposizioni o altro
void BigMap::reshow_map(){
    Mario.show();
    if(curr->prev!=NULL && curr->prev->piece->how_much() > -1) {
        curr->prev->piece->show();
        Mario.show();
    }
    curr->piece->show();
    Mario.show();
    if(curr->next!=NULL && curr->next->piece->how_much() > -1) {
        curr->next->piece->show();
        Mario.show();
    }
}
//metodo che esegue una routine che va eseguita ogni volta che si finiscie di eseguire un ciclo
bool BigMap::routine_fineciclo(bool right) {
    srand(time(0));
    //si muovono i nemici
    if(curr->prev!=NULL) {
            curr->prev->piece->move_enemies();
    }
    curr->piece->move_enemies();
    if(curr->next!=NULL) {
            curr->next->piece->move_enemies();
    }
    //si ristampa l'Eroe nella sua posizione
    Mario.show();
    reshow_map();
    Mario.show();
    //si aggiornano gli spari >
    update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1, right);
    Mario.show();
    //si aggiornano gli spari <
    update_back_shoot((COLS+rect_cols)/2-1 - rect_cols, Mario.getPosx(), right);
    Mario.show();
    //se l'Eroe è a contatto con un nemico K, perde 15 punti vita
    if(!not_this('K', true, Mario.getPos(), false) || !not_this('K', false, Mario.getPos(), false)) {
        Mario.damage(15);
        warning = true;
        attron(COLOR_PAIR(4)); Mario.show(); attroff(COLOR_PAIR(4));
    }
    //se l'Eroe è a contatto con un nemico A, perde 20 punti vita
    if(!not_this('A', true, Mario.getPos(), false) || !not_this('A', false, Mario.getPos(), false)) {
        Mario.damage(20);
        warning = true;
        attron(COLOR_PAIR(4)); Mario.show(); attroff(COLOR_PAIR(4));
    }
    if(Mario.getlife() < 0)
        Mario.setlife(0);
    //se l'Eroe ha finito la vita, il gioco finisce quindi il metodo ritorna false
    if(Mario.getlife() == 0) return false;
    //si invoca il metodo che gestisce i nemici o e li fa muovere
    free_bullet();
    //si aggiorna la barra della vita
    health_bar();
    attron(COLOR_PAIR(3));
    mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2, "POINTS    %d", points);
    attroff(COLOR_PAIR(3));
    Mario.show();
    //si colora per un attimo l'Eroe di rosso se ha appena perso punti vita
    if(warning) {
        for(int i=0; i<3000; i++) {
            attron(COLOR_PAIR(4));
            Mario.show();
            attroff(COLOR_PAIR(4));
        }
        warning = false;
    }
    //se il giocatore non è morto, il metodo ritorna true
    return true;
}
//metodo che verifica se un certo carattere è presente a destra o sinistra di una certa posizione
bool BigMap::not_this(char object, bool dx, position pos, bool going_right) {
    Mario.show();
    //si trovano le coordinate rispetto alla finestra di gioco (anzichè rispetto a tutto lo schermo)
    int y_on_pad = pos.y - (LINES-rect_lines)/2;
    int x_on_pad = pos.x - (COLS-rect_cols)/2;
    //si capisce in che pezzo di mappa ci si trova (se prev, curr o next)
    if(curr->prev!=NULL) {
        if(curr->prev->piece->how_much() > x_on_pad)
            return !(curr->prev->piece->there_is_this(object, y_on_pad,x_on_pad + rect_cols - curr->prev->piece->how_much()-1, dx, going_right));
        else{
            if (curr->prev->piece->how_much()>-1) {
                return !(curr->piece->there_is_this(object, y_on_pad,curr->piece->how_much() - rect_cols + x_on_pad+1 ,dx, going_right));
            }
            else {
                if(x_on_pad > curr->piece->how_much())
                    return !(curr->next->piece->there_is_this(object, y_on_pad, x_on_pad - curr->piece->how_much()-1, dx, going_right));
                else
                    return !(curr->piece->there_is_this(object, y_on_pad,rect_cols - curr->piece->how_much() + x_on_pad-1, dx, going_right));
            }
        }
    }
    else {
        if(x_on_pad >= curr->piece->how_much())
            return !(curr->next->piece->there_is_this(object, y_on_pad, x_on_pad - curr->piece->how_much()-1, dx, going_right));
        else
            return !(curr->piece->there_is_this(object, y_on_pad,rect_cols - curr->piece->how_much() + x_on_pad-1, dx, going_right));
    }
    Mario.show();
}
//ritorna i punti ottenuti durante il gioco
int BigMap::get_points() {
    return points;
}
//setta la variabile killer_prize (a 1 oppure a 2) che indica per quanto moltiplicare i punti ottenuti dall'uccisione dei nemici
void BigMap::set_killer_prize(int n) {
    killer_prize = n;
}
