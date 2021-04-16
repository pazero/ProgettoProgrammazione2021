#include "Motore.hpp"

// questa classe prende in input le dimensione della finestra e mette in moto 
// il gioco, ciclando ogni volta che riceve un input da tastiera, può farlo
// anche senza ogni 50 ms 
Motore::Motore(int rect_lines, int rect_cols)
{
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    this->infinita = WorldGen(rect_lines, rect_cols);
    go_game();
}

void Motore::move_all()
{
    infinita.update();

    if (ch == KEY_LEFT)
    {
        infinita.go_left();
    }
    if (ch == KEY_RIGHT)
    {
        infinita.go_right();
    }
    if (ch == KEY_UP)
    {
        infinita.go_up();
    }
    if (ch == 'e')
    {
        infinita.shoot();
    }
    infinita.routine_fineciclo();
    refresh();
}

void Motore::go_game()
{
    while (!pause)
    {
        ch = getch();
        move_all();
        if (ch == KEY_F(1))
            pause = true;
        timeout(50);
    }
    endwin();
}