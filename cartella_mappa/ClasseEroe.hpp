#include <ncurses.h>
struct position{
    int y;
    int x;
};
class Eroe {
    protected:
    position pos;
    char name= 'S';
    int life;
    
    public:
    Eroe(position pos, int life);
    void Move(int Move, bool is_plat);
    position getPos();
    void show();
};
