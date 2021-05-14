#include <ncurses.h>
struct position{
    int y;
    int x;
};
class Oggetto{
    protected:
    position pos;
    char name;

    public:
    Oggetto(position pos);
    Oggetto();
    position getPos();
    int getPosy();
    int getPosx();
    void show();
    char get_name();
};