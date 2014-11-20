#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"


void menu(void)
{
    t_ludotheque* l1, *l2, *lfus, *l, *sugg;
    t_jeu* newgame, *j1, *j2, *j3,* j4;
    char* nom;
    int genre, nbMin, nbMax, duree, nbJ, choix;
    l = NULL;

do{
    printf("---Menu---\n\n");
    printf("1. Creer une ludothèque\n");
    printf("2. Afficher une ludotheque\n");
    printf("3. Ajouter un jeu dans la ludotheque en saisissant ses caracteristiques\n");
    printf("4. Effectuer une recherche de jeu à partir de criteres saisis par l’utilisateur\n");
    printf("5. Creer 2 ludotheques, les afficher, les fusionner puis afficher la nouvelle ludotheque\n");
    printf("6. Quitter\n");

    scanf("%d", &choix);

    while(choix < 1 || choix > 6)
    {
        printf("Choix invalide.\n");
        scanf("%d", &choix);
    }

    switch(choix)
    {
    case 1:
        l = creer_ludotheque();
        printf("Ludotheque creee\n");
        break;

    case 2:
        if (l== NULL)
            printf("error, l n'existe pas\n");
        else
            affiche_ludotheque(l);
        break;
    case 3:
        if (l== NULL)

            printf("error, l n'existe pas\n");
        else
        {
            printf("Entrez le nom du jeu : ");
            scanf("%s", &nom);

            printf("Quel genre pour le jeu ?\n");
            printf("0- Plateau | 1- RPG | 2- Cooperatif | 3- Ambiance | 4- Hasard \n");
            scanf("%d", &genre);
            while(genre < 0 || genre > 6)
            {
                printf("Genre invalide.\n");
                scanf("%d", &genre);
            }

            printf("Nombre de joueurs min ? ");
            scanf("%d", &nbMin);
            while(nbMin < 0)
            {
                printf("Nombre invalide.\n");
                scanf("%d", &nbMin);
            }

            printf("Nombre de joueurs max ? ");
            scanf("%d", &nbMax);
            while(nbMax < nbMin)
            {
                printf("Nb joueurs max doit etre superieur a nb joueurs min\n");
                scanf("%d", &nbMax);
            }

            printf("Duree moyenne de jeu ? ");
            scanf("%d", &duree);
            while(duree < 0)
            {
                printf("Duree invalide\n");
                scanf("%d", &duree);
            }

            newgame = creer_jeu(nom, genre, nbMin, nbMax, duree);
            if (ajouter_jeu(l, newgame) == 1)
                printf("Jeu ajoute\n");
            else printf("Erreur d'ajout\n");
        }
        break;

    case 4:
        if (l== NULL)

            printf("error, l n'existe pas\n");
        else
        {

            printf("Recherche d'un jeu\nQuel genre pour le jeu ?\n");
            printf("0- Plateau | 1- RPG | 2- Cooperatif | 3- Ambiance | 4- Hasard | -1 pour ignorer \n");
            scanf("%d", &genre);
            while(genre < -1 || genre > 6)
            {
                printf("Genre invalide.\n");
                scanf("%d", &genre);
            }

            printf("Nombre de joueurs ? ");
            scanf("%d", &nbJ);
            while(nbJ < 0 && nbJ != -1)
            {
                printf("Nombre invalide.\n");
                scanf("%d", &nbJ);
            }

            printf("Duree moyenne de jeu ? ");
            scanf("%d", &duree);
            while(duree < 0 && duree != -1)
            {
                printf("Duree invalide");
                scanf("%d", &duree);
            }
            t_ludotheque* sugg = requete_jeu(l, genre, nbJ, duree);
            affiche_ludotheque(sugg);
        }
        break;

    case 5:
        l1 = creer_ludotheque();
        l2 = creer_ludotheque();
        j1 = creer_jeu("Times up", 3, 4, 8, 35);
        j2 = creer_jeu("Endor", 1, 3, 8, 90);
        j3 = creer_jeu("Monopoly", 1, 3, 8, 90);
        j4 = creer_jeu("Times up", 3, 4, 8, 35);
        ajouter_jeu(l1, j1);
        ajouter_jeu(l1, j2);
        ajouter_jeu(l2, j3);
        ajouter_jeu(l2, j4);
        printf("Ludotheque 1: \n");
        affiche_ludotheque(l1);
        printf("Ludotheque 2: \n");
        affiche_ludotheque(l2);

        printf("Fusion!\n");
        t_ludotheque* lfus = fusion(l1, l2);
        printf("Resultat de la fusion :\n");
        affiche_ludotheque(lfus);
        break;

    case 6:return;
        if (l1 != NULL)
            supprimer_ludotheque(l1);
        if (l2 != NULL)
            supprimer_ludotheque(l2);
        if (lfus != NULL)
            supprimer_ludotheque(lfus);
        if (l != NULL)
            supprimer_ludotheque(l);
        break;
    } //switch
    }while (choix !=6);

    return;


}



