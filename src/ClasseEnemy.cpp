#include "ClasseEnemy.hpp"

Enemy::Enemy(){
    this->pos = {0,0};
    delay = 0;
}

Enemy::Enemy(char name){
    this->pos = {0,0};
    this->name = name;
    if(name == 'A') {
        delay = rand()%100;
    }
}

/*Enemy::Enemy(int rect_lines, int rect_cols, char name) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;

    this->pos = {0,0};
    this->name = name;
    //this->n=0;
}*/
void Enemy::update_pos(position pos) {
    this->pos = pos;
}

position Enemy::getPos(){
    return (pos);
}

int Enemy::get_delay() {
    return delay;
}