
#include <ctime>
#include <iostream>

#include "ClasseBullet.hpp"
class Bonus{
    protected:
    //dichiaro i 4 tipi di bonus
    char name1;
    char name2;
    char name3;
    char name4;
    //altezza e larghezza della finestra, servono al metodo rand_pos_bonus
    int rect_lines;
    int rect_cols;

    public:
    Bonus();
    Bonus(int rect_lines, int rect_cols);
    char rand_name_bonus(); //metodo per ritornare un bonus random
    position rand_pos_bonus();  //metodo per randomizzare la posizione del bonus
};