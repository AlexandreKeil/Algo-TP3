#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int affichage_menu()
{
    int choix;

    printf("---Menu---\n\n");
    printf("1. Cr�er une ludoth�que\n");
 printf("2. Afficher une ludoth�que\n");
 printf("3. Ajouter un jeu dans la ludoth�que en saisissant ses caract�ristiques\n");
 printf("4. Effectuer une recherche de jeu � partir de crit�res saisis par l�utilisateur\n");
 printf("5. Cr�er 2 ludoth�ques, les afficher, les fusionner puis afficher la nouvelle ludoth�que\n");
 printf("6. Quitter\n");
    scanf("%d", &choix);
    return choix;
}

 void menu(void)
{

    switch (affichage_menu())
    {
    case 1:
        printf("Creation d'une ludotheque...");
        tab_ludo[nb_jeu] = creer_ludotheque();

        break;


   case 6 : return ; break;

    default:
        menu();
        break;
    }

}
