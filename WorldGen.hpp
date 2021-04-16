#include "Eroe.hpp"
// questa classe crea una lista bidirezionale i cui nodi sono finestre costruite dalla classe Map
// contiene metodi per:
// 1) aggiungere un nodo alla lista(pezzo di mappa)
// 2) muovere la mappa (utilizzando i metodi di Map)
// 3) aggiornare posizioni delle entità presenti a schermo (utilizzando i metodi di Map)
// 4) controllo collisioni (utilizzando i metodi di Map)
class WorldGen
{
protected:
    List head = new Node;
    int rect_lines;
    int rect_cols;
    int nodi;
    //distanza dell'eroe dal bordo sinistro della mappa
    int stacco = 30;
    Eroe Mario{};

    int count = 0;

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
    void shoot();
    // 3)
    void routine_fineciclo();
    // 4)
    bool is_freeplatform(int y_on_pad);
    bool ostacolo(int y_on_pad, bool dx);
};
