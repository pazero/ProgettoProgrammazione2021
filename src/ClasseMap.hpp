#include <cstring>
#include <ncurses.h>
#include <ctime>
#include <iostream>
#include <cstdlib>

#include "ClasseBonus.hpp"
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

    Bonus powerup{};


    public:
    Map(int rect_lines, int rect_cols, bool first = false);
    void build();
    void add_plat(int type, int length, int y, int x);
    void rand_plat();
    void spawn_bonus(int n);

    void rslide();
    void lslide();
    bool nx();
    bool previous();
    
    void show();
    int how_much();
    
    bool can_go_up(int y, int how_prev);
    bool can_go_down(int y, int how_prev);
    bool there_is_this(char object, int y, int how_prev, bool dx, bool going_right);

    void print_space(int y_on_pad, int x_on_pad);
};