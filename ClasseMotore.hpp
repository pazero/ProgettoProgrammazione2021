#include <ncurses.h>
#include "ClasseBigMap.hpp"

class Motore{
    protected:
    int rect_lines;
    int rect_cols;
    BigMap infinita{};
    int ch;
    //bool pause;
    bool dead;
    bool right;
    int time;
    int cicli_for_bonus;
    int nodi;
    int bonus_time;

    int flash;

    public:
    Motore(int rect_lines, int rect_cols);
    bool move_all();
    void go_game();
    void update_time();
    void check_bonus();
    void check_cicli();
    void death_menu();
    void pause_menu();
};