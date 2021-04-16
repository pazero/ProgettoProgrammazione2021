#include "ClasseOggetto.hpp"
#include "ClasseWorldGen.hpp"

class Bonus : public Oggetto {
    public:
    Bonus(char name, position pos) {}

    void bullet_bonus();
    void invincible_bonus();
    void rand_bonus();
    void spawn_bonus();
}