#include <string.h>
#include <iostream>
#include <ncurses.h>
using namespace std;

struct position{
    int x;
    int y;
};

class Eroe {
    protected:
    position pos;
    char name= 'S';
    int life;
    
    public:
    entity(position pos, int life ){
        this->pos = pos;
        this->life = life;
    }

    void Move(int Move, bool is_plat){
            if(Move == KEY_UP && is_plat){
                mvprintw(pos.y, pos.x, " ");//cleen old 
                pos.y -=2;
                show();
            }
            /*
            if(Move == KEY_DOWN && empty(pos.y+1,pos.x)){
                mvprintw(pos.y, pos.x, " ");//cleen old
                pos.y ++;
            }*/
    }

    position getPos(){
        return(pos);
    }

    void damage(int danno){
        this->life  = life - danno;
    }
    int getLife(){
        return(life);
    }
    void show(){
          mvprintw(pos.y, pos.x, "%c",name);
    }
};
