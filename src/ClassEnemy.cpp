#include "ClassEnemy.hpp"

Enemy::Enemy(){
    this->pos = {0,0};
    this->n=0;
}

Enemy::Enemy(int rect_lines, int rect_cols) {
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;

    this->pos = {0,0};
    //this->n=0;
}
void Enemy::update_pos(position pos) {
    this->pos = pos;
}

char Enemy::get_name(){
    return name;
}
position Enemy::getPos(){
    return (pos);
}
/*
bool Enemy::empty (int y, int x){ 
    Enemy *tmp = next;
    if(tmp!=NULL){
        while(tmp->next !=NULL){                 
            if(tmp->pos.x == x ){
                if(tmp->pos.y == y ){
                    return false;
                }
                            
            }
            if(mvinch(y,x) != ' ' ){
                return false;
            }
        tmp=tmp->next;
        }
    }
    return true;
}

void Enemy::Move(Enemy *tmp){   
    
        if((rand()%2) == 1){
            if(empty(tmp->pos.y,tmp->pos.x-1)){
                mvprintw(tmp->pos.y, tmp->pos.x," ");//cleen old
                tmp->pos.x --;
            }
        }
        else if(empty(tmp->pos.y,tmp->pos.x+1)){
            mvprintw(tmp->pos.y, tmp->pos.x," ");//cleen old
            tmp->pos.x ++;

        }
}



void Enemy::reposition(Enemy *tmp){ 
        while((mvinch(tmp->pos.y+1,tmp->pos.x) == ' ' )){
            mvprintw(tmp->pos.y, tmp->pos.x," ");
            tmp->pos.y ++;
        }   
}


void Enemy::show(Enemy *tmp){       
        mvprintw(tmp->pos.y,tmp->pos.x, "K");
}          

void Enemy::routine(int ch,Enemy nemici){
    Enemy *tmp = next;
    if(tmp!=NULL){
    while(tmp->next !=NULL){
        

            reposition(tmp);            
            
            Move(tmp);
            show(tmp);
        tmp= tmp->next;
    }
    }

}*/