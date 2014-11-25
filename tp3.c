#include "tp3.h"


toutes_ludos* ensemble_ludos()
{
//CREATION D'UN ENSEMBLE DE LUDO QUI PERMET DE GERER PLUSIEURS LUDOS
    toutes_ludos* ludos = malloc(sizeof(t_ludotheque));
    if (ludos == NULL)
        return NULL;
    else
    {
        //INITIALISATION DE CHAQUE CASE DU TABLEAU A NULL
        int i;
        for (i=0; i<NBRE_MAX; i++)
            ludos->tab[i] = NULL;

        //NBRE DE LUDO INITIALISE A 0
        ludos->nb_ludos = 0;

        return ludos;
    }

}

t_ludotheque* creer_ludotheque()
{
    //Allocation de l'espace mémoire
    t_ludotheque* ludo = malloc(sizeof(t_ludotheque));
    if (ludo == NULL)
        return NULL;
    else
    {
        // INITIALISATION DE LA LUDOTHEQUE
        ludo->nb_jeu = 0;
        ludo->debut = NULL;
        return ludo;
    }
}

t_jeu* creer_jeu(char * nom,enum genre_jeu genre, int nbJoueurMin, int nbJoueurMax, int duree)
{
    //Allocation de l'espace mémoire
    t_jeu* j = malloc(sizeof(t_jeu));
    if (j == NULL)
        return NULL;
    else
    {
        //Initialisation des attributs du jeu
        j->nom = nom;
        j->genre = genre;
        j->nbJoueurMin = nbJoueurMin;
        j->nbJoueurMax = nbJoueurMax;
        j->duree = duree;
        j->suivant = NULL;
        return j;
    }
}



int ajouter_jeu(t_ludotheque *ludo, t_jeu *jeu) // return 1 si jeu ajouté, 0 si erreur
{

    t_jeu *x = ludo->debut; //on récupère le premier jeu
    t_jeu *j = creer_jeu(jeu->nom,jeu->genre, jeu->nbJoueurMin, jeu->nbJoueurMax, jeu->duree); //création d'une copie du jeu

// LUDO VIDE
    if (ludo->debut==NULL)
    {
        ludo->debut=j;
        j->suivant=NULL;
        ludo->nb_jeu++;
        return 1;
    }

//ON TESTE LE PREMIER ELEMENT DE LA LUDOTHEQUE
    if (ludo->debut==j->nom) //Le jeu est déjà dans la ludothèque
    {
        printf("Ce jeu est deja dans cette ludotheque\n");
        return 0;
    }

    if (strcasecmp(ludo->debut->nom,j->nom)>0) //Nécessaire au tri alphabétique
    {
        ludo->debut=j;
        j->suivant=x;
        ludo->nb_jeu++;
        return 1;
    }

//SINON, SE DEPLACER JUSQU'A LA PLACE
    while (x->suivant != NULL && strcasecmp(x->suivant->nom,j->nom)<0)
        x=x->suivant;

//PLACE A LA FIN
    if (x->suivant == NULL)
    {
        x->suivant=j;
        j->suivant= NULL;
        ludo->nb_jeu++;
        return 1;
    }

//JEU DEJA PRESENT : UTILE NOTAMMENT POUR LA FUSION
    else if (strcasecmp(x->suivant->nom,j->nom)==0)
    {
        printf("Ce jeu est deja dans cette ludotheque \n");
        return 0;
    }
// JEU NI DEBUT, NI FIN, NI PRESENT
    else // (strcasecmp(x->suivant->nom,j->nom)>0)
    {
        j->suivant= x->suivant;
        x->suivant=j;
        ludo->nb_jeu++;
        return 1;
    }
}


int ajouter_ludo(toutes_ludos *ludos, t_ludotheque *ludo) // return 1 si ludo ajouté, 0 si erreur
{
    int i =0;

// RECHERCHE D'UNE PLACE LIBRE DANS LE TABLEAU
    while (ludos->tab[i] != NULL && i!=NBRE_MAX)
        i++;

// PLACE LIBRE TROUVEE
    if (ludos->tab[i] == NULL)
    {
        ludos->tab[i]=ludo;
        ludos->nb_ludos++;
        printf("Ludotheque creee, il s'agit de la ludotheque numero %d \n", i+1);
        return i; // on retourne le numero de la place
    }

// TABLEAU REMPLI
    else
    {
        printf("Vous avez cree le nombre maximum autorise de ludotheques");
        return 0;
    }
}



void affiche_ludotheque(t_ludotheque* ludo)
{
    char * tabgenre[5] = {"PLATEAU", "RPG", "COOPERATIF", "AMBIANCE", "HASARD"};
    if (ludo->debut == NULL)
        printf("La ludotheque est vide.\n");
    else
    {
        //Création des colonnes avec une taille imposée, afin d'avoir un affichage esthétique
        printf ("%15s| %15s| %16s| %15s \n", "Nom", "Type", "Nbre de joueurs", "Duree moyenne");
        int i=0;
        t_jeu* j = ludo->debut;
        while (j != NULL)
        {
            //Affichage des jeux de la ludothèque
            printf ("%15s| %15s| %d-%d%13s| %15d \n", j->nom,tabgenre[j->genre], j->nbJoueurMin, j->nbJoueurMax, "", j->duree);
            i++;
            j = j->suivant;
        }
        printf("%15s| %d \n\n", "Total", i);
    }
}

//Renvoie le genre de jeu à partir de sa position dans l'énumération
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
    if (ludo->debut != NULL)
        supprimer_jeu(j); //Appel d'une fonction récursive
    free(ludo); //Une fois tous les jeux supprimés, on supprime la ludothèque
    printf("La ludotheque a bien ete supprimee\n");
}

void supprimer_jeu(t_jeu* j)
{
    if (j->suivant != NULL)  //tant que le jeu courant n'est pas le dernier de la ludothèque
        supprimer_jeu(j->suivant); //on appelle la fonction récursive sur le suivant
    free(j); //sinon, on supprime le jeu courant
}

int retirer_jeu(t_ludotheque* ludo, char*nom)
{
    //Ludothèque vide -> erreur
    if (ludo->debut == NULL)
    {
        printf("La ludotheque est vide, suppression impossible\n");
        return 0;
    }
    else if (ludo->nb_jeu == 1) //Un seul jeu dans la ludothèque
    {
        if (ludo->debut->nom == nom) //Le seul jeu est-il celui recherché ?
        {
            //Si oui, on le supprime
            ludo->debut->suivant = NULL;
            ludo->debut = NULL;
        }
        else printf("La ludotheque ne contient pas le jeu.\n"); //Sinon, erreur
        return 0;
    }
    else
    {
        t_jeu* j = ludo->debut;
        t_jeu* prec =j; //Conservation du jeu précédent
        while (j != NULL && j->nom != nom)
        {
            //Progression dans la liste
            prec = j;
            j = j->suivant;

        }
        if ( j==NULL) //A la fin, le jeu n'a pas été trouvé -> erreur
        {
            printf("La ludotheque ne contient pas le jeu.\n");
            return 0;
        }

        else //Jeu trouvé
        {
            if (prec == j) // Cas du premier jeu de la ludotheque
                (ludo->debut = j->suivant);
            else prec->suivant = j->suivant; //Cas des autres positions : chainage du jeu précédent et du jeu suivant
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
                //Les -1 permettent d'ignorer les paramètres
        {
            ajouter_jeu(suggestions, j);
        }
        j = j->suivant;
    }
    return suggestions;
}



t_ludotheque * fusion(t_ludotheque * ludo1, t_ludotheque * ludo2)
{
    t_ludotheque* l_fusion = creer_ludotheque(); //Ludotheque de résultat
    t_jeu* j = ludo1->debut;
    t_jeu* k = ludo2->debut;

//cas du premier

    while (j!=NULL) //Ajout des copies des jeux de la première ludothèque
    {
        t_jeu* x=creer_jeu(j->nom,j->genre, j->nbJoueurMin, j->nbJoueurMax, j->duree);
        ajouter_jeu(l_fusion, x); //Ajouter_jeu gère les doublons
        j=j->suivant;
    }


    while (k!=NULL) //Ajout des copies des jeux de la seconde ludothèque
    {
        t_jeu* x=creer_jeu(k->nom,k->genre, k->nbJoueurMin, k->nbJoueurMax, k->duree);
        ajouter_jeu(l_fusion, x);
        k=k->suivant;
    }
    return l_fusion;
}
