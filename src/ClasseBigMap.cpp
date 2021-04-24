#include "ClasseBigMap.hpp"
BigMap::BigMap(){}
BigMap::BigMap(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    nodi = 1;
    count=3;

    head->piece = new Map(rect_lines, rect_cols, true);
    head->piece->build();
    head->piece->show();
    head->n = 1;
    head->next = NULL;
    head->prev = NULL;

    position pos = {(LINES+rect_lines)/2 -3, (COLS-rect_cols)/2 +stacco};
    int life = 100;
    Mario = Eroe(pos, life);
    Mario.show();
    gun = NULL;
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
    //mvprintw(LINES/2 +1,0,"Aggiunta nodo numero: %d", nodi);
}
void BigMap::update() {
    count++;
    Mario.show();
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
    //mvprintw(LINES/2,0, "Current node: %d  ", head->n);
}
void BigMap::go_left(){
    if(not_this('|', false, Mario.getPos(), false)) {
        head->piece->lslide();
        if(head->next!=NULL) {
            head->next->piece->lslide();
        }
        if(head->prev!=NULL) {
            if(head->piece->previous())
                head->prev->piece->lslide();
        }
        while (Mario.getPosy()<(LINES+rect_lines)/2 -3 && free_down(Mario.getPosy() - (LINES-rect_lines)/2))
            Mario.go_down();
            
        update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1, false);
    }
}

void BigMap::go_right(){
    if(not_this('|', true, Mario.getPos(), true)) {
        head->piece->rslide();
        if(head->next!=NULL) {
            if(head->piece->nx())
                head->next->piece->rslide();
        }
        if(head->prev!=NULL)
            head->prev->piece->rslide();

        while (Mario.getPosy()<(LINES+rect_lines)/2 -3 && free_down(Mario.getPosy() - (LINES-rect_lines)/2)){
            Mario.go_down();
        }
    }
}

void BigMap::go_up(){
    int y_on_pad = Mario.getPosy() - (LINES-rect_lines)/2;
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>stacco) {
            if(head->prev->piece->can_go_up(y_on_pad,stacco + rect_cols - head->prev->piece->how_much()-1)){
                Mario.go_up();
            }
        }
        else {
            if(head->prev->piece->how_much()>-1) {
                if(head->piece->can_go_up(y_on_pad,head->piece->how_much() - rect_cols + stacco+1)){
                    Mario.go_up();
                }
            }
            else {
                if(head->piece->can_go_up(y_on_pad,rect_cols - head->piece->how_much() + stacco-1)){
                    Mario.go_up();
                }
            }
        }
    }
}

void BigMap::shoot(){
    if(count/3 > 0) {
        add_bullet(Mario.getPos());
        count=0;
    }
}

bool BigMap::free_down(int y_on_pad) {
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>stacco)
            return head->prev->piece->can_go_down(y_on_pad,stacco + rect_cols - head->prev->piece->how_much()-1);
        else {
            if (head->prev->piece->how_much()>-1) {
                return head->piece->can_go_down(y_on_pad,head->piece->how_much() - rect_cols + stacco+1);
            }
            else {
                return head->piece->can_go_down(y_on_pad,rect_cols - head->piece->how_much() + stacco-1);
            }
        }
    }
}

void BigMap::add_bullet(position pos) {
    colpi tmp = new colpo;
    tmp->curr = Bullet(pos);
    tmp->next = gun;
    gun = tmp;
}

void BigMap::update_shoot(int limit_sx, int limit_dx, bool going_right){
    colpi aux = gun;
    colpi prec = NULL;
    while(aux!=NULL) {
        Mario.show();
        if(aux->curr.getPosx()==limit_sx) {
            if(not_this('|', true, aux->curr.getPos(), going_right)) {
                aux->curr.go_dx();
            }
            else{
                //aggiungere verifica di COSA colpisce
                colpi tmp;
                if(prec == NULL){
                    tmp = aux;
                    aux = aux->next;
                    delete(tmp);
                    tmp = NULL;
                    gun = aux;
                }
                else{
                    tmp = aux;
                    aux = aux->next;
                    prec->next = aux;
                    delete (tmp);
                    tmp = NULL;
                }
            }
        }
        else {
            if(aux->curr.getPosx()<limit_dx-1) {
                aux->curr.destroy_win();
                if(not_this('|', true, aux->curr.getPos(), going_right)) {
                    aux->curr.go_dx();
                }
                else{
                    //aggiungere verifica di COSA colpisce
                    colpi tmp;
                    if(prec == NULL){
                        tmp = aux;
                        aux = aux->next;
                        delete(tmp);
                        tmp = NULL;
                        gun = aux;
                    }
                    else{
                        tmp = aux;
                        aux = aux->next;
                        prec->next = aux;
                        delete (tmp);
                        tmp = NULL;
                    }
                }
            }
            // caso aux->curr.getPosx()==limit_dx
            else {
                aux->curr.destroy_win();
                colpi tmp;
                if(prec == NULL){
                    tmp = aux;
                    aux = aux->next;
                    delete(tmp);
                    tmp = NULL;
                    gun = aux;
                }
                else{
                    tmp = aux;
                    aux = aux->next;
                    prec->next = aux;
                    delete (tmp);
                    tmp = NULL;
                }
            }
        }
        prec = aux;
        if(aux!=NULL)
            aux = aux->next;
    }
}

bool BigMap::not_this(char object, bool dx, position pos, bool going_right) {
    int y_on_pad = pos.y - (LINES-rect_lines)/2;
    int x_on_rect = pos.x - (COLS-rect_cols)/2;

    if(head->prev!=NULL) {
        if(head->prev->piece->how_much() > x_on_rect)
            return !(head->prev->piece->there_is_this(object, y_on_pad,x_on_rect + rect_cols - head->prev->piece->how_much()-1, dx, going_right));
        else{
            if (head->prev->piece->how_much()>-1) {
                return !(head->piece->there_is_this(object, y_on_pad,head->piece->how_much() - rect_cols + x_on_rect+1 ,dx, going_right));
            }
            else {
                if(x_on_rect >= head->piece->how_much())
                    return !(head->next->piece->there_is_this(object, y_on_pad, x_on_rect - head->piece->how_much()-1, dx, going_right));
                else
                    return !(head->piece->there_is_this(object, y_on_pad,rect_cols - head->piece->how_much() + x_on_rect-1, dx, going_right));
            }
        }
    }
    else {
        if(x_on_rect >= head->piece->how_much())
            return !(head->next->piece->there_is_this(object, y_on_pad, x_on_rect - head->piece->how_much()-1, dx, going_right));
        else
            //return head->piece->there_is_this(object, y_on_pad,rect_cols - head->piece->how_much() + x_on_rect-1, dx, going_right);
            return true;
    }
}

void BigMap::routine_fineciclo(bool right) {
    Mario.show();
    reshow_map();
    update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1, right);
    Mario.show();
}
void BigMap::reshow_map(){
    if(head->prev!=NULL && head->prev->piece->how_much() > -1) {
        head->prev->piece->show();
    }
    head->piece->show();
    if(head->next!=NULL && head->next->piece->how_much() > -1) {
        head->next->piece->show();
    }
}