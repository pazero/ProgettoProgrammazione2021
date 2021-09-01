#include "ClasseMotore.hpp"
#include "Comandi.hpp"
using namespace std;
int main() {
    //classe che esegue comandi necessari all'avvio delle modalità per far funzionare il gioco 
    Comandi();
    //dichiaro le variabile per l'altezza e la larghezza della finestra di gioco
    int rect_lines = 19;
    int rect_cols = 100;
    //classe che avvia il funzionamento del gioco
    Motore(rect_lines, rect_cols);
    return 0;
}