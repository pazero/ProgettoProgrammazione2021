#include "ClasseBonus.hpp"

Bonus::Bonus(){}

Bonus::Bonus(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    name1 = '#';
    name2 = '*';
    name3 = '$';
    name4 = '&';
}
//ritorna un nome random fra # * $ &
char Bonus::rand_name_bonus() {
    int choice;
    choice = rand()%17;
    if(choice == 0) return name2;
    if(choice>0 && choice<5) return name1;
    if(choice >=5 && choice<8) return name3;
    if(choice >= 8 && choice<11) return name4;
    else return ' ';
}
//prende una posizione random all'interno della finestra di gioco 
position Bonus::rand_pos_bonus(){
    position rand_pos;
    rand_pos.y = rand()%(rect_lines-3);
    rand_pos.x = rand()%(rect_cols);
    return rand_pos;
}