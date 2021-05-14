#include "Map.hpp"
#include <ncurses.h>
// questa classe crea una lista bidirezionale i cui nodi sono finestre costruite dalla classe Map
// contiene metodi per:
// 1) aggiungere un nodo alla lista(pezzo di mappa)
// 2) muovere la mappa e il giocatore(utilizzando i metodi di Map)
// 3) controllo collisioni (utilizzando i metodi di Map)
// 4) sparare proiettili
// 5) aggiornare posizioni delle entità e status della mappa
// 6) funzioni ausiliarie (utili soprattutto alla classe motore)
struct colpo {
    Bullet curr{};
    colpo *next;
};
typedef colpo* colpi;

struct MapNode {
        Map *piece;
        int n;
        MapNode *next;
        MapNode *prev;
    };
typedef MapNode* MapList;

class WorldGen {
    protected:
        MapList head = new MapNode;
        int rect_lines;
        int rect_cols;
        int nodi;

        int stacco;
        Eroe Mario{};
        

        int count_bullet;
        int count_backbullet;
        
        colpi gun;
        colpi backgun;

    
    public:
    WorldGen();
    WorldGen(int rect_lines, int rect_cols);
    // 1)
    void addMap();
    void update();
    // 2)
    void go_left();
    void go_right();
    void go_up();
    void go_down();
    void shoot();
    void back_shoot();
    // 3)
    bool free_down(int y_on_pad);
    bool not_this(char object, bool dx, position pos, bool going_right);
    // 4)
    void add_bullet(position pos);
    void add_backbullet(position pos);
    void remove_bullet(colpi &prec, colpi &aux, bool back);
    void update_shoot(int stacco,int rect_cols, bool right);
    void update_back_shoot(int limit_sx, int limit_dx, bool going_right);
    // 5)
    bool routine_fineciclo(bool right);
    void reshow_map();
    void health_bar();
    // 6)
    int n_map();
    bool is_bonus();
    void is_enemy();
    void delete_char(int y, int x);
};