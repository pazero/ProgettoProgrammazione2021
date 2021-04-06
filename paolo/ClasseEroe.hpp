#include <ncurses.h>
struct position{
    int y;
    int x;
};
class Eroe {
    protected:
    position pos;
    char name= 'Y';
    int life;
    
    public:
    Eroe(position pos, int life);
    void go_up();
    void go_down();
    int getPosy();
    int getPosx();
    void show();
};
