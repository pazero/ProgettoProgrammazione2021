#include <ncurses.h>
#include "WorldGen.hpp"
// questa classe prende in input le dimensione della finestra e mette in moto 
// il gioco, ciclando ogni volta che riceve un input da tastiera, può farlo
// anche senza ogni 100 ms, questo timeout ogni 10 mappe diminuisce di 2 

class Motore{
    protected:
    int rect_lines;
    int rect_cols;
    WorldGen infinita{};
    int ch;
    bool pause=false;
    bool right;
    int time;
    int cicli;
    int aux_nodi;
    int bonus;
    
    public:
    Motore(int rect_lines, int rect_cols);
    void move_all();
    void go_game();
    void update_time();
    bool check_bonus();
    void count_n_cicli();
    void death_menu();
};