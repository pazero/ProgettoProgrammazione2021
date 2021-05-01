#include "Bonus.hpp"

Bonus::Bonus(){}

Bonus::Bonus(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    name1 = '#';
    name2 = '*';
}

char Bonus::rand_name_bonus()
{
    int choice;
    choice = rand() % 2;
    if (choice == 0)
        return name1;
    else
        return name2;
}

position Bonus::rand_pos_bonus(){
    position rand_pos;
    rand_pos.y = rand()%(rect_lines-3);
    rand_pos.x = rand()%(rect_cols);
    return rand_pos;
}