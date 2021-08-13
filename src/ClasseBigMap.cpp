#include "ClasseBigMap.hpp"
BigMap::BigMap(){}
BigMap::BigMap(int rect_lines, int rect_cols) {

    init_pair(1, COLOR_BLUE, COLOR_BLACK);      //Colors are always used in pairs. 
	init_pair(2, COLOR_GREEN, COLOR_BLACK);     //That means you have to use the function 
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);    //init_pair() to define the foreground
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_YELLOW);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_GREEN);

    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    nodi = 1;
    count_Bullet=3;
    count_backBullet=3;
    count_ghostBullet=3;
    stacco = 30;

    head->piece = new Map(rect_lines, rect_cols, nodi, true);
    head->piece->build();
    head->piece->show();
    head->n = 1;
    head->next = NULL;
    head->prev = NULL;
    
    position MarioPos = {(LINES+rect_lines)/2 -3, (COLS-rect_cols)/2 +stacco};
    int life = 100;
    Mario = Eroe(MarioPos, life);
    Mario.show();
    gun = NULL;
    backGun = NULL;
    ghostGun = NULL;


    points = 0;
   set_killer_prize(1);

    //active_bonus = 'X';
    attron(COLOR_PAIR(7));
    mvprintw((LINES - rect_lines)/2 - 4, (COLS-rect_cols)/2 + 10, "LIFE");
    attroff(COLOR_PAIR(7));
    health_bar();
    attron(COLOR_PAIR(3));
    mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2, "POINTS    %d", points);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2 +25, "BONUS    X");
    attroff(COLOR_PAIR(2));
}

void BigMap::addMap() {
    nodi++;
    if(nodi>2) {
        points = points +  50;
    }
    MapList aux = head;
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
    count_Bullet++;
    count_backBullet++;
    count_ghostBullet++;
    if(head->next==NULL) {
        addMap();
    }
    if(head->piece->how_much() < head->next->piece->how_much()) {
        head = head->next;
    }
    if(head->prev!=NULL) {
            if(head->piece->how_much() < head->prev->piece->how_much()) {
                head = head->prev;
            }
        }
    Mario.show();
}
void BigMap::go_left(){
    Mario.show();
    if(not_this('|', false, Mario.getPos(), false) && not_this('K', false, Mario.getPos(), false) && not_this('{', false, Mario.getPos(), false) && not_this('}', false, Mario.getPos(), false) && not_this('[', false, Mario.getPos(), false) && not_this(']', false, Mario.getPos(), false)) {
    //if(!not_this(' ', false, Mario.getPos(), false) || !not_this('*', false, Mario.getPos(), false) || !not_this('#', false, Mario.getPos(), false)){
        head->piece->lslide();
        Mario.show();
        if(head->next!=NULL) {
            head->next->piece->lslide();
            Mario.show();
        }
        if(head->prev!=NULL) {
            if(head->piece->previous())
                head->prev->piece->lslide();
            Mario.show();
        }
        Mario.show();
        while (Mario.getPosy()<(LINES+rect_lines)/2 -3 && free_down(Mario.getPosy() - (LINES-rect_lines)/2))
            Mario.go_down();
        Mario.show();
        update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1, false);
        //ghost_shoot();
    }
    Mario.show();
}

void BigMap::go_right()
{
    Mario.show();
    if(not_this('|', true, Mario.getPos(), false) && not_this('K', true, Mario.getPos(), false) && not_this('{', true, Mario.getPos(), false) && not_this('}', true, Mario.getPos(), false) && not_this('[', true, Mario.getPos(), false) && not_this(']', true, Mario.getPos(), false)) {
    //if(!not_this(' ', true, Mario.getPos(), false) || !not_this('*', true, Mario.getPos(), false) || !not_this('#', true, Mario.getPos(), false)){
        head->piece->rslide();
        Mario.show();
        if (head->next != NULL)
        {
            if (head->piece->nx()){
                head->next->piece->rslide();
                Mario.show();
            }
        }
        if (head->prev != NULL)
            head->prev->piece->rslide();
        Mario.show();
        while (Mario.getPosy() < (LINES + rect_lines) / 2 - 3 && free_down(Mario.getPosy() - (LINES - rect_lines) / 2))
        {
            Mario.go_down();
        }
        Mario.show();
        update_back_shoot((COLS+rect_cols)/2-1 - rect_cols, Mario.getPosx(), right);
        ghost_shoot();
    }
    Mario.show();
}

void BigMap::go_up(){
    int y_on_pad = Mario.getPosy() - (LINES-rect_lines)/2;
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>=stacco) {
            if(head->prev->piece->can_pass_through(y_on_pad,stacco + rect_cols - head->prev->piece->how_much()-1, true)){
                Mario.go_up();
            }
        }
        else {
            if(head->prev->piece->how_much()>-1) {
                if(head->piece->can_pass_through(y_on_pad,head->piece->how_much() - rect_cols + stacco+1, true)){
                    Mario.go_up();
                }
            }
            else {
                if(head->piece->can_pass_through(y_on_pad,rect_cols - head->piece->how_much() + stacco-1, true)){
                    Mario.go_up();
                }
            }
        }
    }
}

void BigMap::go_down() {
    int y_on_pad = Mario.getPosy() - (LINES-rect_lines)/2;
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>=stacco) {
            if(head->prev->piece->can_pass_through(y_on_pad,stacco + rect_cols - head->prev->piece->how_much()-1, false)){
                Mario.go_down();
            }
        }
        else {
            if(head->prev->piece->how_much()>-1) {
                if(head->piece->can_pass_through(y_on_pad,head->piece->how_much() - rect_cols + stacco+1, false)){
                    Mario.go_down();
                }
            }
            else {
                if(head->piece->can_pass_through(y_on_pad,rect_cols - head->piece->how_much() + stacco-1, false)){
                    Mario.go_down();
                }
            }
        }
    }
}
void BigMap::shoot(){
    if(count_Bullet/3 > 0) {
        add_bullet(Mario.getPos());
        count_Bullet=0;
    }
}

void BigMap::back_shoot(){
    if(count_backBullet/3 > 0) {
        add_backbullet(Mario.getPos());
        count_backBullet=0;
    }
}

void BigMap::delete_char(int y, int x){
    Mario.show();
    int y_on_pad = y - (LINES-rect_lines)/2;
    int x_on_pad = x - (COLS-rect_cols)/2;
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much() >= x_on_pad) {
            head->prev->piece->print_space(y_on_pad, x_on_pad + rect_cols - head->prev->piece->how_much() - 1);
            Mario.show();
            head->prev->piece->remove_enemy({y_on_pad, x_on_pad + rect_cols - head->prev->piece->how_much() - 1});
        }
        else{
            if (head->prev->piece->how_much()>-1) {
                head->piece->print_space(y_on_pad, head->piece->how_much() - rect_cols + x_on_pad + 1);
                head->piece->remove_enemy({y_on_pad, head->piece->how_much() - rect_cols + x_on_pad + 1});
                Mario.show();
            }
            else {
                if(x_on_pad >= head->piece->how_much()) {
                    head->next->piece->print_space(y_on_pad, x_on_pad - head->piece->how_much()-1);
                    head->next->piece->remove_enemy({y_on_pad, x_on_pad - head->piece->how_much()-1});
                }
                else{
                    head->piece->print_space(y_on_pad, rect_cols - head->piece->how_much() + x_on_pad - 1);
                    head->piece->remove_enemy({y_on_pad, rect_cols - head->piece->how_much() + x_on_pad - 1});
                }
                Mario.show();
            }
        }
        Mario.show();
    }
    else {
        if(x_on_pad >= head->piece->how_much()) {
            head->next->piece->print_space(y_on_pad, x_on_pad - head->piece->how_much()-1);
            head->next->piece->remove_enemy({y_on_pad, x_on_pad - head->piece->how_much()-1});
        }
        else{
            head->piece->print_space(y_on_pad,rect_cols - head->piece->how_much() + x_on_pad-1);
            head->piece->remove_enemy({y_on_pad,rect_cols - head->piece->how_much() + x_on_pad-1});
        }
        Mario.show();
    }
}

bool BigMap::free_down(int y_on_pad) {
    Mario.show();
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>=stacco)
            return head->prev->piece->can_fall(y_on_pad,stacco + rect_cols - head->prev->piece->how_much()-1);
        else {
            if (head->prev->piece->how_much()>-1) {
                return head->piece->can_fall(y_on_pad,head->piece->how_much() - rect_cols + stacco+1);
            }
            else {
                return head->piece->can_fall(y_on_pad,rect_cols - head->piece->how_much() + stacco-1);
            }
        }
    }
    Mario.show();
    return false;
}

void BigMap::add_bullet(position pos) {
    Mario.show();
    colpi tmp = new colpo;
    tmp->curr = Bullet(pos);
    tmp->curr.set_name('>');
    tmp->next = gun;
    gun = tmp;
}

void BigMap::add_backbullet(position pos) {
    Mario.show();
    colpi tmp = new colpo;
    tmp->curr = Bullet(pos);
    tmp->curr.set_name('<');
    tmp->next = backGun;
    backGun = tmp;
}

void BigMap::add_ghost_bullet(int y) {
    Mario.show();
    colpi tmp = new colpo;
    tmp->curr = Bullet({y + (LINES - rect_lines)/2,rect_cols + (COLS - rect_cols)/2});
    tmp->curr.set_name('o');
    tmp->next = ghostGun;
    ghostGun = tmp;
}

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
void BigMap::update_back_shoot(int limit_sx, int limit_dx, bool going_right){
    colpi aux = backGun;
    colpi prec = NULL;
    while(aux!=NULL) {
        Mario.show();
        if(aux->curr.getPosx()==limit_dx) {
            if(not_this('|', false, aux->curr.getPos(), going_right) && not_this('K', false, aux->curr.getPos(), going_right)) {
                //if(not_this(' ', false, aux->curr.getPos(), going_right) && not_this('#', false, aux->curr.getPos(), going_right) && not_this('*', false, aux->curr.getPos(), going_right)) {
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
                   //if(not_this(' ', false, aux->curr.getPos(), going_right) && not_this('*', false, aux->curr.getPos(), going_right) && not_this('#', false, aux->curr.getPos(), going_right)) {
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
void BigMap::update_shoot(int limit_sx, int limit_dx, bool going_right){
    colpi aux = gun;
    colpi prec = NULL;
    while(aux!=NULL) {
        Mario.show();
        if(aux->curr.getPosx()==limit_sx) {
            if(not_this('|', true, aux->curr.getPos(), going_right) && not_this('K', true, aux->curr.getPos(), going_right)) {
                if(!not_this('A', true, aux->curr.getPos(), going_right)) {
                //if(not_this(' ', true, aux->curr.getPos(), going_right) && not_this('#', true, aux->curr.getPos(), going_right) && not_this('*', true, aux->curr.getPos(), going_right)) {
                    if(going_right)
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                    delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                    remove_bullet(prec,aux, 0);
                    Mario.show();
                    points = points +  100*killer_prize;
                }
                else {
                    if(!not_this('{', true, aux->curr.getPos(), going_right) || !not_this('[', true, aux->curr.getPos(), going_right) || !not_this('}', true, aux->curr.getPos(), going_right) || !not_this(']', true, aux->curr.getPos(), going_right)) {
                        if(going_right)
                            delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                        remove_bullet(prec,aux, 0);
                        Mario.show();
                        points = points +  50*killer_prize;
                    }
                    else {
                        aux->curr.go_dx();
                        Mario.show();
                    }
                }
            }
            else{
                remove_bullet(prec, aux, 0);
            }
            Mario.show();
        }
        else {
            if(aux->curr.getPosx()<limit_dx) {
                aux->curr.destroy_win();
                Mario.show();
                if(not_this('|', true, aux->curr.getPos(), going_right) && not_this('K', true, aux->curr.getPos(), going_right)) {
                    if(!not_this('A', true, aux->curr.getPos(), going_right)){
                    //if(not_this(' ', true, aux->curr.getPos(), going_right) && not_this('*', true, aux->curr.getPos(), going_right) && not_this('#', true, aux->curr.getPos(), going_right)){
                        if(going_right)
                            delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                        remove_bullet(prec,aux, 0);
                        Mario.show();
                        points = points +  100*killer_prize;
                    }
                    else {
                        if(!not_this('{', true, aux->curr.getPos(), going_right) || !not_this('[', true, aux->curr.getPos(), going_right) || !not_this('}', true, aux->curr.getPos(), going_right) || !not_this(']', true, aux->curr.getPos(), going_right)) {
                            if(going_right)
                                delete_char(aux->curr.getPosy(), aux->curr.getPosx());
                            delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                            remove_bullet(prec,aux, 0);
                            Mario.show();
                            points = points +  50*killer_prize;
                        }
                        else {
                            aux->curr.go_dx();
                        }
                    }
                }
                else{
                    remove_bullet(prec, aux, 0);
                }
                Mario.show();
            }
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

void BigMap::free_bullet() {
    int y=1;
    int diff = 7;
    if(head->piece->get_n() > 5) {
        diff = 6;
    }
    if(head->piece->get_n() > 10) {
        diff = 5;
    }
    if(head->piece->get_n() > 15) {
        diff = 4;
    }
    if(head->piece->get_n() > 20) {
        diff = 3;
    }
    if(head->piece->get_n() > 25) {
        diff = 2;
    }

    if(nodi>2 && count_ghostBullet/diff > 0) {
        if(head->piece->get_n()%3 == 0) {
            while(y%2 != 0) {
                y = rand()%(rect_lines - 4) +2;
            }
            add_ghost_bullet(y);

            if(head->piece->get_n()%5 == 0) {
                while(y%2 != 0) {
                    y = rand()%(rect_lines - 4) +2;
                }
                add_ghost_bullet(y);
            }
        }
        if(nodi>10) {
            if(head->piece->get_n()%2 == 0) {
                while(y%2 != 0) {
                    y = rand()%(rect_lines - 4) +2;
                }
                add_ghost_bullet(y);
            }
            if(head->piece->get_n()%4 == 0) {
                while(y%2 != 0) {
                    y = rand()%(rect_lines - 4) +2;
                }
                add_ghost_bullet(y);
            }
        }
        count_ghostBullet = 0;
    }
    ghost_shoot();
}

void BigMap::ghost_shoot() {
    colpi aux = ghostGun;
    colpi prec = NULL;
    while(aux!=NULL) {
        Mario.show();
        if(aux->curr.getPosx() == Mario.getPosx()+1 && aux->curr.getPosy() == Mario.getPosy()) {
            Mario.damage(5);
            remove_bullet(prec, aux, 2);
        }
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
int BigMap::n_map() {
    return nodi;
}

char BigMap::is_bonus(){
    Mario.show();
    position tmp = {Mario.getPosy(), Mario.getPosx()-1};
    if(!not_this('&', true, tmp, false)) {
        //active_bonus = '%';
        delete_char(tmp.y, tmp.x+1);
        set_killer_prize(2);
        Mario.show();
        return '&';
    }
    if(!not_this('#', true, tmp, false)) {
        //active_bonus = '#';
        delete_char(tmp.y, tmp.x+1);
        Mario.show();
        return '#';
    }
    if(!not_this('*', true, tmp, false)) {
        delete_char(tmp.y, tmp.x+1);
        Mario.bonus_life();
        Mario.show();
        return '*';
    }
    
    if(!not_this('$', true, tmp, false)) {
        delete_char(tmp.y, tmp.x+1);
        points = points +  1000;
        Mario.show();
        return '$';
    }
    return 'X';
}

//char BigMap::get_active_bonus() {
//    return active_bonus;
//}

void BigMap::set_print_bonus(char actual_bonus) {

}

void BigMap::health_bar() {
    int n_vita = Mario.getlife() / 5; // stampa una barra ogni 5 punti vita
    char barra_salute[n_vita]; 
    WINDOW *health_win;
    health_win = newwin(3, 22, (LINES - rect_lines)/2 - 5, (COLS-rect_cols)/2 +17); // altezza, larghezza, starty, startx
    refresh();
    box(health_win, 0, 0);

    //init_pair(1, COLOR_BLUE, COLOR_BLACK);      //Colors are always used in pairs. 
	//init_pair(2, COLOR_GREEN, COLOR_BLACK);     //That means you have to use the function 
    //init_pair(3, COLOR_YELLOW, COLOR_BLACK);    //init_pair() to define the foreground
    //init_pair(4, COLOR_RED, COLOR_BLACK);       //and background for the pair number you give.
    
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

void BigMap::reshow_map(){
    Mario.show();
    if(head->prev!=NULL && head->prev->piece->how_much() > -1) {
        head->prev->piece->show();
        Mario.show();
    }
    head->piece->show();
    Mario.show();
    if(head->next!=NULL && head->next->piece->how_much() > -1) {
        head->next->piece->show();
        Mario.show();
    }
}
bool BigMap::routine_fineciclo(bool right) {
    mvwprintw(stdscr,0,0,"%d", killer_prize);
    srand(time(0));
    if(head->prev!=NULL) {
            head->prev->piece->move_enemies();
    }
    head->piece->move_enemies();
    if(head->next!=NULL) {
            head->next->piece->move_enemies();
    }
    Mario.show();
    reshow_map();
    Mario.show();
    //player_on_enemy();
    Mario.show();
    update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1, right);
    Mario.show();
    update_back_shoot((COLS+rect_cols)/2-1 - rect_cols, Mario.getPosx(), right);
    Mario.show();

    if(!not_this('K', true, Mario.getPos(), false) || !not_this('K', false, Mario.getPos(), false)) {
        Mario.damage(15);
    }
    if(!not_this('A', true, Mario.getPos(), false) || !not_this('A', false, Mario.getPos(), false)) {
        Mario.damage(20);
    }
    if(Mario.getlife() < 0)
        Mario.setlife(0);
    if(Mario.getlife() == 0) return false;

    free_bullet();
    health_bar();
    attron(COLOR_PAIR(3));
    mvwprintw(stdscr, (LINES - rect_lines)/2 - 4, COLS/2, "POINTS    %d", points);
    attroff(COLOR_PAIR(3));
    Mario.show();
    return true;
}

bool BigMap::not_this(char object, bool dx, position pos, bool going_right) {
    Mario.show();
    int y_on_pad = pos.y - (LINES-rect_lines)/2;
    int x_on_pad = pos.x - (COLS-rect_cols)/2;

    if(head->prev!=NULL) {
        if(head->prev->piece->how_much() > x_on_pad)
            return !(head->prev->piece->there_is_this(object, y_on_pad,x_on_pad + rect_cols - head->prev->piece->how_much()-1, dx, going_right));
        else{
            if (head->prev->piece->how_much()>-1) {
                return !(head->piece->there_is_this(object, y_on_pad,head->piece->how_much() - rect_cols + x_on_pad+1 ,dx, going_right));
            }
            else {
                if(x_on_pad > head->piece->how_much())
                    return !(head->next->piece->there_is_this(object, y_on_pad, x_on_pad - head->piece->how_much()-1, dx, going_right));
                else
                    return !(head->piece->there_is_this(object, y_on_pad,rect_cols - head->piece->how_much() + x_on_pad-1, dx, going_right));
            }
        }
    }
    else {
        if(x_on_pad >= head->piece->how_much())
            return !(head->next->piece->there_is_this(object, y_on_pad, x_on_pad - head->piece->how_much()-1, dx, going_right));
        else
            return !(head->piece->there_is_this(object, y_on_pad,rect_cols - head->piece->how_much() + x_on_pad-1, dx, going_right));
    }
    Mario.show();
}

int BigMap::get_points() {
    return points;
}

void BigMap::set_killer_prize(int n) {
    killer_prize = n;
}