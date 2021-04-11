#include "ClasseBigMap.hpp"
#include "Comandi.hpp"
using namespace std;

int main() {
    Comandi();

    int rect_lines = 19;
    int rect_cols = 100;
    BigMap infinita = BigMap(rect_lines, rect_cols);
    int ch;
    bool exit;
    while(!exit) {
        
        ch = getch();
        infinita.slideMap(ch);
        refresh();
        if(ch==KEY_F(1)) exit=true;
        timeout(50);
    }
    endwin();
    return 0;
}