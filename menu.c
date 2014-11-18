#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int affichage_menu()
{
    int choix;

    printf("---Menu---\n\n");
    printf("1. Créer une ludothèque\n");
 printf("2. Afficher une ludothèque\n");
 printf("3. Ajouter un jeu dans la ludothèque en saisissant ses caractéristiques\n");
 printf("4. Effectuer une recherche de jeu à partir de critères saisis par l’utilisateur\n");
 printf("5. Créer 2 ludothèques, les afficher, les fusionner puis afficher la nouvelle ludothèque\n");
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
