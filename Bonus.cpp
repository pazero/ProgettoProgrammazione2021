#include "Bonus.hpp"

Bonus::Bonus(char name, position pos)
{
    this->name = name;
    this->pos = pos;
}

Bonus::bullet_bonus(position pos)
{
    name = '%';
}

Bonus::invincible_bonus(position pos)
{
    name = '*';
}

Bonus::rand_bonus() {
    srand(time(0));
    int rand = rand() % 2;
    
}

