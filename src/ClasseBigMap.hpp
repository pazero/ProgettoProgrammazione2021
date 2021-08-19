#include "ClasseMap.hpp"
#include <ncurses.h>
#include <ctime>
// ciao
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
        

        int count_Bullet;
        int count_backBullet;
        int count_ghostBullet;
        
        colpi gun;
        colpi backGun;
        colpi ghostGun;

        colpi enemy_gun;
        colpi enemy_backGun;
        
        WINDOW *health_win;

        int points;
        char active_bonus;
        int killer_prize;
        bool warning;

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
    void remove_bullet(colpi &prec, colpi &aux, int type);
    void update_shoot(int stacco,int rect_cols, bool right);
    void update_back_shoot(int limit_sx, int limit_dx, bool going_right);

    bool routine_fineciclo(bool right);
    void reshow_map();

    int n_map();
    char is_bonus();
    void delete_char(int y, int x);

    void health_bar();
    void free_bullet();
    void ghost_shoot();
    void add_ghost_bullet(int y);

    char get_active_bonus();
    void set_print_bonus(char actual_bonus);

    int get_points();
    void set_killer_prize(int n);
    bool get_warning();
};
