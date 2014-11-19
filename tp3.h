#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NBRE_MAX 10

enum genre_jeu {PLATEAU, RPG, COOPERATIF, AMBIANCE, HASARD};


typedef struct jeu {
    char *nom;
    enum genre_jeu genre;
    int nbJoueurMin;
    int nbJoueurMax;
    int duree;
    struct jeu *suivant;
} t_jeu;

typedef struct ludotheque {
    int nb_jeu; //indique nombre jeux de la ludotheque
    t_jeu* debut; //adresse du premier jeu, ou NULL si ludotheque vide
} t_ludotheque;

//B : Fonctions
t_ludotheque* creer_ludotheque(); //OK
t_jeu* creer_jeu(char * nom, enum genre_jeu genre, int nbJoueurMin, int nbJoueurMax, int duree); //OK
int ajouter_jeu(t_ludotheque* ludo, t_jeu* j); //OK
const char* enumtostring(enum genre_jeu type); //OK
void affiche_ludotheque(t_ludotheque* ludo); //Indentation des colonnes à revoir
void supprimer_ludotheque(t_ludotheque* ludo); //OK
void supprimer_jeu(t_jeu* j); //OK
int retirer_jeu(t_ludotheque* ludo, char*nom);
t_ludotheque* requete_jeu(t_ludotheque* ludo, enum genre_jeu genre, int nbJoueurs, int duree);
t_ludotheque * fusion(t_ludotheque * ludo1, t_ludotheque * ludo2) ;
int affichageMenu(void);

#endif // FONCTIONS_H_INCLUDEDdonc
