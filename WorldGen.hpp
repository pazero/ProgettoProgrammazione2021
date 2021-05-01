#include "Map.hpp"
#include <ncurses.h>
// questa classe crea una lista bidirezionale i cui nodi sono finestre costruite dalla classe Map
// contiene metodi per:
// 1) aggiungere un nodo alla lista(pezzo di mappa)
// 2) muovere la mappa (utilizzando i metodi di Map)
// 3) aggiornare posizioni delle entità presenti a schermo (utilizzando i metodi di Map)
// 4) controllo collisioni (utilizzando i metodi di Map)

struct colpo
{
    Bullet curr{};
    colpo *next;
};
typedef colpo *colpi;

struct MapNode
{
    Map *piece;
    int n;
    MapNode *next;
    MapNode *prev;
};
typedef MapNode *MapList;

class WorldGen
{
protected:
    MapList head = new MapNode;
    int rect_lines;
    int rect_cols;
    int nodi;
    int life;
    int stacco; // distanza giocatore dal bordo sinistro
    Eroe Mario{};

    int count_bullet;

    colpi gun;

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
    // 3)
    void add_bullet(position pos);
    void update_shoot(int stacco, int rect_cols, bool right);
    void routine_fineciclo(bool right);
    void reshow_map();
    // 4)
    bool free_down(int y_on_pad);
    bool not_this(char object, bool dx, position pos, bool going_right);
    int n_map();
    bool is_bonus();
    void get_bonus();
    int damage(int life);
    int get_life(int life);
    bool hit_enemy();
    bool is_enemy();
};