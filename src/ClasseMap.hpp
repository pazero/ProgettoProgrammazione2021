#include <cstring>
#include <ncurses.h>
#include <ctime>
#include <iostream>
#include <cstdlib>

#include "ClasseEnemy.hpp"

struct colpo {
    Bullet curr{};
    colpo *next;
};
typedef colpo* colpi;

struct nemico {
    Enemy bad;
    nemico *next;
};

typedef nemico* lista_nemici;

class Map {
    protected:
    WINDOW *mappa;
    bool first;

    int rect_lines;
    int rect_cols;
    int n;

    int pad_x;
    int pad_y;

    int sy;
    int sx;
    int ey;
    int ex;
    
    int iniziox_rect;
    int finex_rect;
    int inizioy_rect;
    int finey_rect;

    Bonus powerup{};
    lista_nemici nemici;
    //usato per nemici
    int count_move;
    int count_A;

    public:
    Map(int rect_lines, int rect_cols, int n, bool first = false);
    void build();
    void add_plat(int type, int y, int x);
    void rand_plat();
    
    void spawn_enemy(int n);

    void rslide();
    void lslide();
    bool nx();
    bool previous();
    
    void show();
    int how_much();
    
    bool can_fall(int y, int x);
    bool can_pass_through(int y, int x, bool up);
    bool there_is_this(char object, int pady, int padx, bool dx, bool going_right);

    void print_space(int y_on_pad, int x_on_pad);
    void print_player(char player_name, int y, int stacco);
    void move_enemies();
    void enemies_A();
    void remove_enemy(position pos);

    int get_sx();
    int get_ex();

    int get_n();
    void spawn_bonus();
};