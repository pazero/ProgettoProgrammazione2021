#include "Map.hpp"

Map::Map(int rect_lines, int rect_cols, int n, bool first)
{
    this->first = first;

    iniziox_rect = (COLS - rect_cols) / 2;
    finex_rect = (COLS + rect_cols) / 2 - 1;
    inizioy_rect = (LINES - rect_lines) / 2;
    finey_rect = (LINES + rect_lines) / 2;
    pad_y = 0;
    this->n = n;

    if (first)
    {
        this->sx = iniziox_rect;
    }
    else
    {
        this->sx = finex_rect + 1;
    }
    this->ex = finex_rect;
    this->sy = inizioy_rect;
    this->ey = finey_rect;

    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;

    this->pad_x = 0;

    mappa = newpad(rect_lines, rect_cols);
    refresh();

    powerup = Bonus(rect_lines, rect_cols);
    nemici = NULL;
}

void Map::build()
{
    for (int i = 0; i < rect_cols; i++)
    {
        mvwaddch(mappa, 0, i, '=');
        mvwaddch(mappa, 1, i, '=');
        mvwaddch(mappa, rect_lines - 2, i, '=');
        mvwaddch(mappa, rect_lines - 1, i, '=');
    }
    if (first)
    {
        mvwaddstr(mappa, 0, 0, "          ");
        mvwaddstr(mappa, 1, 0, "          ");
        mvwaddstr(mappa, rect_lines - 2, 0, "          ");
        mvwaddstr(mappa, rect_lines - 1, 0, "          ");
        for (int i = 0; i < rect_lines; i++)
        {
            if (i % 2 == 0)
                mvwaddstr(mappa, i, 10, "|");
            else
            {
                mvwaddstr(mappa, i, 10, " ");
            }
        }
        char start[] = "S T A R T";
        int length = strlen(start);
        for (int i = 0; i < length; i++)
        {
            mvwaddch(mappa, (rect_lines - length) / 2 + i, 6, start[i]);
        }
    }
    mvwaddch(mappa, 0, rect_cols - 1, '|');
    mvwaddch(mappa, rect_lines - 1, rect_cols - 1, '|');
    if (!first)
    {
        rand_plat();
        spawn_bonus(1);
        if (n < 3)
            spawn_enemy(1);
        else
            spawn_enemy(n / 3 + 1);
    }
}
void Map::spawn_enemy(int n)
{
    position tmp_pos;
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        tmp_pos.y = rand() % (rect_lines - 3);
        tmp_pos.x = rand() % rect_cols;
        lista_nemici cattivo = new nemico;
        cattivo->bad.update_pos(tmp_pos);

        while (can_go_down(tmp_pos.y, tmp_pos.x) && tmp_pos.y < rect_lines - 3)
        {
            tmp_pos.y++;
        }
        mvwprintw(mappa, tmp_pos.y, tmp_pos.x, "%c", cattivo->bad.get_name());

        cattivo->next = nemici;
        nemici = cattivo;
        /*
        if(tmp->next == NULL){
            tmp->n=0;
        }
        else tmp->n =tmp->next->n + 1;
        */
    }
}

void Map::spawn_bonus(int n)
{
    char name;
    position tmp_pos;
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        name = powerup.rand_name_bonus();
        tmp_pos = powerup.rand_pos_bonus();
        while (can_go_down(tmp_pos.y, tmp_pos.x) && tmp_pos.y < rect_lines - 3)
        {
            tmp_pos.y++;
        }
        mvwprintw(mappa, tmp_pos.y, tmp_pos.x, "%c", name);
    }
}
void Map::add_plat(int type, int y, int x)
{
    if (type == 0)
    {
        mvwprintw(mappa, y - 12, x, "          ");
        mvwprintw(mappa, y - 10, x, " +++++++++");
        mvwprintw(mappa, y - 8, x, "++++++    ");
        mvwprintw(mappa, y - 6, x, "++++++++++");
        mvwprintw(mappa, y - 4, x, "       +++");
        mvwprintw(mappa, y - 2, x, "++++++++++");
        mvwprintw(mappa, y, x, "  ++++++++");
    }
    if (type == 1)
    {
        mvwprintw(mappa, y - 13, x, "   |     ");
        mvwprintw(mappa, y - 12, x, "++++++++++");
        mvwprintw(mappa, y - 10, x, "     +++++");
        mvwprintw(mappa, y - 8, x, "++++++    ");
        mvwprintw(mappa, y - 6, x, "  ++++++++");
        mvwprintw(mappa, y - 4, x, "++++++++++");
        mvwprintw(mappa, y - 3, x, "        | ");
        mvwprintw(mappa, y - 2, x, "  ++++++++");
        mvwprintw(mappa, y, x, "++++++++++");
    }
    if (type == 2)
    {
        mvwprintw(mappa, y - 12, x, "          ");
        mvwprintw(mappa, y - 10, x, "++++++++++");
        mvwprintw(mappa, y - 8, x, "+++++++   ");
        mvwprintw(mappa, y - 6, x, "  ++++++++");
        mvwprintw(mappa, y - 4, x, " +++++++++");
        mvwprintw(mappa, y - 2, x, "++++++++++");
        mvwprintw(mappa, y - 1, x, "|         ");
        mvwprintw(mappa, y, x, "++++++++  ");
    }
    if (type == 3)
    {
        mvwprintw(mappa, y - 12, x, " +++++++++");
        mvwprintw(mappa, y - 10, x, "          ");
        mvwprintw(mappa, y - 8, x, "+++++++++ ");
        mvwprintw(mappa, y - 6, x, "   +++++++");
        mvwprintw(mappa, y - 4, x, "++++++++++");
        mvwprintw(mappa, y - 2, x, " +++++++++");
        mvwprintw(mappa, y, x, "   +++++++");
        mvwprintw(mappa, y + 1, x, "       |   ");
    }
    if (type == 4)
    {
        mvwprintw(mappa, y - 12, x, "++++++++++");
        mvwprintw(mappa, y - 10, x, "+++++++   ");
        mvwprintw(mappa, y - 9, x, "|         ");
        mvwprintw(mappa, y - 8, x, "++++++++++");
        mvwprintw(mappa, y - 6, x, "          ");
        mvwprintw(mappa, y - 4, x, "++++++++++");
        mvwprintw(mappa, y - 2, x, "++++++++  ");
        mvwprintw(mappa, y, x, "          ");
    }
    if (type == 5)
    {
        mvwprintw(mappa, y - 12, x, "++++++++++");
        mvwprintw(mappa, y - 10, x, "++++++++++");
        mvwprintw(mappa, y - 8, x, "   +++++++");
        mvwprintw(mappa, y - 6, x, "++++++++++");
        mvwprintw(mappa, y - 5, x, "   |      ");
        mvwprintw(mappa, y - 4, x, "+++++     ");
        mvwprintw(mappa, y - 2, x, "++++++++++");
        mvwprintw(mappa, y, x, "    ++++++");
    }
    if (type == 6)
    {
        mvwprintw(mappa, y - 12, x, "++++++++++");
        mvwprintw(mappa, y - 11, x, "       |  ");
        mvwprintw(mappa, y - 10, x, "++++++++++");
        mvwprintw(mappa, y - 8, x, "          ");
        mvwprintw(mappa, y - 6, x, "+++++++   ");
        mvwprintw(mappa, y - 4, x, "     +++++");
        mvwprintw(mappa, y - 2, x, "++++++++++");
        mvwprintw(mappa, y - 1, x, "     |    ");
        mvwprintw(mappa, y, x, "+++++++++");
    }
}
void Map::rand_plat()
{
    int c;
    int stop = 0;
    srand(time(0));
    int length = 10;
    while (stop < rect_cols)
    {
        c = rand() % 7;
        add_plat(c, rect_lines - 4, stop);
        stop += length;
    }
}

void Map::rslide()
{
    if (first)
    {
        if (pad_x < (rect_cols - rect_cols))
        {
            pad_x += 1;
        }
        else
        {
            if (pad_x < rect_cols - 1)
            {
                pad_x += 1;
                ex -= 1;
            }
            else
            {
                if (ex == sx)
                {
                    ex -= 1;
                }
            }
        }
    }
    else
    {
        if (sx > iniziox_rect)
        {
            sx--;
        }
        else
        {
            if (ex > iniziox_rect - 1)
            {
                pad_x++;
                ex--;
            }
        }
    }
    prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
}
void Map::lslide()
{
    if (first)
    {
        if (ex < sx)
        {
            ex += 1;
        }
        else
        {
            if (ex < finex_rect)
            {
                pad_x -= 1;
                ex += 1;
            }
            else
            {
                if (pad_x > 0)
                {
                    pad_x -= 1;
                }
            }
        }
    }
    else
    {
        if (pad_x > 0)
        {
            ex++;
            pad_x--;
        }
        else
        {
            if (sx < finex_rect + 1)
            {
                sx++;
            }
        }
    }
    prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
}
bool Map::nx()
{
    if (ex < finex_rect)
        return true;
    else
        return false;
}
bool Map::previous()
{
    if (sx > iniziox_rect)
        return true;
    else
        return false;
}
void Map::show()
{
    prefresh(mappa, pad_y, pad_x, sy, sx, ey, ex);
}

int Map::how_much()
{
    return ex - sx;
}

bool Map::can_go_up(int y, int how_prev)
{
    return (mvwinch(mappa, y - 2, how_prev) != '|') && (mvwinch(mappa, y - 2, how_prev) != 'K') && (mvwinch(mappa, y - 1, how_prev) == '+');
}

bool Map::can_go_down(int y, int how_prev)
{
    if (mvwinch(mappa, y + 1, how_prev) == '+')
        return false;
    return true;
}

bool Map::can_pass_through(int y, int how_prev)
{
    return (mvwinch(mappa, y + 2, how_prev) != '|') && (mvwinch(mappa, y + 2, how_prev) != 'K') && ((mvwinch(mappa, y + 3, how_prev) == '+') || (mvwinch(mappa, y + 3, how_prev) == '='));
}
bool Map::there_is_this(char object, int y, int padx, bool dx, bool going_right)
{
    if (going_right)
    {
        if (dx)
            return (mvwinch(mappa, y, padx) == object) || (mvwinch(mappa, y, padx + 1) == object);
        else
            return (mvwinch(mappa, y, padx) == object) || (mvwinch(mappa, y, padx - 1) == object);
    }
    else
    {
        if (dx)
            return (mvwinch(mappa, y, padx + 1) == object);
        else
            return (mvwinch(mappa, y, padx - 1) == object);
    }
}

void Map::print_space(int y_on_pad, int x_on_pad)
{
    mvwprintw(mappa, y_on_pad, x_on_pad, " ");
}