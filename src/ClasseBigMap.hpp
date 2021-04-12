#include "ClasseMap.hpp"
#include "ClasseEroe.hpp"
#include <ncurses.h>
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

    public:
    BigMap();
    BigMap(int rect_lines, int rect_cols);
    void addMap();
    void update();
    void go_left();
    void go_right();
    void go_up();
    void shoot();
    void routine_fineciclo();
    bool is_freeplatform(int y_on_pad);
    bool ostacolo(int y_on_pad, bool dx);
};