#include "ClasseMap.hpp"
//ogni pezzo di mappa è un pad, ovvero una finestra con particolari proprietà
//che permettono di stampare a schermo solo una parte di essa
Map::Map(int rect_lines, int rect_cols, int n, bool first) {
    //il primo pezzo di mappa è diverso da tutti gli altri
    this->first = first;
    //si stabilisce la posizione dei 4 vertici della finestra di gioco
    iniziox_rect = (COLS - rect_cols)/2;
    finex_rect = (COLS + rect_cols)/2 - 1;
    inizioy_rect = (LINES - rect_lines)/2;
    finey_rect = (LINES + rect_lines)/2;
    //punto di coordinata y rispetto al quale si comincia a guardare il contenuto del pad
    //(sempre =0 perchè in altezza si guarda sempre tutto, mentre è la larghezza che può variare)
    pad_y=0;
    //numero del pezzo di mappa
    this->n = n;
    if(first) {
        this->sx = iniziox_rect;
    }
    else {
        this->sx = finex_rect+1;
    }
    this->ex = finex_rect;
    this->sy = inizioy_rect;
    this->ey = finey_rect;
    //dimensione della finestra di gioco
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    //si comincia a guardare il pad dalla prima colonna a sinistra
    this->pad_x = 0;

    mappa = newpad(rect_lines, rect_cols);
    refresh();
    //variabile per gestire i tipi di bonus
    powerup = Bonus(rect_lines, rect_cols);
    //inizialmente non ci sono nemici
    nemici = NULL;
    //contatore usato per i nemici aumentato di 1 ad ogni esecuzione, arrivato a 4 si riazzera
    count_move = 0;
    //contatore funzionale al nemico A
    count_A = 0;
}
//metodo che gestisce il movimento dei nemici
void Map::move_enemies(){
    enemies_A();
    lista_nemici aux = nemici;
    int c;
    srand(time(0));
    //per non far muovere i nemici troppo velocemente, i nemici si muovono ogni 4 cicli di esecuzione
    if(count_move%4 == 0) {
        while(aux!=NULL) {
            //si scorre tutta la lista facendo muovere solo i nemici K
            if(aux->bad.get_name() == 'K') {
                c = rand()%2;
                //va a sinistra
                if(c==0) {
                    //si controlla che il nemico non esca dai limiti del pad
                    if(aux->bad.getPosx() > 0) {
                        //si può muovere solo se a fianco non ha niente
                        if(there_is_this(' ',aux->bad.getPosy(), aux->bad.getPosx() , false, false)) {
                            //si può muovere solo se è sopra una piattaforma o per terra
                            if(there_is_this('+',aux->bad.getPosy()+1, aux->bad.getPosx(), false, true) || there_is_this('=',aux->bad.getPosy()+1, aux->bad.getPosx() , false, true)) {
                                print_space(aux->bad.getPosy(), aux->bad.getPosx());
                                aux->bad.update_pos({aux->bad.getPosy(),aux->bad.getPosx()-1});
                                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx(), "%c", aux->bad.get_name());
                            }
                        }
                    }
                }
                //va a destra (come sopra ma dalla parte opposta)
                else {
                    if(aux->bad.getPosx() < rect_cols){
                        if(there_is_this(' ',aux->bad.getPosy(), aux->bad.getPosx() , true, false)) {
                            if(there_is_this('+',aux->bad.getPosy()+1, aux->bad.getPosx() , true, false) || there_is_this('=',aux->bad.getPosy()+1, aux->bad.getPosx() , true, false)) {
                                print_space(aux->bad.getPosy(), aux->bad.getPosx());
                                aux->bad.update_pos({aux->bad.getPosy(),aux->bad.getPosx()+1});
                                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx(), "%c", aux->bad.get_name());
                            }
                        }
                    }
                }   
            }
            aux = aux->next;
        }
        count_move=0;
    }
    count_move++;
}
//i nemici A non si muovono ma a tempi alterni hanno o meno la corazza {[A]}
void Map::enemies_A(){
    lista_nemici aux = nemici;
    while(aux!=NULL) {
        if(aux->bad.get_name() == 'A') {
            if(count_A - aux->bad.get_delay() == 0) {
                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx()-2, "{");
                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx()-1, "[");
                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx()+1, "]");
                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx()+2, "}");
            }
            if(count_A - aux->bad.get_delay() == 100) { //dopo 100 cicli non hanno la corazza
                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx()-2, " ");
                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx()-1, " ");
                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx()+1, " ");
                mvwprintw(mappa,aux->bad.getPosy(), aux->bad.getPosx()+2, " ");
            }
        }
        aux = aux->next;
    }
    if(count_A == 200) {
        count_A = -1; //in modo che poi per 100 cicli abbiano la corazza
    }
    count_A++;
}
//metodo che disegna l'intero pezzo di mappa
void Map::build(){
    for(int i=0; i<rect_cols; i++) { //pavimento e soffitto
        mvwaddch(mappa,0,i,'=');
        mvwaddch(mappa,1,i,'=');
        mvwaddch(mappa,rect_lines-2,i,'=');
        mvwaddch(mappa,rect_lines-1,i,'=');
    }
    if(first) { //se è la prima mappa, a sinistra c'è dello spazio vuoto con la scritta START in verticale
        mvwaddstr(mappa,0,0,"          ");
        mvwaddstr(mappa,1,0,"          ");
        mvwaddstr(mappa,rect_lines-2,0,"          ");
        mvwaddstr(mappa,rect_lines-1,0,"          ");
        for(int i=0; i<rect_lines; i++) {
            if(i%2==0)
                mvwaddstr(mappa,i,10,"|");
            else {
                mvwaddstr(mappa,i,10," ");
            }
        }
        char start[] = "S T A R T";
        int length = strlen(start);
        for(int i=0; i<length; i++) {
            mvwaddch(mappa, (rect_lines-length)/2+i, 6, start[i]);
        }
    }
    if(!first) { //a partire dal secondo pezzo di mappa è possibile trovare bonus e nemici nel percorso
        rand_plat();
        spawn_bonus();
        if(n<3) spawn_enemy(1);
        else spawn_enemy(n);
    } 
}
//metodo che spawna randomicamente m nemici nella mappa
void Map::spawn_enemy(int m){
    position tmp_pos;
    for(int i=0;i<m;i++){
        lista_nemici cattivo = new nemico;
        if(i<(m/3)*2) {
            cattivo->bad = Enemy('K');
        }
        else {
            cattivo->bad = Enemy('A');
        }
        //gli si setta una posizione randomica
        tmp_pos.y = rand()%(rect_lines-3);
        tmp_pos.x = rand()%(rect_cols-4)+2;
        //poi lo si fa cadere finchè non incontra un punto in cui può stare (piattaforma o terreno)
        while(can_fall(tmp_pos.y, tmp_pos.x) && tmp_pos.y < rect_lines-3) {
                tmp_pos.y ++;
            }
        mvwprintw(mappa,tmp_pos.y, tmp_pos.x, "%c", cattivo->bad.get_name());
        cattivo->bad.update_pos(tmp_pos);
        cattivo->next = nemici;
        nemici = cattivo;
    }
}
//metodo che spawna al più 1 bonus nella mappa
void Map::spawn_bonus(){
    char name;
    position tmp_pos;
    name = powerup.rand_name_bonus();
    tmp_pos = powerup.rand_pos_bonus();
    while(can_fall(tmp_pos.y, tmp_pos.x) && tmp_pos.y < rect_lines-3) {
        tmp_pos.y ++;
    }
    mvwprintw(mappa,tmp_pos.y, tmp_pos.x, "%c",name);
}
//metodo che stampa le piattaforme in diverse disposizioni
void Map::add_plat(int type, int y, int x) {
    if(type==0) {
        mvwprintw(mappa,y-10,x+1,"+++++++++");
        mvwprintw(mappa,y-8,x,  "++++++"    );
        mvwprintw(mappa,y-6,x,  "++++++++++");
        mvwprintw(mappa,y-4,x+7,       "+++");
        mvwprintw(mappa,y-2,x,  "++++++++++");
        mvwprintw(mappa,y,x+2,    "++++++++");
        mvwprintw(mappa,y+1,x+5,      "|"   );
    }
    if(type==1) {
        mvwprintw(mappa,y-13,x+3,   "|");
        mvwprintw(mappa,y-12,x,  "++++++++++");
        mvwprintw(mappa,y-10,x+5,     "+++++");
        mvwprintw(mappa,y-8,x,   "++++++"    );
        mvwprintw(mappa,y-6,x+2,   "++++++++");
        mvwprintw(mappa,y-4,x,   "++++++++++");
        mvwprintw(mappa,y-3,x+8,         "|" );
        mvwprintw(mappa,y-2,x+2,   "++++++++");
        mvwprintw(mappa,y,x,     "++++++++++");
        mvwprintw(mappa,y+1,x+7,       "|"   );
    }
    if(type==2) {
        mvwprintw(mappa,y-10,x, "++++++++++");
        mvwprintw(mappa,y-8,x,  "+++++++"   );
        mvwprintw(mappa,y-6,x+2,  "++++++++");
        mvwprintw(mappa,y-4,x+1, "+++++++++");
        mvwprintw(mappa,y-2,x,  "++++++++++");
        mvwprintw(mappa,y-1,x,  "|"         );
        mvwprintw(mappa,y,x,    "++++++++"  );  

    }
    if(type==3) {
        mvwprintw(mappa,y-12,x+1, "+++++++++");
        mvwprintw(mappa,y-8,x,  "+++++++++"  );
        mvwprintw(mappa,y-6,x+3,    "+++++++");
        mvwprintw(mappa,y-4,x,   "++++++++++");
        mvwprintw(mappa,y-2,x+1,  "+++++++++");
        mvwprintw(mappa,y,x+3,      "+++++++");
        mvwprintw(mappa,y+1,x+7,       "|"   );
    }
    if(type==4) {
        mvwprintw(mappa,y-12,x, "++++++++++");
        mvwprintw(mappa,y-10,x, "+++++++"   );
        mvwprintw(mappa,y-9,x,  "|"         );
        mvwprintw(mappa,y-8,x,  "++++++++++");
        mvwprintw(mappa,y-4,x,  "++++++++++");
        mvwprintw(mappa,y-2,x,  "++++++++"  );
    }
    if(type==5){
        mvwprintw(mappa,y-12,x, "++++++++++");
        mvwprintw(mappa,y-10,x, "++++++++++");
        mvwprintw(mappa,y-8,x+3,    "+++++++");
        mvwprintw(mappa,y-6,x,  "++++++++++");
        mvwprintw(mappa,y-5,x+3,   "|"      );
        mvwprintw(mappa,y-4,x,  "+++++"     );
        mvwprintw(mappa,y-2,x,  "++++++++++");
        mvwprintw(mappa,y,x+4,      "++++++");
    }
    if(type==6){
        mvwprintw(mappa,y-12,x,  "++++++++++");
        mvwprintw(mappa,y-11,x+7,      "|"   );
        mvwprintw(mappa,y-10,x,  "++++++++++");
        mvwprintw(mappa,y-6,x,   "+++++++"   );
        mvwprintw(mappa,y-4,x+5,      "+++++");
        mvwprintw(mappa,y-2,x,   "++++++++++");
        mvwprintw(mappa,y-1,x+5,     "|"     );
        mvwprintw(mappa,y,x,      "+++++++++");
        mvwprintw(mappa,y+1,x+1,       "|"   );
    }
}
//metodo che semirandomicamente aggiunge le piattaforme alla mappa
void Map::rand_plat() {
    int c;
    int stop = 0;
    srand(time(0));
    int length = 10;
    while(stop<rect_cols) {
        c = rand()%7;
        add_plat(c,rect_lines -4,stop);
        stop+=length;
    }
}
//metodo che fa scorrere la mappa a sinistra, dando così la sensazione che l'Eroe vada a destra
void Map::rslide(){
    if(first) {
        if(pad_x<(rect_cols - rect_cols)) {
            pad_x += 1;
        }
        else {
            if(pad_x<rect_cols-1) {
                pad_x += 1;
                ex -= 1;
            }
            else {
                if(ex == sx) {
                    ex -= 1;
                }
            }
        }
    }
    else {
        if(sx>iniziox_rect) {
            sx--;
        }
        else {
            if(ex>iniziox_rect-1) {
                pad_x++;
                ex--;
            }
        }
    }
    prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
}
//metodo che fa scorrere la mappa a detra, dando così la sensazione che l'Eroe vada a sinistra
void Map::lslide(){
    if(first) {
        if(ex<sx) {
            ex += 1;
        }
        else {
            if(ex<finex_rect) {
                pad_x -= 1;
                ex +=1;
            }
            else {
                if(pad_x>0) {
                    pad_x -= 1;
                }
            }
        }
    }
    else {
        if(pad_x>0) {
            ex++;
            pad_x--;
        }
        else {
            if(sx<finex_rect+1) {
                sx++;
            }
        }
    }
    prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
}
//metodo che restituisce il numero della mappa
int Map::get_n() {
    return n;
}
//metodo che ritorna se il pezzo di mappa successivo a questo si vede o no nella finestra di gioco
bool Map::nx() {
    if(ex<finex_rect) 
        return true;
    else return false;
}
//metodo che ritorna se il pezzo di mappa precedente a questo si vede o no nella finestra di gioco
bool Map::previous() {
    if(sx>iniziox_rect)
        return true;
    else return false;
}
//metodo che stampa a schermo tutta la mappa
void Map::show(){
    prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
}
//metodo che ritorna quante colonne di questo pezzo di mappa si vedono a schermo
int Map::how_much() {
    return ex - sx;
}
//metodo che ritorna true se si può salire o scendere da una piattaforma
bool Map::can_pass_through(int y, int x, bool up) {
    if(up) {
        return (mvwinch(mappa, y-2, x) != '|' && mvwinch(mappa, y-2, x) != 'K' && mvwinch(mappa, y-2, x) != 'A' && mvwinch(mappa, y-1, x) == '+');
    }
    else {
        if(mvwinch(mappa, y+2, x) != '|' && (mvwinch(mappa, y+3, x) == '+' || mvwinch(mappa, y+3, x) == '=')) {
            if(mvwinch(mappa, y+2, x) != 'A' && mvwinch(mappa, y+2, x) != 'K')
                return true; 
        }
    }    
    return false;
}
//metodo che ritorna true se l'oggetto può cadere di una posizione(quindi scendere) oppure no
bool Map::can_fall(int y, int x) {
    if(mvwinch(mappa, y+1,x) == '+')
        return false;
    return true;
}
//metodo che ritorna true se in una data posizione c'è un certo oggetto
bool Map::there_is_this(char object,int pady, int padx, bool dx, bool going_right) {
    if(going_right) {
        if(dx)
            return (mvwinch(mappa, pady, padx) == object) || (mvwinch(mappa, pady, padx+1) == object);
        else
            return (mvwinch(mappa, pady, padx-1) == object);
    }
    else {
        if(dx)
            return (mvwinch(mappa, pady, padx +1) == object);
        else
            return (mvwinch(mappa, pady, padx) == object) || (mvwinch(mappa, pady, padx -1) == object);
    }
}
//metodo che stampa uno spazio in una data posizione
void Map::print_space(int y_on_pad, int x_on_pad){
    mvwaddch(mappa, y_on_pad, x_on_pad, ' ');
}
//metodo che stampa l'Eroe nella sua attuale posizione
void Map::print_player(char player_name, int y, int stacco){
    mvwprintw(mappa, y, stacco, "%c", player_name);
}
//metodo che rimuove un nemico dalla lista dei nemici
void Map::remove_enemy(position pos) {
    lista_nemici tmp;
    lista_nemici aux = nemici;
    lista_nemici prec = NULL;
    while(aux!=NULL) {
        if(aux->bad.getPosx()==pos.x) {
            if(prec == NULL){
                tmp = aux;
                aux = aux->next;
                delete(tmp);
                tmp = NULL;
                nemici = aux;
            }
            else{
                tmp = aux;
                aux = aux->next;
                prec->next = aux;
                delete (tmp);
                tmp = NULL;
            }
        }
        prec=aux;
        if(aux!=NULL)
            aux=aux->next;
    }
}
