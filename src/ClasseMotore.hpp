#include <ncurses.h>
#include "ClasseBigMap.hpp"

class Motore{
    protected:
    int rect_lines; //altezza finestra di gioco
    int rect_cols; //larghezza finestra di gioco

    BigMap infinita{}; //dichiarazione della mappa infinita
    int nodi; //numero nodi della bilista infinita
    
    int ch; //variabile usata insieme al metodo getch() che memorizza il tasto premuto dall'user
    bool dead; //booleano per la morte dell'eroe
    bool right; //variabile necessaria ad alcuni metodi in BigMap che indica se l'Eroe si sta muovendo verso destra
    
    int time; //tempo in ms tra un ciclo e l'altro
    int cicli_for_bonus; //numero di cicli in cui è attivo un bonus
    int bonus_time; //variabile che viene sommata a "time" in modo da aumentare il tempo tra un ciclo e l'altro, usata per un bonus

    public:
    Motore(int rect_lines, int rect_cols);
    void go_game();     //metodo che avvia il gioco
    bool move_all();    //metodo che si occupa di far muovere l'Eroe e restituire false solo se l'Eroe è morto
    void update_time(); //metodo per aumentare la velocità del gioco con l'avanzare dell'Eroe nel gioco
    void check_bonus(); //metodo che controlla i bonus attivi
    void check_cicli(); //metodo necessario ai bonus "#" e "&", che fa durare i loro effetti per una certo numero di cicli

    bool start_menu();      //menu iniziale
    void death_menu();      //menu morte
    bool pause_menu();      //menu pausa
    void tutorial_page();   //menu tutorial
    void credit_page();     //menu crediti
    void print_gameOver();  //stampa la finestra gameover
};