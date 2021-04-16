#include "Map.hpp"
#include "Bullet.hpp"

struct Node
{
    int n;
    Map *piece;
    Bullet  curr;
    Node *next;
    Node *prev;
};
typedef Node *List;

