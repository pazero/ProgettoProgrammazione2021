#include "ClasseMap.hpp"
#include "ClasseBullet.hpp"
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

        int stacco = 30;
        Eroe Mario{};

        int count=0;
        
        colpi gun;

    
    public:
    BigMap();
    BigMap(int rect_lines, int rect_cols);
    void addMap();
    void update();

    void go_left();
    void go_right();
    void go_up();
    void shoot();

    bool free_down(int y_on_pad);
    bool not_this(char object, bool dx, position pos, bool going_right);

    void add_bullet(position pos);
    void update_shoot(int stacco,int rect_cols, bool right);

    void routine_fineciclo(bool right);
    void reshow_map();
};