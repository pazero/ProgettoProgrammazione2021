#include <cstring>
#include <ncurses.h>
#include <ctime>
#include <iostream>
#include <cstdlib>

// questa classe permette di creare un pad con piattaforme casuali, inoltre ha:
// 1) metodi per muovere il pad
// 2) metodi di controllo per la lista bidirezionale
// 3) metodi per rilevare piattaforme e ostacoli
class Map
{
protected:
    WINDOW *mappa;
    // booleano atto a controllare se si è nello spawn iniziale del mondo
    bool first;
    // numero di righe e colonne della finestra "mappa"
    int rect_lines;
    int rect_cols;
    // coordinata x dell'angolo in alto a sx del pad da cui si vuole cominciare
    // a copiare
    int pad_x;
    // coordinata x dell'angolo in alto a sx del pad da cui si vuole cominciare
    // a copiare
    int pad_y = 0;
    // y dell'angolo in alto a sx del rettangolo da visualizzare sullo std screen
    int sy;
    // x dell'angolo in alto a sx del rettangolo da visualizzare sullo std screen
    int sx;
    // y dell'angolo in basso a dx del rettangolo da visualizzare sullo std screen
    int ey;
    // x dell'angolo in basso a dx del rettangolo da visualizzare sullo std screen
    int ex;
    // x dell'angolo in alto a sx della finestra mappa
    int iniziox_rect;
    // x dell'angolo in basso a dx della finestra mappa
    int finex_rect;
    // y dell'angolo in alto a sx della finestra mappa
    int inizioy_rect;
    // y dell'angolo in basso a dx della finestra mappa
    int finey_rect;

public:
    Map(int rect_lines, int rect_cols, bool first = false);
    void build();
    void add_plat(int type, int length, int y, int x);
    void rand_plat();
    // 1)
    void rslide();
    void lslide();
    // 2)
    bool next();
    bool previous();
    void show();
    int how_much();
    void pad_refresh(int pad_x, int sx, int ex);
    // 3)
    bool is_plat(int y, int x, int how_prev, bool is_prec);
    bool is_wall(int y, int x, int how_prev, bool is_prec, bool is_dx);
    bool is_freeup(int y, int x, int how_prev, bool is_prec);
    int player_pos();
};