#include "ClasseMap.hpp"
struct MapNode {
        Map *piece;
        int n;
        MapNode *next;
        MapNode *prev;
    };
typedef MapNode* MapList;

class BigMap{
    protected:
        MapList curr = new MapNode;
        int rect_lines; //altezza finestra di gioco
        int rect_cols; //larghezza finestra di gioco
        int nodi; //numeri nodi della bilista

        int stacco; //distanza dell'Eroe dal margine sinistro della finestra di gioco
        Eroe Mario{}; //dichiarazione dell'Eroe
        //contatori per i diversi tipi di proiettili
        int count_Bullet;
        int count_backBullet;
        int count_ghostBullet;
        //liste per tener traccia dei vari tipi di proiettili
        colpi gun;
        colpi backGun;
        colpi ghostGun;
        
        WINDOW *health_win; //dichiarazione finestra per la barra della vita
        int points; //variabile per memorizzare punti ottenuti durante il gioco
        int killer_prize; //variabile per bonus &
        bool warning; //variabile per sapere se l'Eroe ha appena perso vita

    public:
    BigMap();
    BigMap(int rect_lines, int rect_cols);
    void addMap(); //aggiunge un pezzo di mappa per rendere infinito il percorso 
    void update(); //aggiorna la situazione delle mappe, controllando qual è il pezzo di mappa principale in quel momento
    int n_map(); //ritorna il numero di nodi che ha la bilista

    void go_left(); //si sposta la mappa a destra mentre l'Eroe sta fermo
    void go_right(); //si sposta la mppa a sinistra mentre l'Eroe sta fermo
    void go_up(); //l'Eroe va su, se possibile
    void go_down(); //l'Eroe va giù, se possibile
    
    void shoot(); //aggiornamenti spari dell'Eroe verso destra
    void back_shoot(); //aggiornamenti spari dell'Eroe verso sinistra
    void add_bullet(position pos); //si spara un proiettile a destra
    void add_backbullet(position pos); //si spara un proiettile a sinsitra
    void remove_bullet(colpi &prec, colpi &aux, int type); //si rimuove un certo proiettile da una lista
    void update_shoot(int stacco,int rect_cols, bool right); //si aggiorna movimento spari verso destra
    void update_back_shoot(int limit_sx, int limit_dx, bool going_right); //si aggiorna movimento spari verso sinistra
    
    void add_ghost_bullet(int y); //aggiunge un nemico alla lista di "spari fantasma"
    void free_bullet(); //gestisce un certo tipo di nemico che sono come degli "spari fantasma"
    void update_ghost_shoot(); //aggiorna gli "spari fantasma"

    bool free_down(int y_on_pad); //controlla che al di sotto sia libero
    bool not_this(char object, bool dx, position pos, bool going_right); //controlla che non ci sia un determinato carattere a destra o sinistra della posizione data

    bool routine_fineciclo(bool right); //routine con controlli e azioni da fare alla fine di ogni ciclo
    void reshow_map(); //ristampa a schermo tutto ciò che si deve vedere in quel momento

    char is_bonus(); //ritorna quale bonus ha preso l'Eroe (ritorna ' ' se non ha preso bonus)
    void delete_char(int y, int x); //cancella un carattere in una data posizione

    void health_bar(); //aggiorna la barra della vita
    int get_points(); //ritorna il punteggio ottenuto in quel momento
    void set_killer_prize(int n); //setta una variabile funzionale a un certo tipo di bonus
    bool get_warning(); //ritorna la variabile warning, che indica se l'Eroe ha appena subito danno o no
};
