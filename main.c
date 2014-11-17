#include "tp3.h"

int main()
{
    t_ludotheque* l = creer_ludotheque();
    //affiche_ludotheque(l);
    t_jeu* j1 = creer_jeu("Times up", 3, 4, 8, 35);
    t_jeu* j2 = creer_jeu("Endor", 1, 3, 8, 90);
    ajouter_jeu(l, j2);
    ajouter_jeu(l, j1);
    //l->debut = j1;
    affiche_ludotheque(l);
    return 0;
}

