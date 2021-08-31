#include <ncurses.h>
#include "ClasseBigMap.hpp"

class Motore{
    protected:
    int rect_lines; //altezza finestra
    int rect_cols;  //larghezza finestra
    BigMap infinita{};  //inizializzo la mappa infinita
    int ch; //variabile usata insieme al metodo getch()
    bool dead;  //booleano per la morte dell'eroe
    bool right; //variabile necessaria al metodo BigMap::routine_fineciclo()
    int time;   //tempo in ms tra un ciclo e l'altro
    int cicli_for_bonus;    //numero di cicli in cui è attivo un bonus
    int nodi;   //numero nodi
    int bonus_time; //variabile che viene sommata a "time" in modo da aumentare il tempo tra un ciclo e l'altro, usata per un bonus

    public:
    Motore(int rect_lines, int rect_cols);
    bool move_all();    //metodo che prende input da tastiera e aggiorna mappa, eroe, ecc. di conseguenza
    void go_game();     //metodo principale che controlla sia il menù che il gioco
    void update_time(); //metodo per aumentare la velocità del gioco con l'aumentare dei nodi esplorati
    void check_bonus(); //metodo che controlla i bonus attivi
    void check_cicli(); //metodo necessario al bonus "#", aumenta il tempo tra un ciclo e l'altro

    void print_gameOver();  //stampa la finestra gameover
    void death_menu();  //menù morte
    bool pause_menu();  //menù pausa
    bool start_menu();  //menù iniziale
    void credit_page(); //menù crediti
    void tutorial_page();   //menù tutorial
};