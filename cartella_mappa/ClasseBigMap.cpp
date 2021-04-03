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
bool BigMap::slideMap(int ch) {
    update();
    mvprintw(LINES/2,0,   "Current node: %d  ", head->n);
    if(ch == KEY_LEFT){
        head->piece->lslide();
        if(head->next!=NULL) {
            head->next->piece->lslide();
        }
        if(head->prev!=NULL) {
            if(head->piece->previous())
                head->prev->piece->lslide();
        }
    }
    if(ch == KEY_RIGHT){
        head->piece->rslide();
        if(head->next!=NULL) {
            if(head->piece->nx())
                head->next->piece->rslide();
        }
        if(head->prev!=NULL)
            head->prev->piece->rslide();
    }
    if(ch == KEY_F(1)) return false;
    return true;
}
bool BigMap::is_platform(int y, int x) {
    //if(head->prev->piece!=NULL) return head->piece->is_plat(y,x)||head->prev->piece->is_plat(y,x);
    return head->piece->is_plat(y,x);
} 