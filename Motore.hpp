#include <ncurses.h>
#include "WorldGen.hpp"
class Motore{
    protected:
    int rect_lines;
    int rect_cols;
    WorldGen infinita{};
    int ch;
    bool pause = false;

    public:
    Motore(int rect_lines, int rect_cols);
    void move_all();
    void go_game();
};