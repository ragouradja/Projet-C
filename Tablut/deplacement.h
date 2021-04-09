#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "plateau.h"


//Constantes


typedef enum {N,S,E,O} direction;


//Structure


typedef struct Coord
{		

    int j;
    
    int i_depart;
    int j_depart;

    int i_arrive;
    int j_arrive;
	
}Coord;


//Prototype des fonctions


void deplacement_pions(Plateau *a, Coord co);
int dir(Coord co);
void message(int a);

int validite_deplacement(Plateau *a,Coord co);
int capture_pions(Plateau *a, Coord co);
int detecte_bord_chateau(Plateau *a,int i,int j);
int capture_roi(Plateau *a , Coord co);












#endif
