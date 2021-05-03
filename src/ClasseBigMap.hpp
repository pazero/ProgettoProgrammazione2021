#include "ClasseMap.hpp"

#include <ncurses.h>

struct colpo {
    Bullet curr{};
    colpo *next;
};
typedef colpo* colpi;

struct MapNode {
        Map *piece;
        int n;
        MapNode *next;
        MapNode *prev;
    };
typedef MapNode* MapList;

class BigMap {
    protected:
        MapList head = new MapNode;
        int rect_lines;
        int rect_cols;
        int nodi;

        int stacco;
        Eroe Mario{};
        

        int count_bullet;
        int count_backbullet;
        
        colpi gun;
        colpi backgun;

    
    public:
    BigMap();
    BigMap(int rect_lines, int rect_cols);
    void addMap();
    void update();

    void go_left();
    void go_right();
    void go_up();
    void go_down();
    void shoot();
    void back_shoot();

    bool free_down(int y_on_pad);
    bool not_this(char object, bool dx, position pos, bool going_right);

    void add_bullet(position pos);
    void add_backbullet(position pos);
    void remove_bullet(colpi &prec, colpi &aux, bool back);
    void update_shoot(int stacco,int rect_cols, bool right);
    void update_back_shoot(int limit_sx, int limit_dx, bool going_right);

    bool routine_fineciclo(bool right);
    void reshow_map();

    int n_map();
    bool is_bonus();
    void delete_char(int y, int x);
};