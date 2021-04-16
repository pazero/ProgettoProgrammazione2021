#include "Map.hpp"
#include "Bullet.hpp"
// struttura per la lista bidirezionale
struct Node
{
    int n;
    Map *piece; // "pezzo di mappa": puntatore di tipo Map che crea dei nodi 
                // con le caratteristiche definite dalla classe Map 
    Bullet  curr;
    Node *next;
    Node *prev;
};
typedef Node *List;

