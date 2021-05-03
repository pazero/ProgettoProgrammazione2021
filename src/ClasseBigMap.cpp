#include "ClasseBigMap.hpp"
BigMap::BigMap(){}
BigMap::BigMap(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    nodi = 1;
    count_bullet=3;
    count_backbullet=3;
    stacco = 30;

    head->piece = new Map(rect_lines, rect_cols, nodi, true);
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
    backgun = NULL;
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
    aux->next->piece = new Map(rect_lines, rect_cols, nodi);
    aux->next->piece->build();

    aux->next->n = nodi;
    aux->next->next = NULL;
    aux->next->prev = prec;
    
    prec = NULL;
    delete(prec);
    //mvprintw(LINES/2 +1,0,"Aggiunta nodo numero: %d", nodi);
}
void BigMap::update() {
    count_bullet++;
    count_backbullet++;
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
    Mario.show();
}
void BigMap::go_left(){
    if(not_this('|', false, Mario.getPos(), false) && not_this('K', false, Mario.getPos(), false)) {
        head->piece->lslide();
        Mario.show();
        if(head->next!=NULL) {
            head->next->piece->lslide();
            Mario.show();
        }
        if(head->prev!=NULL) {
            if(head->piece->previous())
                head->prev->piece->lslide();
        }
        Mario.show();
        while (Mario.getPosy()<(LINES+rect_lines)/2 -3 && free_down(Mario.getPosy() - (LINES-rect_lines)/2))
            Mario.go_down();
            
        update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1, false);
    }
}

void BigMap::go_right()
{
    if (not_this('|', true, Mario.getPos(), false) && not_this('K', true, Mario.getPos(), false))
    {
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
    }
}

void BigMap::go_up(){
    int y_on_pad = Mario.getPosy() - (LINES-rect_lines)/2;
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>=stacco) {
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

void BigMap::go_down() {
    int y_on_pad = Mario.getPosy() - (LINES-rect_lines)/2;
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>=stacco) {
            if(head->prev->piece->can_pass_through(y_on_pad,stacco + rect_cols - head->prev->piece->how_much()-1)){
                Mario.go_down();
            }
        }
        else {
            if(head->prev->piece->how_much()>-1) {
                if(head->piece->can_pass_through(y_on_pad,head->piece->how_much() - rect_cols + stacco+1)){
                    Mario.go_down();
                }
            }
            else {
                if(head->piece->can_pass_through(y_on_pad,rect_cols - head->piece->how_much() + stacco-1)){
                    Mario.go_down();
                }
            }
        }
    }
}
void BigMap::shoot(){
    if(count_bullet/3 > 0) {
        add_bullet(Mario.getPos());
        count_bullet=0;
    }
}

void BigMap::back_shoot(){
    if(count_backbullet/3 > 0) {
        add_backbullet(Mario.getPos());
        count_backbullet=0;
    }
}

void BigMap::delete_char(int y, int x){
    int y_on_pad = y - (LINES-rect_lines)/2;
    int x_on_pad = x - (COLS-rect_cols)/2;
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much() >= x_on_pad)
            head->prev->piece->print_space(y_on_pad, x_on_pad + rect_cols - head->prev->piece->how_much() - 1);
        else{
            if (head->prev->piece->how_much()>-1) {
                head->piece->print_space(y_on_pad, head->piece->how_much() - rect_cols + x_on_pad + 1);
            }
            else {
                if(x_on_pad >= head->piece->how_much())
                    head->next->piece->print_space(y_on_pad, x_on_pad - head->piece->how_much()-1);
                else
                    return head->piece->print_space(y_on_pad, rect_cols - head->piece->how_much() + x_on_pad - 1);
            }
        }
    }
    else {
        if(x_on_pad >= head->piece->how_much())
            head->next->piece->print_space(y_on_pad, x_on_pad - head->piece->how_much()-1);
        else
            head->piece->print_space(y_on_pad,rect_cols - head->piece->how_much() + x_on_pad-1);
    }
}

bool BigMap::free_down(int y_on_pad) {
    if(head->prev!=NULL) {
        if(head->prev->piece->how_much()>=stacco)
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
    tmp->curr.set_name('>');
    tmp->next = gun;
    gun = tmp;
}

void BigMap::add_backbullet(position pos) {
    colpi tmp = new colpo;
    tmp->curr = Bullet(pos);
    tmp->curr.set_name('<');
    tmp->next = backgun;
    backgun = tmp;
}

void BigMap::remove_bullet(colpi &prec, colpi &aux, bool back){
    colpi tmp;
    if(prec == NULL){
        tmp = aux;
        aux = aux->next;
        delete(tmp);
        tmp = NULL;
        if(back) backgun = aux;
        else gun = aux;
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
    colpi aux = backgun;
    colpi prec = NULL;
    while(aux!=NULL) {
        Mario.show();
        if(aux->curr.getPosx()==limit_dx) {
            if(not_this('|', false, aux->curr.getPos(), !going_right)) {
                if(not_this('K', false, aux->curr.getPos(), !going_right))
                    aux->curr.go_sx();
                else {
                    delete_char(aux->curr.getPosy(), aux->curr.getPosx()-1);
                    remove_bullet(prec,aux, true);
                }
            }
            else{
                //aggiungere verifica di COSA colpisce
                remove_bullet(prec, aux, true);
            }
            Mario.show();
        }
        else {
            if(aux->curr.getPosx()>limit_sx+1) {
                aux->curr.destroy_win();
                if(not_this('|', false, aux->curr.getPos(), !going_right)) {
                    if(not_this('K', false, aux->curr.getPos(), !going_right))
                        aux->curr.go_sx();
                    else {
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx()-1);
                        remove_bullet(prec,aux, true);
                    }
                }
                else{
                    remove_bullet(prec, aux, true);
                }
            }
            // caso aux->curr.getPosx()==limit_sx
            else {
                aux->curr.destroy_win();
                remove_bullet(prec, aux, true);
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
            if(not_this('|', true, aux->curr.getPos(), going_right)) {
                if(not_this('K', true, aux->curr.getPos(), going_right))
                    aux->curr.go_dx();
                else {
                    delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                    remove_bullet(prec,aux, false);
                }
            }
            else{
                //aggiungere verifica di COSA colpisce
                remove_bullet(prec, aux, false);
            }
            Mario.show();
        }
        else {
            if(aux->curr.getPosx()<limit_dx) {
                aux->curr.destroy_win();
                if(not_this('|', true, aux->curr.getPos(), going_right)) {
                    if(not_this('K', true, aux->curr.getPos(), going_right))
                        aux->curr.go_dx();
                    else {
                        delete_char(aux->curr.getPosy(), aux->curr.getPosx()+1);
                        remove_bullet(prec,aux, false);
                    }
                }
                else{
                    //aggiungere verifica di COSA colpisce
                    remove_bullet(prec, aux, false);
                }
            }
            // caso aux->curr.getPosx()==limit_dx
            else {
                aux->curr.destroy_win();
                remove_bullet(prec, aux, false);
            }
            Mario.show();
        }
        prec = aux;
        if(aux!=NULL)
            aux = aux->next;
    }
}

bool BigMap::not_this(char object, bool dx, position pos, bool going_right) {
    int y_on_pad = pos.y - (LINES-rect_lines)/2;
    int x_on_pad = pos.x - (COLS-rect_cols)/2;

    if(head->prev!=NULL) {
        if(head->prev->piece->how_much() >= x_on_pad)
            return !(head->prev->piece->there_is_this(object, y_on_pad,x_on_pad + rect_cols - head->prev->piece->how_much()-1, dx, going_right));
        else{
            if (head->prev->piece->how_much()>-1) {
                return !(head->piece->there_is_this(object, y_on_pad,head->piece->how_much() - rect_cols + x_on_pad+1 ,dx, going_right));
            }
            else {
                if(x_on_pad >= head->piece->how_much())
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
            //return head->piece->there_is_this(object, y_on_pad,rect_cols - head->piece->how_much() + x_on_pad+1, dx, going_right);
            return true;
    }
}

bool BigMap::routine_fineciclo(bool right) {
    Mario.show();
    reshow_map();
    update_shoot(Mario.getPosx(), rect_cols + (COLS-rect_cols)/2-1, right);
    update_back_shoot((COLS+rect_cols)/2-1 - rect_cols, Mario.getPosx(), right);
    if(!not_this('K', true, Mario.getPos(), false) || !not_this('K', false, Mario.getPos(), false)) {
        Mario.damage(15);
        if(Mario.getlife() < 0)
            Mario.setlife(0);
    }
    mvprintw(14,0,"Life: %d  ", Mario.getlife());
    if(Mario.getlife() == 0) return false;
    Mario.show();
    return true;
}

void BigMap::reshow_map(){
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

int BigMap::n_map() {
    return nodi;
}

bool BigMap::is_bonus(){
    position tmp = {Mario.getPosy(), Mario.getPosx()-1};
    if(!not_this('#', true, tmp, false)) {
        delete_char(tmp.y, tmp.x+1);
        Mario.show();
        return true;
    }
    if(!not_this('*', true, tmp, false)) {
        delete_char(tmp.y, tmp.x+1);
        Mario.bonus_life();
        Mario.show();
    }
    mvprintw(0,10,"      ");
    mvprintw(1,10,"      ");
    return false;
}