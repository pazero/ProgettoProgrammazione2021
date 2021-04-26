
#include <ctime>
#include <iostream>

#include "ClasseBullet.hpp"
class Bonus{
    protected:
    char name1;
    char name2;
    int rect_lines;
    int rect_cols;


    public:
    Bonus();
    Bonus(int rect_lines, int rect_cols);
    char rand_name_bonus();
    position rand_pos_bonus();
};