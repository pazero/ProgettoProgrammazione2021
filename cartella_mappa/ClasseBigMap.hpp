#include "ClasseMap.hpp"
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
    public:
    BigMap(int rect_lines, int rect_cols);
    void addMap();
    void update();
    bool slideMap(int ch);
    bool is_platform(int y, int x);
};