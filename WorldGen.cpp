#include "WorldGen.hpp"

WorldGen::WorldGen() {}
WorldGen::WorldGen(int rect_lines, int rect_cols)
{
    this->rect_lines = rect_lines;
    this->rect_cols = rect_cols;
    nodi = 1;
    count_bullet = 3;
    stacco = 30;

    head->piece = new Map(rect_lines, rect_cols, nodi, true);
    head->piece->build();
    head->piece->show();
    head->n = 1;
    head->next = NULL;
    head->prev = NULL;

    position pos = {(LINES + rect_lines) / 2 - 3, (COLS - rect_cols) / 2 + stacco};
    this->life = 100;
    Mario = Eroe(pos, life);
    Mario.show();
    gun = NULL;
}
void WorldGen::addMap()
{
    nodi++;
    MapList aux = head;
    MapList prec = NULL;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    prec = aux;
    aux->next = new MapNode;
    aux->next->piece = new Map(rect_lines, rect_cols, nodi);
    aux->next->piece->build();

    aux->next->n = nodi;
    aux->next->next = NULL;
    aux->next->prev = prec;

    prec = NULL;
    delete (prec);
    //mvprintw(LINES/2 +1,0,"Aggiunta nodo numero: %d", nodi);
}
void WorldGen::update()
{
    count_bullet++;
    if (head->next == NULL)
    {
        addMap();
    }
    if (head->piece->how_much() < head->next->piece->how_much())
    {
        head = head->next;
    }
    if (head->prev != NULL)
    {
        if (head->piece->how_much() < head->prev->piece->how_much())
        {
            head = head->prev;
        }
    }
    mvprintw(LINES / 2, 0, "Current node: %d  ", head->n);
    Mario.show();
}
void WorldGen::go_left()
{
    if (not_this('|', false, Mario.getPos(), false) && not_this('K', false, Mario.getPos(), false))
    {
        head->piece->lslide();
        if (head->next != NULL)
        {
            head->next->piece->lslide();
        }
        if (head->prev != NULL)
        {
            if (head->piece->previous())
                head->prev->piece->lslide();
        }
        while (Mario.getPosy() < (LINES + rect_lines) / 2 - 3 && free_down(Mario.getPosy() - (LINES - rect_lines) / 2))
            Mario.go_down();

        update_shoot(Mario.getPosx(), rect_cols + (COLS - rect_cols) / 2 - 1, false);
    }
}

void WorldGen::go_right()
{
    if (not_this('|', true, Mario.getPos(), false) && not_this('K', true, Mario.getPos(), false))
    {
        head->piece->rslide();
        if (head->next != NULL)
        {
            if (head->piece->nx())
                head->next->piece->rslide();
        }
        if (head->prev != NULL)
            head->prev->piece->rslide();

        while (Mario.getPosy() < (LINES + rect_lines) / 2 - 3 && free_down(Mario.getPosy() - (LINES - rect_lines) / 2))
        {
            Mario.go_down();
        }
    }
}

void WorldGen::go_up()
{
    int y_on_pad = Mario.getPosy() - (LINES - rect_lines) / 2;
    if (head->prev != NULL)
    {
        if (head->prev->piece->how_much() > stacco)
        {
            if (head->prev->piece->can_go_up(y_on_pad, stacco + rect_cols - head->prev->piece->how_much() - 1))
            {
                Mario.go_up();
            }
        }
        else
        {
            if (head->prev->piece->how_much() > -1)
            {
                if (head->piece->can_go_up(y_on_pad, head->piece->how_much() - rect_cols + stacco + 1))
                {
                    Mario.go_up();
                }
            }
            else
            {
                if (head->piece->can_go_up(y_on_pad, rect_cols - head->piece->how_much() + stacco - 1))
                {
                    Mario.go_up();
                }
            }
        }
    }
}

void WorldGen::go_down()
{
    int y_on_pad = Mario.getPosy() - (LINES - rect_lines) / 2;
    if (head->prev != NULL)
    {
        if (head->prev->piece->how_much() > stacco)
        {
            if (head->prev->piece->can_pass_through(y_on_pad, stacco + rect_cols - head->prev->piece->how_much() - 1))
            {
                Mario.go_down();
            }
        }
        else
        {
            if (head->prev->piece->how_much() > -1)
            {
                if (head->piece->can_pass_through(y_on_pad, head->piece->how_much() - rect_cols + stacco + 1))
                {
                    Mario.go_down();
                }
            }
            else
            {
                if (head->piece->can_pass_through(y_on_pad, rect_cols - head->piece->how_much() + stacco - 1))
                {
                    Mario.go_down();
                }
            }
        }
    }
}
void WorldGen::shoot()
{
    if (count_bullet / 3 > 0)
    {
        add_bullet(Mario.getPos());
        count_bullet = 0;
    }
}
void WorldGen::get_bonus()
{
    position tmp = {Mario.getPosy(), Mario.getPosx() - 1};
    if (!not_this('#', true, tmp, false) || !not_this('*', true, tmp, false))
    {
        int y_on_pad = Mario.getPosy() - (LINES - rect_lines) / 2;
        if (head->prev != NULL)
        {
            if (head->prev->piece->how_much() > stacco)
                head->prev->piece->print_space(y_on_pad, stacco + rect_cols - head->prev->piece->how_much() - 1);
            else
            {
                if (head->prev->piece->how_much() > -1)
                {
                    head->piece->print_space(y_on_pad, head->piece->how_much() - rect_cols + stacco + 1);
                }
                else
                {
                    head->piece->print_space(y_on_pad, rect_cols - head->piece->how_much() + stacco - 1);
                }
            }
        }
    }
}

bool WorldGen::free_down(int y_on_pad)
{
    if (head->prev != NULL)
    {
        if (head->prev->piece->how_much() >= stacco)
            return head->prev->piece->can_go_down(y_on_pad, stacco + rect_cols - head->prev->piece->how_much() - 1);
        else
        {
            if (head->prev->piece->how_much() > -1)
            {
                return head->piece->can_go_down(y_on_pad, head->piece->how_much() - rect_cols + stacco + 1);
            }
            else
            {
                return head->piece->can_go_down(y_on_pad, rect_cols - head->piece->how_much() + stacco - 1);
            }
        }
    }
}

void WorldGen::add_bullet(position pos)
{
    colpi tmp = new colpo;
    tmp->curr = Bullet(pos);
    tmp->next = gun;
    gun = tmp;
}

void WorldGen::update_shoot(int limit_sx, int limit_dx, bool going_right)
{
    colpi aux = gun;
    colpi prec = NULL;
    while (aux != NULL)
    {
        Mario.show();
        if (aux->curr.getPosx() == limit_sx)
        {
            if (not_this('|', true, aux->curr.getPos(), going_right))
            {
                aux->curr.go_dx();
            }
            else
            {
                //aggiungere verifica di COSA colpisce
                colpi tmp;
                if (prec == NULL)
                {
                    tmp = aux;
                    aux = aux->next;
                    delete (tmp);
                    tmp = NULL;
                    gun = aux;
                }
                else
                {
                    tmp = aux;
                    aux = aux->next;
                    prec->next = aux;
                    delete (tmp);
                    tmp = NULL;
                }
            }
        }
        else
        {
            if (aux->curr.getPosx() < limit_dx - 1)
            {
                aux->curr.destroy_win();
                if (not_this('|', true, aux->curr.getPos(), going_right))
                {
                    aux->curr.go_dx();
                }
                else
                {
                    //aggiungere verifica di COSA colpisce
                    colpi tmp;
                    if (prec == NULL)
                    {
                        tmp = aux;
                        aux = aux->next;
                        delete (tmp);
                        tmp = NULL;
                        gun = aux;
                    }
                    else
                    {
                        tmp = aux;
                        aux = aux->next;
                        prec->next = aux;
                        delete (tmp);
                        tmp = NULL;
                    }
                }
            }
            // caso aux->curr.getPosx()==limit_dx
            else
            {
                aux->curr.destroy_win();
                colpi tmp;
                if (prec == NULL)
                {
                    tmp = aux;
                    aux = aux->next;
                    delete (tmp);
                    tmp = NULL;
                    gun = aux;
                }
                else
                {
                    tmp = aux;
                    aux = aux->next;
                    prec->next = aux;
                    delete (tmp);
                    tmp = NULL;
                }
            }
        }
        prec = aux;
        if (aux != NULL)
            aux = aux->next;
    }
}

bool WorldGen::not_this(char object, bool dx, position pos, bool going_right)
{
    int y_on_pad = pos.y - (LINES - rect_lines) / 2;
    int x_on_rect = pos.x - (COLS - rect_cols) / 2;

    if (head->prev != NULL)
    {
        if (head->prev->piece->how_much() > x_on_rect)
            return !(head->prev->piece->there_is_this(object, y_on_pad, x_on_rect + rect_cols - head->prev->piece->how_much() - 1, dx, going_right));
        else
        {
            if (head->prev->piece->how_much() > -1)
            {
                return !(head->piece->there_is_this(object, y_on_pad, head->piece->how_much() - rect_cols + x_on_rect + 1, dx, going_right));
            }
            else
            {
                if (x_on_rect >= head->piece->how_much())
                    return !(head->next->piece->there_is_this(object, y_on_pad, x_on_rect - head->piece->how_much() - 1, dx, going_right));
                else
                    return !(head->piece->there_is_this(object, y_on_pad, rect_cols - head->piece->how_much() + x_on_rect - 1, dx, going_right));
            }
        }
    }
    else
    {
        if (x_on_rect >= head->piece->how_much())
            return !(head->next->piece->there_is_this(object, y_on_pad, x_on_rect - head->piece->how_much() - 1, dx, going_right));
        else
            //return head->piece->there_is_this(object, y_on_pad,rect_cols - head->piece->how_much() + x_on_rect-1, dx, going_right);
            return true;
    }
}

void WorldGen::routine_fineciclo(bool right)
{
    //Mario.show();
    reshow_map();
    update_shoot(Mario.getPosx(), rect_cols + (COLS - rect_cols) / 2 - 1, right);
    Mario.show();
}
void WorldGen::reshow_map()
{
    if (head->prev != NULL && head->prev->piece->how_much() > -1)
    {
        head->prev->piece->show();
    }
    head->piece->show();
    if (head->next != NULL && head->next->piece->how_much() > -1)
    {
        head->next->piece->show();
    }
}

int WorldGen::n_map()
{
    return nodi;
}

bool WorldGen::is_bonus()
{
    position tmp = {Mario.getPosy(), Mario.getPosx() - 1};
    if (!not_this('#', true, tmp, false))
    {
        //mvprintw(0, 10, "bonus #");
        get_bonus();
        Mario.show();
        return true;
    }
    if (!not_this('*', true, tmp, false))
    {
        //mvprintw(1, 10, "bonus *");
        get_bonus();
        Mario.show();
        get_life(life);
        mvprintw(13, 0, "Life: %d", life);
        return false;
    }
    //mvprintw(13, 0, "          ", life);
}
int WorldGen::damage(int life)
{
    this->life = life - 20;
    return life;
}
int WorldGen::get_life(int life)
{
    this->life = life + 50;
    return life;
    
}
bool WorldGen::hit_enemy()
{
    if (is_enemy() && life > 0)
    {
        damage(life);
        if (life <= 0) {
            return false;
        }
        mvprintw(13, 0, "Life: %d", life);
        return true;
    }
}
bool WorldGen::is_enemy()
{
    if (!not_this('K', true, Mario.getPos(), false) || !not_this('K', false, Mario.getPos(), false))
    return true;
}