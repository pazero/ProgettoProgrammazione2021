#include "ClasseEroe.hpp"
#include "ClasseBigMap.hpp"
#include "Comandi.hpp"
using namespace std;

int main() {
    
    Comandi();

    int rect_lines = 19;
    int rect_cols = 100;
    position p {(LINES+rect_lines)/2 -3, (COLS-rect_cols)/2 +30};
    int y_pad = rect_lines -3;
    
    BigMap infinita = BigMap(rect_lines, rect_cols);
    mvprintw(p.y, p.x,"Y");  
    int ch;
    bool exit;
    while(!exit) {
        ch = getch();
        if(!infinita.slideMap(ch)) exit = true;
        mvprintw(p.y, p.x,"Y");
        refresh();   
        if(ch == KEY_UP) {
            if(infinita.is_platform(y_pad,30)) {
                mvprintw(0,0,"ok");
                mvprintw(p.y, p.x," ");
                p.y-=2;
                y_pad -=2;
                mvprintw(p.y, p.x,"Y");
                refresh();
            }
        }
        timeout(50);
    }
    endwin();
    return 0;
}
