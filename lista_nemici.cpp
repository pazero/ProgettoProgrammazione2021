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
    WINDOW *pad;
    int plines;
    int pcols;
    int pminrow;
    int pmincol;
    position start;
    int endy;
    int endx;
    int n;
    int life;
    const char *name = "K";
    Enemy *next;

    public:
    Enemy(int plines=1, int pcols=1,int sx=0,int sy=0, int pminrow = 0, int pmincol= 0){
        
        this->start.y = sy;
        this->start.x = sx;

        this->endy = sy + 1;
        this->endx = sx + 1;

        this->pminrow = pminrow;
        this->pmincol = pmincol;

        this->plines = plines;
        this->pcols = pcols;
        pad = newpad(plines,pcols);
        refresh();
        this->n=0;
        next=NULL;
    }
    void build(){
        mvwaddstr(pad, 0, 0, name);
    }

    bool empty (int y, int x){ //------------------da rifare tutto 
        bool h=true,j=true,k=true,p;
        Enemy *tmp = next;
        if(tmp!=NULL){
        while(tmp->next !=NULL){
            j = (mvinch(y,x) == ' ' );     
           if(true && tmp->start.x != x && tmp->start.y != y){
               mvprintw(10,30,   "entrato");
              p=3;
           }
           if(p==3 && tmp->start.x != x && tmp->start.y != y){
               mvprintw(11,30,   "entrato di nuovo");
           }
            tmp=tmp->next;
            k= ( h && j);
            h = k;
        }
        }
        return k ;
    }

    void Move(Enemy *tmp){   
     
            if((rand()%2) == 1 && empty(tmp->start.y,tmp->start.x-1)){
                mvprintw(tmp->start.y, tmp->start.x, " ");//cleen old
                tmp->start.x --;
                tmp->endx--;
            }
            else if(empty(tmp->start.y,tmp->start.x+1)){
                mvprintw(tmp->start.y, tmp->start.x, " ");//cleen old
                tmp->start.x ++;
                tmp->endx++;
            }
    }

    position getPos(){
        return (start);
    }

    void addEnemy(int n){ 
        position p;
        p.x=0;
        p.y=0;
        for(int i=0;i<n;i++){
                int j= rand()%30;
                int z= rand()%100;
            Enemy *tmp = new Enemy;
            mvwaddstr(tmp->pad, 0, 0, name);
            tmp->start.y = p.y+j;
            tmp->start.x = p.x+z;
            tmp->endx = p.x+z;
            tmp->endy = p.y+j;
            tmp->next = next;
            next = tmp ;
            if(tmp->next == NULL){
                tmp->n=0;
            }else tmp->n =tmp->next->n + 1;
        }
    }

    void reposition(Enemy *tmp){ 
            while(empty(tmp->start.y+1,tmp->start.x)){
                tmp->start.y ++;
                tmp->endy ++;
            }   
    }
    
    void delEnemy(Enemy *tmp){

            delete(tmp);
        
    }

    void show(Enemy *tmp){       
                prefresh(tmp->pad, tmp->pminrow, tmp->pmincol, tmp->start.y, tmp->start.x, tmp->endy, tmp->endx); 
    }          

    void rutine(int ch,Enemy nemici){
        Enemy *tmp = next;
        if(tmp!=NULL){
        while(tmp->next !=NULL){
            
                //nemici.show(tmp);
                reposition(tmp);
                //nemici.show();            
            //    Move(tmp);
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
     mvprintw(20,30,   "++++++++++++++++++++++++++++++++++");


    Enemy nemici = Enemy();
    nemici.build();
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


