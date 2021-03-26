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

    bool empty (int y, int x){
        return (mvinch(y,x) == ' ');
    }

    void build(){
        mvwaddstr(pad, 0, 0, name);
    }

  
    void Move(int Move){    
            if(Move == KEY_LEFT && empty(start.y,start.x-1)){
                mvprintw(start.y, start.x, " ");//cleen old
                start.x --;
                endx--;
            }
            if(Move == KEY_RIGHT && empty(start.y,start.x+1)){
                mvprintw(start.y, start.x, " ");//cleen old
                start.x ++;
                endx++;
            }            
    }

    position getPos(){
        return (start);
    }

    void addEnemy(position p, int n){
    
        for(int i=0;i<n;i++){
            Enemy *tmp = new Enemy;
            mvwaddstr(tmp->pad, 0, 0, name);
            tmp->start = p;
            tmp->endx = p.x;
            tmp->endy = p.y;
            tmp->next = next;
            next = tmp ;
            if(tmp->next == NULL){
                tmp->n=0;
            }else tmp->n =tmp->next->n + 1;
        }
    }




    void delEnemy(){  // da campbiare , prende in imput il numero del nodo, lo cerca e lo elimina 
        if (next !=NULL){
            Enemy *tmp = next;
            next = next->next;
            delete(tmp);
        }
    }

    void show(){
        Enemy *tmp = next;
         while(tmp->next !=NULL){

            prefresh(tmp->pad, tmp->pminrow, tmp->pmincol, tmp->start.y, tmp->start.x, tmp->endy, tmp->endx); 
            tmp = tmp->next;

         }
    }


};






int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);


    position p ;

    Enemy nemici = Enemy();
    nemici.build();
    
    int ch;
    bool flag=true;

    while(ch!=KEY_RIGHT) {
            mvprintw(0,0,"spingi il tasto destro per proseguire");
            timeout(500);
            ch = getch();

            p.y = rand() % 26 ;
            p.x = rand() % 110 ;
            nemici.addEnemy(p,1);

            

//      if (ch == KEY_F(1)) flag= false ;  

           // getch();    
    }
    clear();
    while(flag) {
        //timeout(500);
        ch = getch();
        nemici.show();
      if (ch == KEY_F(1)) flag= false ;          
    }

   
    
    endwin();
    return 0;
}


