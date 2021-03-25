#include <string.h>
#include <iostream>
#include <ncurses.h>
using namespace std;

struct position{
    int x;
    int y;
};

bool empty (int y, int x){
    return (mvinch(y,x) == ' ');
} 

class entity {
    protected:
    position pos;
    char name;
    int life;
    
    public:
    entity(position pos, char name, int life ){
        this->pos = pos;
        this->name = name;
        this->life = life;
    }

    void Move(int Move){
            if(Move == KEY_UP && empty(pos.y-1,pos.x)){
                mvprintw(pos.y, pos.x, " ");//cleen old 
                pos.y --;
            }
            if(Move == KEY_DOWN && empty(pos.y+1,pos.x)){
                mvprintw(pos.y, pos.x, " ");//cleen old
                pos.y ++;
            }
            if(Move == KEY_LEFT && empty(pos.y,pos.x-1)){
                mvprintw(pos.y, pos.x, " ");//cleen old
                pos.x --;
            }
            if(Move == KEY_RIGHT && empty(pos.y,pos.x+1)){
                mvprintw(pos.y, pos.x, " ");//cleen old
                pos.x ++;
            }            
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
    void show(){  // funzione non definitiva bisogna trovare una soluzione diversa
          mvprintw(pos.y, pos.x, "%c",name);
    }

      
};




class eroe: public entity {
public:
eroe(position pos, char name, int life ): entity(pos, name, life ){}

void colpito () {
    if(mvinch(pos.y,pos.x+1) == '-'){
        damage(2);
    }

}


};
class enemy:public entity{
public :
enemy(position pos, char name, int life ): entity(pos, name, life ){}

};
class bullet:public entity{

};
class bonus:public entity{

};




int main() {
    timeout(1);
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    

    int ch;
    bool flag=false;    
    int life;
    position p ;
    p.y = 20;
    p.x = 50;
    char S = 'S';
    char K = 'K';


        eroe om = eroe(p, S ,10);
            om.show();
        entity nemico = entity(p, K ,10);
            nemico.show();
            

    while(!flag) {
            timeout(150);
            ch = getch();
            // clear();
            
            om.Move(ch);
            om.show();

            p = om.getPos();
            life = om.getLife();
            mvprintw(0, 0, "%d",p.y);
            mvprintw(1,0 , "%d",p.x);
            mvprintw(2,0 , "%d",life);
         
        int a = rand() % 2 ;
        if(a==1){
            nemico.Move(KEY_LEFT);
        }else {
            nemico.Move(KEY_RIGHT);
        }
        nemico.show();
        om.colpito();

// rutine:
// aggiorno le posizioni dei nemici 
// aggiotno le posizioni dei proiettili 
// mostro tutti i nemici e i proiettili 
// controllo se qualcuno è stato colpito 
//
//problema: ho un numero N non conosciuto di entita da mostrare 
//          come le mostro tutte ? 


      if (ch == KEY_F(1)) flag= true ;      
    }

    
    endwin();
    return 0;
}
