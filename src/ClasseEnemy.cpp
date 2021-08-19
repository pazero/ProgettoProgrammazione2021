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
void Enemy::update_pos(position pos) {
    this->pos = pos;
}

int Enemy::get_delay() {
    return delay;
}