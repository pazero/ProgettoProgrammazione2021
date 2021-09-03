#include "ClasseEnemy.hpp"

struct colpo {
    Bullet curr{};
    colpo *next;
};
typedef colpo* colpi;

struct nemico {
    Enemy bad;
    nemico *next;
};

typedef nemico* lista_nemici;

class Map {
    protected:
    WINDOW *mappa;
    bool first; //indica se il pezzo di mappa è il primo nella lista

    int rect_lines; //altezza della mappa
    int rect_cols; //larghezza della mappa
    int n; //numero della mappa

    int pad_x; //coordinata orizzontale da cui cominciare a guardare la mappa
    int pad_y; //coordinata verticale da cui cominciare a guardare la mappa

    int sy; //coordinata y del vertice in alto a sinistra del pezzo di mappa che si vede a schermo
    int sx; //coordinata x del vertice in alto a sinistra del pezzo di mappa che si vede a schermo
    int ey; //coordinata y del vertice in basso a destra del pezzo di mappa che si vede a schermo
    int ex; //coordinata x del vertice in basso a destra del pezzo di mappa che si vede a schermo
    
    int inizioy_rect; //coordinata y del vertice in alto a sinistra della finestra di gioco
    int iniziox_rect; //coordinata x del vertice in alto a sinistra della finestra di gioco
    int finey_rect; //coordinata y del vertice in basso a destra della finestra di gioco
    int finex_rect; //coordinata x del vertice in basso a destra della finestra di gioco

    Bonus powerup{}; //campo utilizzato per la gestione dei bonus
    lista_nemici nemici; //lista che memorizza tutti i nemici presenti nella mappa
    int count_move; //contatore usato per gestire il movimento dei nemici K
    int count_A; //contatore usato per gestire l'azione dei nemici A

    public:
    Map(int rect_lines, int rect_cols, int n, bool first = false);
    void build(); //metodo che gestisce l'inserimento delle piattaforme nella mappa
    void add_plat(int type, int y, int x); //metodo che aggiunge una piattaforma alla mappa
    void rand_plat(); //metodo che sceglie randomicamente una disposizione per un set di piattaforme
    
    void spawn_enemy(int n); //metodo per aggiungere nemici alla mappa

    void rslide(); //metodo che fa scorrere la mappa a sinistra dando così il senso di movimento a destra dell'Eroe
    void lslide(); //metodo che fa scorrere la mappa a destra dando così il senso di movimento a sinistra dell'Eroe
    bool nx(); //metodo che restituisce true se è visibile a schermo il pezzo di mappa successivo a questo
    bool previous(); //metodo che restituisce true se è visibile a schermo il pezzo di mappa precedente a questo
    
    void show(); //metodo che stampa la mappa a schermo
    int how_much(); //metodo che ritorna il numero di colonne della mappa visibili a schermo
    
    bool can_fall(int y, int x); //metodo che ritorna true se un oggetto può cadere o meno dalla posizione in cui è
    bool can_pass_through(int y, int x, bool up); //metodo che ritorna true se un oggetto può salire o scendere da una piattaforma
    bool there_is_this(char object, int pady, int padx, bool dx, bool going_right); //metodo che ritorna true se in una data posizione c'è un certo oggetto

    void print_space(int y_on_pad, int x_on_pad); //metodo che stampa uno spazio in una data posizione
    void print_player(char player_name, int y, int stacco); //metodo che stampa l'Eroe nella sua posizione
    void move_enemies(); //metodo che gestisce il movimento dei nemici K
    void enemies_A(); //metodo che gestisce le azioni dei nemici A
    void remove_enemy(position pos); //metodo che rimuove un nemico dall'apposita lista

    int get_n(); //metodo che ritorna il numero di questo pezzo di mappa
    void spawn_bonus(); //metodo che gestise la disposizione dei bonus
};