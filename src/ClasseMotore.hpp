#include <ncurses.h>
#include "ClasseBigMap.hpp"

class Motore{
    protected:
    int rect_lines;
    int rect_cols;
    BigMap infinita{};
    int ch;
    bool pause=false;
    bool right;
    int time;
    int cicli_for_bonus;
    int aux_nodi;
    int bonus;
    
    public:
    Motore(int rect_lines, int rect_cols);
    void move_all();
    void go_game();
    void update_time();
    bool check_bonus();
    void count_n_cicli(int n);
};