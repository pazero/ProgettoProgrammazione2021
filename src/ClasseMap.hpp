#include <cstring>
#include <ncurses.h>
#include <ctime>
#include <iostream>
#include <cstdlib>
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
    Map(int rect_lines, int rect_cols, bool first = false);
    void build();
    void add_plat(int type, int length, int y, int x);
    void rand_plat();
    void rslide();
    void lslide();
    bool nx();
    bool previous();
    void show();
    int how_much();
    void pad_refresh(int pad_x,int sx,int ex);
    bool is_plat(int y, int x, int how_prev, bool is_prec);
    bool is_wall(int y, int x, int how_prev, bool is_prec, bool dx);
    bool is_freeup(int y, int x, int how_prev, bool is_prec);
    bool is_empty(int y, int how_prev, int pad, bool dx);
    int player_pos();
};