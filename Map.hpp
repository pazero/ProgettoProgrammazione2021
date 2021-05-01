#include <cstring>
#include <ncurses.h>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "Enemy.hpp"

struct nemico
{
  Enemy bad;
  nemico *next;
};
typedef nemico *lista_nemici;

// questa classe permette di creare un pad con piattaforme casuali, inoltre ha:
// 1) metodi per muovere il pad
// 2) metodi di controllo per la lista bidirezionale
// 3) metodi per rilevare piattaforme e ostacoli
class Map
{
protected:
  //puntatore alla finestra
  WINDOW *mappa;
  // booleano atto a controllare se si è nello spawn iniziale del mondo
  bool first;
  // numero di righe e colonne della finestra "mappa"
  int rect_lines;
  int rect_cols;
  int n;
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

  Bonus powerup{};
  lista_nemici nemici;

public:
  Map(int rect_lines, int rect_cols, int n, bool first = false);
  // 2)
  void build();
  void add_plat(int type, int y, int x);
  void rand_plat();
  void spawn_bonus(int n);
  void spawn_enemy(int n);
  // 1)
  void rslide();
  void lslide();
  bool nx();
  bool previous();

  void show();
  int how_much();
  // 3)
  bool can_go_up(int y, int how_prev);
  bool can_go_down(int y, int how_prev);
  bool can_pass_through(int y, int how_prev);
  bool there_is_this(char object, int y, int how_prev, bool dx, bool going_right);

  void print_space(int y_on_pad, int x_on_pad);
};