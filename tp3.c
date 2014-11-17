#include "tp3.h"

t_ludotheque* creer_ludotheque()
{
    t_ludotheque* ludo = malloc(sizeof(t_ludotheque));
    if (ludo == NULL)
        return NULL;
    else
    {
        ludo->nb_jeu = 0;
        ludo->debut = NULL;
        return ludo;
    }
}

t_jeu* creer_jeu(char * nom,enum genre_jeu genre, int nbJoueurMin, int nbJoueurMax, int duree)
{
    t_jeu* j = malloc(sizeof(t_jeu));
    if (j == NULL)
        return NULL;
    else
    {
        j->nom = nom;
        j->genre = genre;
        j->nbJoueurMin = nbJoueurMin;
        j->nbJoueurMax = nbJoueurMax;
        j->duree = duree;
        j->suivant = NULL;
        return j;
    }
}

int ajouter_jeu(t_ludotheque *ludo, t_jeu *j)
{
    t_jeu *x = ludo->debut;
    if (ludo->nb_jeu == 0)
    {
        ludo->debut=j;
        ludo->nb_jeu = 1;
    }
    else if (strcmp(j->nom, x->nom) <= 0)
    {
        j->suivant = ludo->debut;
        ludo->debut = j;
    }
    else
    {
        while (x->suivant != NULL && strcmp(j->nom, x->suivant->nom) != 0)
        {
            x = x->suivant;
        }
        j->suivant = x->suivant;
        x->suivant = j;
    }
    return 1;
}

void affiche_ludotheque(t_ludotheque* ludo)
{
    if (ludo->debut == NULL)
        printf("La ludotheque est vide.\n");
    else
    {
        printf ("%15s| %15s| %16s| %15s \n", "Nom", "Type", "Nbre de joueurs", "Duree moyenne");
        int i=0;
        t_jeu* j = ludo->debut;
        while (j != NULL)
        {
            printf ("%15s| %15s| %d-%d%13s| %15d \n", j->nom, enumtostring(j->genre), j->nbJoueurMin, j->nbJoueurMax, "", j->duree);
            i++;
            j = j->suivant;
        }
        printf("%15s| %d", "Total", i);
    }
}

const char* enumtostring(enum genre_jeu type)
{
    switch (type)
    {
        case PLATEAU: return "Plateau"; break;
        case RPG: return "RPG"; break;
        case COOPERATIF: return "Cooperatif"; break;
        case AMBIANCE: return "Ambiance"; break;
        case HASARD: return "Hasard"; break;
    }
}

void supprimer_ludotheque(t_ludotheque* ludo){
    t_jeu* j = ludo->debut;
    supprimer_jeu(j);
    free(ludo);
}

void supprimer_jeu(t_jeu* j){
    if (j->suivant == NULL){ //le jeu est le dernier de la ludoth�que
        free(j);
    }
    else { //il y a encore d'autres jeux � supprimer
        supprimer_jeu(j->suivant);
        free(j);
    }
}

t_ludotheque* requete_jeu(t_ludotheque* ludo, enum genre_jeu genre, int nbJoueurs, int duree){
    t_ludotheque* suggestions = creer_ludotheque();
    t_jeu* j = ludo->debut;
    while (j != NULL){
        if (j->genre == genre &&
            j->nbJoueurMin <= nbJoueurs &&
            j->nbJoueurMax >= nbJoueurs &&
            j->duree >= 0.9*duree &&
            j->duree <= 1.1*duree){
                ajouter_jeu(suggestions, j);
            }
        j = j->suivant;
    }
    return suggestions;
}