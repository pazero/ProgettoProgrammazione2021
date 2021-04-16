#include <ncurses.h>
struct position{
    int y;
    int x;
};
class Oggetto{
    protected:
    position pos;
    char name;
    int life;

    public:
    Oggetto(position pos);
    Oggetto();
    position getPos();
    int getPosy();
    int getPosx();
    void show();
};