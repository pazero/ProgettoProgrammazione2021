#include "ClasseBigMap.hpp"

BigMap::BigMap(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    this->nodi = 1;

    head->piece = new Map(rect_lines, rect_cols, true);
    head->piece->build();
    head->piece->show();
    head->n = 1;
    head->next = NULL;
    head->prev = NULL;

    position pos = {(LINES+rect_lines)/2 -3, (COLS-rect_cols)/2 +stacco};
    int life = 100;
    this->Mario = Eroe(pos, life);
    this->Mario.show();
}
void BigMap::addMap() {
    nodi++;
    MapList aux = head;
    MapList prec = NULL;
    while(aux->next!=NULL) {
        aux = aux->next;
    }
    prec = aux;
    aux->next = new MapNode;
    aux->next->piece = new Map(rect_lines, rect_cols);
    aux->next->piece->build();

    aux->next->n = nodi;
    aux->next->next = NULL;
    aux->next->prev = prec;
    
    prec = NULL;
    delete(prec);
    mvprintw(LINES/2 -3,0,"Aggiunta nodo numero: %d", nodi);
}
void BigMap::update() {
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
}
void BigMap::slideMap(int ch) {
    this->count++;
    update();
    mvprintw(LINES/2,0,   "Current node: %d  ", head->n);
    if(ch == KEY_LEFT){
        if(!ostacolo(Mario.getPosy() - (LINES-rect_lines)/2, false)) {
            head->piece->lslide();
            if(head->next!=NULL) {
                head->next->piece->lslide();
            }
            if(head->prev!=NULL) {
                if(head->piece->previous())
                    head->prev->piece->lslide();
            }
            while (Mario.getPosy()<(LINES+rect_lines)/2 -3 && !is_platform(Mario.getPosy() - (LINES-rect_lines)/2 + 2))
            {
                Mario.go_down();
            }
            Mario.shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1);
        }
    }
    if(ch == KEY_RIGHT){
        if(!ostacolo(Mario.getPosy() - (LINES-rect_lines)/2, true)) {
            head->piece->rslide();
            if(head->next!=NULL) {
                if(head->piece->nx())
                    head->next->piece->rslide();
            }
            if(head->prev!=NULL)
                head->prev->piece->rslide();

            while (Mario.getPosy()<(LINES+rect_lines)/2 -3 && !is_platform(Mario.getPosy() - (LINES-rect_lines)/2 + 2)){
                Mario.go_down();
            }
        }
    }
    if(ch == KEY_UP) {
        mvprintw(0,0,"%d ",Mario.getPosy() - (LINES-rect_lines)/2);
        mvprintw(1,0,"%d ",Mario.getPosx() - (COLS-rect_cols)/2);
        if(is_platform(Mario.getPosy() - (LINES-rect_lines)/2))
            Mario.go_up();
    }

    if(ch == 'e') {
        if(this->count/2 >0) {
            Mario.add_bullet(Mario.getPos());
            this->count=0;
        }
    }
    Mario.shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1);
    Mario.show();
    Mario.count_bullet();
}
bool BigMap::is_platform(int y_on_pad) {
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>30)
            return head->prev->piece->is_plat(y_on_pad,stacco,head->prev->piece->how_much()+1,true);
        else {
            if (head->prev->piece->how_much()>-1) {
                return head->piece->is_plat(y_on_pad,stacco,head->piece->how_much() - rect_cols + stacco+1, false);
            }
            else {
                return head->piece->is_plat(y_on_pad,stacco,rect_cols - head->piece->how_much() + stacco-1,false);
            }
        }
    }
}

bool BigMap::ostacolo(int y_on_pad, bool dx) {
    if(dx) {
        if(head->prev!=NULL) {
            if(head->prev->piece->how_much()>30)
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
            if(head->prev->piece->how_much()>30)
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
        if(Mario.getPosy()<(LINES+rect_lines)/2 -3 && !is_platform(Mario.getPosy() - (LINES-rect_lines)/2 + 2))
            Mario.go_down();
    }*/