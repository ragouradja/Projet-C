#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdio.h>
#include <stdlib.h>



//Constantes

typedef enum {VIDE,ROI,SUEDOIS,MOSCOVITE} piece;
				


//Structure

typedef struct Cellule
{
    int chateau; 								
    piece piece;
	
}Cellule;


typedef struct Plateau
{
    Cellule **contenu;

}Plateau;




//Prototype des fonctions

Plateau *allocmat(void);
void liberer(Plateau *a);

void afficher(Plateau *a);						
void initialiser(Plateau *a);

void placer_pions(Plateau *a);

#endif
