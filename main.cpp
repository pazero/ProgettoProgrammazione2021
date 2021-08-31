#include "ClasseMotore.hpp"
#include "Comandi.hpp"
using namespace std;
//dichiaro le costanti per l'altezza e la larghezza della finestra di gioco
#define RECT_LINES 19
#define RECT_COLS 100
int main() {
    Comandi();
    Motore(RECT_LINES, RECT_COLS);
    return 0;
}

/*
paolo   BigMap
simo    Map
andre   bonus, oggetto, eroe, bullet, Enemy, motore

comandi, main
*/