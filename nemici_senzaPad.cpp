#include <string.h>
#include <iostream>
#include <ncurses.h>
using namespace std;

struct position{
    int x;
    int y;
};

class Enemy {
    protected: 
    position pos;
    int n;
    int life;
    const char *name = "K";
    Enemy *next;

    public:
    Enemy(position pos){
        
        this->pos = pos;

        this->n=0;
        next=NULL;
    }


    bool empty (int y, int x){ 
    
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

    void Move(Enemy *tmp){   
     
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

    position getPos(){
        return (pos);
    }

    void addEnemy(int n){ 
        position p;
        p.x=0;
        p.y=0;
        for(int i=0;i<n;i++){
                int j= rand()%30;
                int z= rand()%100;
            Enemy *tmp = new Enemy(p);

            tmp->pos.y = p.y+j;
            tmp->pos.x = p.x+z;
            tmp->next = next;
            next = tmp ;
            if(tmp->next == NULL){
                tmp->n=0;
            }else tmp->n =tmp->next->n + 1;
        }
    }

    void reposition(Enemy *tmp){ 
            while((mvinch(tmp->pos.y+1,tmp->pos.x) == ' ' )){
                mvprintw(tmp->pos.y, tmp->pos.x," ");
                tmp->pos.y ++;
            }   
    }
    

    void show(Enemy *tmp){       
                 mvprintw(tmp->pos.y,tmp->pos.x, "K");
    }          

    void rutine(int ch,Enemy nemici){
        Enemy *tmp = next;
        if(tmp!=NULL){
        while(tmp->next !=NULL){
            

                reposition(tmp);            
             
                Move(tmp);
                show(tmp);
            tmp= tmp->next;
        }
        }

    }

};

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    srand(time(0));
     mvprintw(0,0,   "premi il tasto UP");
     mvprintw(20,30,   "+++++++++++++++++++++++++++++");

    position p{0,0};
    Enemy nemici = Enemy(p) ;
    nemici.addEnemy(1);
     
    int ch;
    bool flag=true;
        while(flag) {
            timeout(500);
            ch = getch();
            if(ch==KEY_UP)nemici.addEnemy(2);
            nemici.rutine(ch,nemici);
            if (ch == KEY_F(1)) flag= false ;          
        }
    endwin();
    return 0;
}