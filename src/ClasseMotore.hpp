#include <ncurses.h>
#include "ClasseBigMap.hpp"

class Motore{
    protected:
    int rect_lines;
    int rect_cols;
    BigMap infinita{};
    int ch;
    bool pause=false;

    public:
    Motore(int rect_lines, int rect_cols);
    void move_all();
    void go_game();
};