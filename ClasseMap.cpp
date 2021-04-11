#include "ClasseMap.hpp"

Map::Map(int rect_lines, int rect_cols, bool first) {
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
}

void Map::build(){
    for(int i=0; i<rect_cols; i++) {
        mvwaddch(mappa,0,i,'=');
        mvwaddch(mappa,1,i,'=');
        mvwaddch(mappa,rect_lines-2,i,'=');
        mvwaddch(mappa,rect_lines-1,i,'=');
    }
    if(!first)
        rand_plat();
    if(first) {
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
    mvwaddch(mappa,0,rect_cols-1,'|');
    mvwaddch(mappa,rect_lines-1,rect_cols-1,'|');
}

void Map::add_plat(int type, int length, int y, int x) {
    if(type==0) {
        mvwprintw(mappa,y,x,"+++++ +++++");
        mvwprintw(mappa,y+1,x+4,"|");
    }
    if(type==1) {
        mvwprintw(mappa,y-2,x+5,     "++++++++++");
        mvwprintw(mappa,y,x,    "++++++++++");
    }
    if(type==2) {
        mvwprintw(mappa,y-4,x-1,"++++++++++");
        mvwprintw(mappa,y-2,x+7,        "++++++++");
        mvwprintw(mappa,y,x,     "+++++++++++");
    }
    if(type==3) {
        mvwprintw(mappa,y-4,x+4,       "++++++++++");
        mvwprintw(mappa,y-2,x-3,"+++++++++++");
        mvwprintw(mappa,y,x,       "++++++++++");
    }
    if(type==4) {
        mvwprintw(mappa,y-6,x-1,"+++++++");
        mvwprintw(mappa,y-4,x,"+++++++++++");
        mvwprintw(mappa,y-2,x+1, "+++++++++");
        mvwprintw(mappa,y,x,  "++++++++++");
    }
    if(type==5){
        mvwprintw(mappa,y-6,x,   "++++++++");
        mvwprintw(mappa,y-4,x+3,      "++++++++++");
        mvwprintw(mappa,y-2,x-2, "++++++++");
        mvwprintw(mappa,y,x,       "++++++++++");
        mvwprintw(mappa,y-1,x+3, "|");
    }
    if(type==6){
        mvwprintw(mappa,y-8,x-2,     "+++++++++++++");
        mvwprintw(mappa,y-6,x-4, "+++++++++++  +++");
        mvwprintw(mappa,y-4,x+4,       "++++++++++");
        mvwprintw(mappa,y-2,x-2,     "+++++++++");
        mvwprintw(mappa,y,x,           "++++++++");
    }
}
void Map::rand_plat() {
    int c;
    int rand_space;
    int stop = 5;
    srand(time(0));
    int length = 10;
    while(stop<rect_cols-15) {
        c = rand()%7;
        add_plat(c,length,rect_lines -4,stop);
        rand_space = rand()%3;
        stop+=length*rand_space;
    }
}

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
    pad_refresh(pad_x, sx, ex);
}
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
    pad_refresh(pad_x, sx, ex);
}
bool Map::nx() {
    if(ex<finex_rect) 
        return true;
    else return false;
}
bool Map::previous() {
    if(sx>iniziox_rect)
        return true;
    else return false;
}
void Map::show(){
    prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
}

int Map::how_much() {
    return ex - sx;
}

void Map::pad_refresh(int pad_x,int sx,int ex) {
    prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
}

bool Map::is_plat(int y, int x, int how_prev, bool is_prec) {
    if(is_prec) {
        return mvwinch(mappa, y-1,x+(rect_cols-how_prev)) == '+';
    }
    else {
        return mvwinch(mappa, y-1, how_prev) == '+';
    }
}

bool Map::is_wall(int y, int x, int how_prev, bool is_prec, bool is_dx) {
    if(is_dx) {
        if(is_prec) {
            return mvwinch(mappa, y,x+(rect_cols-how_prev)+1) == '|';
        }
        else {
            return mvwinch(mappa, y, how_prev+1) == '|';
        }
    }
    else {
        if(is_prec) {
            return mvwinch(mappa, y,x+(rect_cols-how_prev)-1) == '|';
        }
        else {
            return mvwinch(mappa, y, how_prev-1) == '|';
        }
    }
}