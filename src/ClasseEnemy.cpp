#include "ClasseEnemy.hpp"

Enemy::Enemy(){
    this->pos = {0,0};
    delay = 0;
}

Enemy::Enemy(char name){
    //inizializzo la posizione e il tipo
    this->pos = {0,0};
    this->name = name;
    if(name == 'A') {
        //il delay cambia per ogni nemico A in modo che usino le corazze in momenti tutti diversi l'uno dall'altro
        delay = rand()%100;
    }
}
void Enemy::update_pos(position pos) {
    this->pos = pos;
}

int Enemy::get_delay() {
    return delay;
}