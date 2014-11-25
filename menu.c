#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"


void menu(toutes_ludos *ludotheques)
{

    /** VARIABLES A REVOIR (supprimer lorsque inutile)*/
    t_ludotheque* l1, *l2 , *lfus , *l, *sugg;
    l1=NULL;
    l2=NULL;
    lfus=NULL;
    l=NULL;
    sugg=NULL;

    t_jeu* newgame, *j1, *j2, *j3,* j4, *j5;
    char nom[30];
    int genre, nbMin, nbMax, duree, nbJ, choix, n_ludo, i;


// AFFICHAGE DU MENU
    do
    {
        printf("---Menu---\n\n");
        printf("Quelle action voulez-vous faire ?\n\n");
        printf("1. Creer une ludotheque (%d/%d) \n", ludotheques->nb_ludos,NBRE_MAX);
        printf("2. Afficher une ludotheque\n");
        printf("3. Ajouter un jeu dans la ludotheque en saisissant ses caracteristiques\n");
        printf("4. Effectuer une recherche de jeu a partir de criteres saisis par l'utilisateur\n");
        printf("5. Creer 2 ludotheques, les afficher, les fusionner puis afficher la nouvelle ludotheque\n");
        printf("6. Quitter\n");

//CHOIX
        scanf("%d", &choix);

//TEST DES ERREURS POSSIBLES
        while(choix < 1 || choix > 6)
        {
            printf("Choix invalide.\n");
            scanf("%d", &choix);
        }


        /** ACTIONS SELON CHOIX*/
        switch(choix)
        {
// CREATION D'UNE LUDOTHEQUE
        case 1:
            l = creer_ludotheque();
            ajouter_ludo(ludotheques, l);
            break;

// AFFICHAGE D'UNE LUDOTHEQUE QUE L'ON CHOISIT
        case 2:
            if (ludotheques->nb_ludos ==0) //Aucune ludotheque initialisée
                printf("Il n'y a aucune ludotheque a afficher. Veuillez en creer une auparavant.\n");
            else
            {
                printf("Quelle ludotheque voulez-vous afficher ?\n");
                int i;

                // AFFICHAGE DES NUMEROS DES LUDOS DEJA CREES
                printf("Ludotheques precedemment crees : ");
                for (i=0; i< NBRE_MAX; i++)
                    if (ludotheques->tab[i]!=NULL)
                        printf("%d ", i+1);
                printf("\n");

                // CHOIX DE LA LUDO
                scanf("%d",&n_ludo);

                // TEST DES ERREURS POSSIBLES : ludothèque hors limites ou non-initialisée
                while(choix < 1 || n_ludo > NBRE_MAX || ludotheques->tab[n_ludo-1]== NULL)
                {
                    printf("Choix invalide, cette ludotheque n'existe pas.\n");
                    scanf("%d", &n_ludo);
                }
                //Affichage de la ludothèque choisie
                affiche_ludotheque(ludotheques->tab[n_ludo-1]);
            }
            break;

        case 3: //Ajout d'une jeu personnalisé
            if (ludotheques->nb_ludos ==0) //Aucune ludothèque initialisée
                printf("Il n'y a aucune ludotheque. Veuillez en creer une auparavant.\n");
            else
            {
                printf("Dans quelle ludotheque voulez-vous ajouter un jeu ?\n");
                int i;

                // AFFICHAGE DES NUMEROS DES LUDOS DEJA CREES
                printf("Ludotheques precedemment crees : ");
                for (i=0; i< NBRE_MAX; i++)
                    if (ludotheques->tab[i]!=NULL)
                        printf("%d ", i+1);
                printf("\n");

                // CHOIX DE LA LUDO
                scanf("%d",&n_ludo);

                // TEST DES ERREURS POSSIBLES
                while(choix < 1 || n_ludo > NBRE_MAX || ludotheques->tab[n_ludo-1]== NULL)
                {
                    printf("Choix invalide, cette ludotheque n'existe pas.\n");
                    scanf("%d", &n_ludo);
                }

                //Saisie des paramètres
                printf("Entrez le nom du jeu : ");
                scanf("%s", nom);

                printf("Quel genre pour le jeu ?\n");
                printf("0- Plateau | 1- RPG | 2- Cooperatif | 3- Ambiance | 4- Hasard \n");
                scanf("%d", &genre);
                while(genre < 0 || genre > 5)

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

                //Création du jeu
                newgame = creer_jeu(strdup(nom), genre, nbMin, nbMax, duree); // Strdup permet de reinitialiser la chaine de caractère
                if (ajouter_jeu(ludotheques->tab[n_ludo-1], newgame) == 1)
                    printf("Jeu ajoute\n");
                else printf("Erreur d'ajout\n");
            }
            break;

        case 4: //Suggestions de jeu

             if (ludotheques->nb_ludos ==0) //Aucune ludothèque initialisée
                printf("Il n'y a aucune ludotheque. Veuillez en creer une auparavant.\n");
            else
            {
                printf("Dans quelle ludotheque voulez-vous chercher un jeu ?\n");
                int i;

                // AFFICHAGE DES NUMEROS DES LUDOS DEJA CREES
                printf("Ludotheques precedemment crees : ");
                for (i=0; i< NBRE_MAX; i++)
                    if (ludotheques->tab[i]!=NULL)
                        printf("%d ", i+1);
                printf("\n");

                // CHOIX DE LA LUDO
                scanf("%d",&n_ludo);

                // TEST DES ERREURS POSSIBLES
                while(choix < 1 || n_ludo > NBRE_MAX || ludotheques->tab[n_ludo-1]== NULL)
                {
                    printf("Choix invalide, cette ludotheque n'existe pas.\n");
                    scanf("%d", &n_ludo);
                }
                if (ludotheques->tab[n_ludo-1]->debut== NULL)
                    printf("Cette ludotheque est vide\n");

                else{

                //Saisie des critères
                printf("Recherche d'un jeu\nQuel genre pour le jeu ?\n");
                printf("0- Plateau | 1- RPG | 2- Cooperatif | 3- Ambiance | 4- Hasard | -1 pour ignorer \n");
                scanf("%d", &genre);
                while(genre < -1 || genre > 5)
                {
                    printf("Genre invalide.\n");
                    scanf("%d", &genre);
                }

                printf("Nombre de joueurs ? -1 pour ignorer \n ");
                scanf("%d", &nbJ);
                while(nbJ < 0 && nbJ != -1)
                {
                    printf("Nombre invalide.\n");
                    scanf("%d", &nbJ);
                }

                printf("Duree moyenne de jeu ? -1 pour ignorer \n ");
                scanf("%d", &duree);
                while(duree < 0 && duree != -1)
                {
                    printf("Duree invalide");
                    scanf("%d", &duree);
                }

                //Recherche et affichage des jeux correspondants
                t_ludotheque* sugg = requete_jeu(ludotheques->tab[n_ludo-1], genre, nbJ, duree);
                printf("Voici les jeux correspondant à votre recherche");
                affiche_ludotheque(sugg);
}
            break;

        case 5: //Fusion de 2 ludothèques contenant des doublons
            l1 = creer_ludotheque();
            l2 = creer_ludotheque();
            j1 = creer_jeu("Times up", 3, 4, 8, 35);
            j2 = creer_jeu("Endor", 1, 3, 8, 90);
            j3 = creer_jeu("Monopoly", 1, 3, 8, 90);
            j4 = creer_jeu("Times up", 3, 4, 8, 35);
            j5 = creer_jeu("a", 3, 4, 8, 35);

            ajouter_jeu(l1, j1);
            ajouter_jeu(l1, j2);
            ajouter_jeu(l2, j3);
            ajouter_jeu(l2, j4);
            ajouter_jeu(l2, j5);
            printf("Ludotheque 1: \n");
            affiche_ludotheque(l1);
            printf("Ludotheque 2: \n");
            affiche_ludotheque(l2);

            printf("Fusion!\n");
            t_ludotheque* lfus = fusion(l1, l2);
            printf("Resultat de la fusion :\n");
            affiche_ludotheque(lfus);
            break;

        case 6: //Libération de l'espace mémoire puis fin du programme
            for (i=0; i< NBRE_MAX; i++)
                if (ludotheques->tab[i]!=NULL)
                    supprimer_ludotheque(ludotheques->tab[i]);

            if (l1 != NULL)
                supprimer_ludotheque(l1);
            if (l2 != NULL)
                supprimer_ludotheque(l2);
            if (lfus != NULL)
                supprimer_ludotheque(lfus);
            if (l != NULL)
                supprimer_ludotheque(l);
            for (i=0; i>20; i++); // Boucle qui permet de ne pas planter avec le break juste après...
            break;
        } //switch
    }
}
    while (choix !=6);

    return;


}



