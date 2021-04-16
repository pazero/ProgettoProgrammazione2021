#include "WorldGen.hpp"

WorldGen::WorldGen() {}
WorldGen::WorldGen(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    this->nodi = 1;
    // mettiamo nel nodo in testa alla lista il pezzo di mappa con lo spawn iniziale
    head->piece = new Map(rect_lines, rect_cols, true);
    // costruiamo il pezzo di mappa
    head->piece->build();
    // stampiamo a schermo il pezzo costruito
    head->piece->show();

    head->n = 1;
    head->next = NULL;
    head->prev = NULL;

    position pos = {(LINES+rect_lines)/2 -3, (COLS-rect_cols)/2 + stacco};
    int life = 100;
    this->Mario = Eroe(pos, life);
    this->Mario.show();
}
// aggiunge un nodo alla lista
void WorldGen::addMap() {
    nodi++;
    List aux = head;
    List prec = NULL;
    while(aux->next!=NULL) {
        aux = aux->next;
    }
    prec = aux;
    aux->next = new Node;
    aux->next->piece = new Map(rect_lines, rect_cols);
    aux->next->piece->build();

    aux->next->n = nodi;
    aux->next->next = NULL;
    aux->next->prev = prec;
    
    prec = NULL;
    delete(prec);
    mvprintw(LINES/2 +1,0,"Aggiunta nodo numero: %d", nodi);
}
// aggiorna lo schermo all'inizio di ogni ciclo
void WorldGen::update() {
    count++;
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
    mvprintw(LINES/2,0, "Current node: %d  ", head->n);
}
// sposta la mappa a sx
void WorldGen::go_left(){
    if(!ostacolo(Mario.getPosy() - (LINES-rect_lines)/2, false)) {
        head->piece->lslide();
        if(head->next!=NULL) {
            head->next->piece->lslide();
        }
        if(head->prev!=NULL) {
            if(head->piece->previous())
                head->prev->piece->lslide();
        }
        while (Mario.getPosy()<(LINES+rect_lines)/2 -3 && !is_freeplatform(Mario.getPosy() - (LINES-rect_lines)/2 + 2))
            Mario.go_down();  
        Mario.update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1);
    }
}
// sposta la mappa a dx
void WorldGen::go_right(){
    if(!ostacolo(Mario.getPosy() - (LINES-rect_lines)/2, true)) {
        head->piece->rslide();
        if(head->next!=NULL) {
            if(head->piece->next())
                head->next->piece->rslide();
        }
        if(head->prev!=NULL)
            head->prev->piece->rslide();

        while (Mario.getPosy()<(LINES+rect_lines)/2 -3 && !is_freeplatform(Mario.getPosy() - (LINES-rect_lines)/2 + 2)){
            Mario.go_down();
        }
    }
}
// sposta il giocatore sopra una piattaforma
void WorldGen::go_up(){
    if(is_freeplatform(Mario.getPosy() - (LINES-rect_lines)/2))
        Mario.go_up();
    //aggiungere controllo che sopra sia libero
}
// crea una lista di proiettili e li stampa a schermo
void WorldGen::shoot(){
    if(this->count/2 >0) {
        Mario.add_bullet(Mario.getPos());
        this->count = 0;
    }
}
// aggiorna le entità a fine ciclo
void WorldGen::routine_fineciclo() {
    Mario.update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1);
    Mario.show();
}

bool WorldGen::is_freeplatform(int y_on_pad) {
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>stacco)
            return head->prev->piece->is_plat(y_on_pad,stacco,head->prev->piece->how_much()+1,true) && head->prev->piece->is_freeup(y_on_pad,stacco,head->prev->piece->how_much()+1,true);
        else {
            if (head->prev->piece->how_much()>-1) {
                return head->piece->is_plat(y_on_pad,stacco,head->piece->how_much() - rect_cols + stacco+1, false) && head->piece->is_freeup(y_on_pad,stacco,head->piece->how_much() - rect_cols + stacco+1, false);
            }
            else {
                return head->piece->is_plat(y_on_pad,stacco,rect_cols - head->piece->how_much() + stacco-1,false) && head->piece->is_freeup(y_on_pad,stacco,rect_cols - head->piece->how_much() + stacco-1,false);
            }
        }
    }
}

bool WorldGen::ostacolo(int y_on_pad, bool dx) {
    if(dx) {
        if(head->prev!=NULL) {
            if(head->prev->piece->how_much()>stacco)
                return head->prev->piece->is_wall(y_on_pad,stacco,head->prev->piece->how_much()+1,true, true);
            else {
                if (head->prev->piece->how_much()>-1) {
                    return head->piece->is_wall(y_on_pad,stacco,head->piece->how_much() - rect_cols + stacco+1, false, true);
                }
                else {
                    return head->piece->is_wall(y_on_pad,stacco,rect_cols - head->piece->how_much() + stacco-1,false, true);
                }
            }
        }
    }
    else {
        if(head->prev!=NULL) {
            if(head->prev->piece->how_much()>stacco)
                return head->prev->piece->is_wall(y_on_pad,stacco,head->prev->piece->how_much()+1,true, false);
            else {
                if (head->prev->piece->how_much()>-1) {
                    return head->piece->is_wall(y_on_pad,stacco,head->piece->how_much() - rect_cols + stacco+1, false, false);
                }
                else {
                    return head->piece->is_wall(y_on_pad,stacco,rect_cols - head->piece->how_much() + stacco-1,false, false);
                }
            }
        }
    }
}
    /*
    if(ch == KEY_DOWN) {
        if(Mario.getPosy()<(LINES+rect_lines)/2 -3 && !is_freeplatform(Mario.getPosy() - (LINES-rect_lines)/2 + 2))
            Mario.go_down();
    }*/