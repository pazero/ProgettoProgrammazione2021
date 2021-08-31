#include <ncurses.h>
//struttura per le coordinate delle entità
struct position{
    int y;
    int x;
};
class Oggetto{
    protected:
    position pos;   //posizione entità
    char name;      //nome entità

    public:
    Oggetto(position pos);
    Oggetto();
    position getPos();  //ritorna la posizione dell'entità
    int getPosy();  //ritorna la coordinata y dell'entità 
    int getPosx();  //ritorna la coordinata x dell'entità
    void show();    //stampa l'entità a schermo
    char get_name();    //ritorna il nome dell'entità
};