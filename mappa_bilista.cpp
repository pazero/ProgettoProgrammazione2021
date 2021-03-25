#include <string.h>
#include <iostream>
#include <ncurses.h>
using namespace std;

class Map {
    protected:
    WINDOW *mappa;
    bool first;

    int rect_lines;
    int rect_cols;

    int pad_x;
    int pad_y = 0;

    int sy;
    int sx;
    int ey;
    int ex;
    
    int iniziox_rect;
    int finex_rect;
    int inizioy_rect;
    int finey_rect;
    public:
    Map(int rect_lines, int rect_cols, bool first = false) {
        this->first = first;
        
        this->iniziox_rect = (COLS - rect_cols)/2;
        this->finex_rect = (COLS + rect_cols)/2 - 1;
        this->inizioy_rect = (LINES - rect_lines)/2;
        this->finey_rect = (LINES + rect_lines)/2;
        
        if(first) {
            this->sx = iniziox_rect;
        }
        else {
            this->sx = finex_rect+1;
        }
        this->ex = finex_rect;
        this->sy = inizioy_rect;
        this->ey = finey_rect;
        

        this->rect_lines = rect_lines;
        this->rect_cols = rect_cols;

        this->pad_x = 0;

        mappa = newpad(rect_lines, rect_cols);
        refresh();
        mvprintw(inizioy_rect-1, finex_rect, "!");
        mvprintw(inizioy_rect-1, iniziox_rect, "!");
    }
    void build(){
        for(int i=0; i<rect_cols; i++) {
            if(i%10==0) {
                mvwaddch(mappa,0,i,'$');
                mvwaddch(mappa,rect_lines-1,i,'$');
            }
            else {
                mvwaddch(mappa,0,i,'-');
                mvwaddch(mappa,rect_lines-1,i,'-');
            }
        }
        if(first) {
            mvwaddstr(mappa,0,0,"          ");
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
    }
    void pad_refresh(int pad_x,int sx,int ex) {
        prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
    }
    void rslide(){
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
        pad_refresh(pad_x, sx, ex);
    }
    void lslide(){
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
        pad_refresh(pad_x, sx, ex);
    }
    bool nx() {
        if(ex<finex_rect) 
            return true;
        else return false;
    }
    bool previous() {
        if(sx>iniziox_rect)
            return true;
        else return false;
    }
    void show(){
        prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
    }

    int how_much() {
        return ex - sx;
    }
};

typedef Map *ptMap;
struct Mappa {
        ptMap piece;
        int n;
        Mappa *next;
        Mappa *prev;
    };
typedef Mappa *Mappona;

class BigMap {
    protected:
        Mappona head = new Mappa;
        int rect_lines;
        int rect_cols;

        int nodi;
    public:
    BigMap(int rect_lines, int rect_cols) {
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
    void addMap() {
        nodi++;
        Mappona aux = head;
        Mappona prec = NULL;
        while(aux->next!=NULL) {
            aux = aux->next;
        }
        prec = aux;
        aux->next = new Mappa;
        aux->next->piece = new Map(rect_lines, rect_cols);
        aux->next->piece->build();

        aux->next->n = nodi;
        aux->next->next = NULL;
        aux->next->prev = prec;
        
        prec = NULL;
        delete(prec);
        mvprintw(LINES/2 -3,0,"Aggiunta nodo numero: %d", nodi);
    }
    void update() {
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
    void slideMappona(int ch) {
        update();
        mvprintw(LINES/2,0,   "Current node: %d", head->n);
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
    }
};

int main() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int rect_lines = 19;
    int rect_cols = 80;
    
    BigMap infinita = BigMap(rect_lines, rect_cols);
    int ch;
    while((ch = getch()) != KEY_F(1)) {
        infinita.slideMappona(ch);
    }
    endwin();
    return 0;
}