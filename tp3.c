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

/**Ancienne version de ajouter_jeu, avant les modifs liées à la fusion

int ajouter_jeu(t_ludotheque *ludo, t_jeu *j)
{
    t_jeu *x = ludo->debut;
    if (ludo->nb_jeu == 0)
    {
        ludo->debut=j;
        ludo->nb_jeu = 1;
    }
    else
    {
        if (strcmp(j->nom, x->nom) <= 0) //ajout dans l'ordre alphabétique
        {
            j->suivant = ludo->debut;
            ludo->debut = j;
        }
        else
        {
            while (x->suivant != NULL && strcmp(j->nom, x->nom) > 0)
            {
                x = x->suivant;
            }
            j->suivant = x->suivant;
            x->suivant = j;
        }
        ludo->nb_jeu++;
    }
    return 1;
}
*/
int ajouter_jeu(t_ludotheque *ludo, t_jeu *jeu) //A REPRENDRE
{
    t_jeu *x = ludo->debut;
    t_jeu* j = creer_jeu(jeu->nom,jeu->genre, jeu->nbJoueurMin, jeu->nbJoueurMax, jeu->duree);

    if (ludo->nb_jeu == 0)
    {
        ludo->debut=j;
        ludo->nb_jeu = 1;
    }
    else
    {

        if (strcasecmp(j->nom, x->nom) < 0) //ajout dans l'ordre alphabétique
        {
            j->suivant = ludo->debut;
            ludo->debut = j;
        }
        else
        {


            while ((x->suivant != NULL) && (strcasecmp(j->nom, x->nom) >= 0))
                x = x->suivant;

            //if (strcasecmp(j->nom, x->nom) == 0) // Meme jeu
            //    printf("Il y a deja un jeu portant ce nom dans cette ludotheque. Il est impossible de l'ajouter. \n");
            // else
            //  {

            if (x->suivant == NULL)
            {
                x->suivant= j;
                j->suivant =NULL;
            }
            else
            {
                j->suivant = x->suivant;
                x->suivant = j;
            }
            //}
        }
        ludo->nb_jeu++;
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
        printf("%15s| %d \n\n", "Total", i);
    }
}

const char* enumtostring(enum genre_jeu type)
{
    switch (type)
    {
    case PLATEAU:
            return "Plateau";
        break;
    case RPG:
        return "RPG";
        break;
    case COOPERATIF:
        return "Cooperatif";
        break;
    case AMBIANCE:
        return "Ambiance";
        break;
    case HASARD:
        return "Hasard";
        break;
    }
}

void supprimer_ludotheque(t_ludotheque* ludo)
{
    t_jeu* j = ludo->debut;
    supprimer_jeu(j);
    free(ludo);
    printf("La ludotheque a bien ete supprimee\n");

}

void supprimer_jeu(t_jeu* j)
{
    if (j->suivant == NULL)  //le jeu est le dernier de la ludothèque
    {
        free(j);
    }
    else   //il y a encore d'autres jeux à supprimer
    {
        supprimer_jeu(j->suivant);
        free(j);
    }
}

int retirer_jeu(t_ludotheque* ludo, char*nom)
{
    if (ludo->debut == NULL)
    {
        printf("La ludotheque est vide, suppression impossible\n");
        return 0;
    }
    else if (ludo->nb_jeu == 1)
    {
        if (ludo->debut->nom == nom)
        {
            ludo->debut->suivant == NULL;
            ludo->debut == NULL;
        }
        else printf("La ludotheque ne contient pas le jeu.\n");
        return 0;
    }
    else
    {
        t_jeu* j = ludo->debut;
        t_jeu* prec =j;
        while (j != NULL && j->nom != nom)
        {
            prec = j;
            j = j->suivant;

        }
        if ( j==NULL)
        {
            printf("La ludotheque ne contient pas le jeu.\n");
            return 0;
        }

        else //(j->nom == nom)
        {
            if (prec == j) // Cas du premier de la liste
                (ludo->debut = j->suivant);
            else prec->suivant = j->suivant;
            //j->suivant= NULL;

            printf("%s : suppression reussie\n", nom);
            return 1;
        }

    }
}

t_ludotheque* requete_jeu(t_ludotheque* ludo, enum genre_jeu genre, int nbJoueurs, int duree)
{
    t_ludotheque* suggestions = creer_ludotheque();
    t_jeu* j = ludo->debut;
    while (j != NULL)
    {
        if ((j->genre == genre || genre == -1) &&
                ((j->nbJoueurMin <= nbJoueurs && j->nbJoueurMax >= nbJoueurs) || nbJoueurs == -1) &&
                ((j->duree >= 0.9*duree && j->duree <= 1.1*duree) || duree == -1))
        {
            ajouter_jeu(suggestions, j);
        }
        j = j->suivant;
    }
    return suggestions;
}



t_ludotheque * fusion(t_ludotheque * ludo1, t_ludotheque * ludo2)
{
    t_ludotheque* l_fusion = creer_ludotheque();
    t_jeu* j = ludo1->debut;
    t_jeu* k = ludo2->debut;

//cas du premier

    while (j!=NULL)
    {
        t_jeu* x=creer_jeu(j->nom,j->genre, j->nbJoueurMin, j->nbJoueurMax, j->duree);
        ajouter_jeu(l_fusion, x);
        j=j->suivant;
    }


    while (k!=NULL)
    {
        t_jeu* x=creer_jeu(k->nom,k->genre, k->nbJoueurMin, k->nbJoueurMax, k->duree);
        ajouter_jeu(l_fusion, x);
        k=k->suivant;
    }
    return l_fusion;
}
