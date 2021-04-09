#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "deplacement.h"
#include "menu.h"

extern int SIZE;




void deplacement_pions(Plateau *a,Coord co)

{

    a -> contenu[co.i_arrive][co.j_arrive].piece = a -> contenu[co.i_depart][co.j_depart].piece;	
    a -> contenu[co.i_depart][co.j_depart].piece = VIDE;                                           


    if(co.i_arrive -1 >= 0 && a -> contenu[co.i_arrive -1][co.j_arrive].piece != VIDE ||
       co.i_arrive +1 <  SIZE && a -> contenu[co.i_arrive +1 ][co.j_arrive].piece != VIDE ||
       co.j_arrive -1 >= 0 && a -> contenu[co.i_arrive][co.j_arrive-1 ].piece != VIDE ||
       co.j_arrive +1 <  SIZE && a -> contenu[co.i_arrive][co.j_arrive+1].piece != VIDE )
	{
	    capture_pions(a,co);
	    capture_roi(a,co);
	}

    afficher(a);
    fin_jeu(a,co);
	
	

}

int dir(Coord co)																						
{

    if((co.i_depart > co.i_arrive) && (co.j_depart == co.j_arrive)) return N;
    if((co.i_depart < co.i_arrive) && (co.j_depart == co.j_arrive)) return S;

    if((co.i_depart == co.i_arrive) && (co.j_depart > co.j_arrive)) return O;
    if((co.i_depart == co.i_arrive) && (co.j_depart < co.j_arrive)) return E;
	

}

void message(int a)
{
    switch(a)
	{
	case 2:
	    printf("Ce ne sont pas vos pions ! \n");
	    break;
	case 3:
	    printf("Ce ne sont pas vos pions ! \n");
	    break;
	case 4:
	    printf("\nVeuillez rester sur le plateau ! \n\n");
	    break;
	case 5:
	    printf("\nIl n'y a pas de piece ici ! \n\n");
	    break;
	case 6:
	    printf("\nDeplacement non valide ! \n\n");
	    break;
	case 7:
	    printf("\nVous faites du surplace ! \n\n");
	    break;
	case 8:
	    printf("\nIl y a deja une piece surplace ! \n\n");
	    break;
	case 9:
	    printf("\nVous ne pouvez pas aller sur le trone ! \n\n");
	    break;
	case 10:
	    printf("\nIl y a une piece sur le chemin ! \n\n");
	    break;

	}
}
    
int validite_deplacement(Plateau *a,Coord co)
{
    int i,j,direction;

    // Bon pions ?

    if(co.j == 1 && a -> contenu[co.i_depart][co.j_depart].piece == MOSCOVITE)
	{
		
	    return 2;
	}

	
    else if(co.j == 2 &&( a -> contenu[co.i_depart][co.j_depart].piece == ROI || a -> contenu[co.i_depart][co.j_depart].piece == SUEDOIS))
	{
		
	    return 3;
	}
	
    // Verif sur coordonnées

    if(((co.i_depart < 0 || co.i_depart >= SIZE) || (co.j_depart < 0 || co.j_depart >= SIZE)) 
       || ((co.i_arrive < 0 || co.i_arrive >= SIZE) || (co.j_arrive < 0 || co.j_arrive >= SIZE)))		
	{
		
	    return 4;
	}

    if(a -> contenu[co.i_depart][co.j_depart].piece == VIDE) 									
	{	
	
	    return 5;
	}

    if(co.i_arrive != co.i_depart && co.j_arrive != co.j_depart )					
	{
		
	    return 6;
	}

    if(co.i_arrive == co.i_depart && co.j_arrive == co.j_depart )							
	{
		
	    return 7;
	}

    if(a -> contenu[co.i_arrive][co.j_arrive].piece != VIDE)						
	{
		
	    return 8;
	}

    if(a -> contenu[co.i_arrive][co.j_arrive].chateau == 2)						       		
	{
		
	    return 9;					
	}																							


    // Pions sur chemin ?

	
    direction = dir(co);												 


    j = co.j_depart;				      								

    i = co.i_depart;					       								

    while(1)																						
	{
	    if(direction == N || direction == S)			       				
		{
		    if( i == co.i_arrive) break;	       				

		    if( direction == N ) i--;					   				
		    else i++;																			
		}

	    if(direction == O || direction == E)				       		
		{
		    if(j == co.j_arrive) break;	    					

		    if( direction == O ) j--;			     					
		    else j++;																			
		}

	    if(a -> contenu[i][j].piece != VIDE)				       		
		{
			
		    return 10;																				
		}

	}

    return 1;																						
}

int detecte_bord_chateau(Plateau *a,int i,int j)
{

    if(a -> contenu[i][j].chateau == 1 || a -> contenu[i][j].chateau == 2 ) return 2;
	

    if( i+1 < SIZE && a -> contenu[i+1][j].chateau == 1 
	|| i-1 >= 0  && a -> contenu[i-1][j].chateau == 1
	||j+1 < SIZE && a -> contenu[i][j+1].chateau == 1
	|| j-1 >= 0  && a -> contenu[i][j-1].chateau == 1)

	return 1;

    return 0;
}

	
int capture_pions(Plateau *a, Coord co)															
{

    int VICTIME,VICTIME2,AGRESSEUR,AGRESSEUR2;
    int i = -1,j, i2,j2, f = 1;


    if(a -> contenu[co.i_arrive][co.j_arrive].piece == SUEDOIS || a -> contenu[co.i_arrive][co.j_arrive].piece == ROI)										
	{
	    AGRESSEUR = SUEDOIS;
	    AGRESSEUR2 = ROI;
	    VICTIME = MOSCOVITE;
	    VICTIME2 = MOSCOVITE;
	}

    if(a -> contenu[co.i_arrive][co.j_arrive].piece == MOSCOVITE)											
	{
	    AGRESSEUR = MOSCOVITE;
	    AGRESSEUR2 = MOSCOVITE;
	    VICTIME = SUEDOIS;
	    VICTIME2 = ROI;
	}

	

    while(f <= 4)
	{
	    if(f == 1)		//GAUCHE
		{
		    if(co.j_arrive -2 >=0)
			{		
			    
			    i = co.i_arrive;
			    j = co.j_arrive -1;

			    i2 = co.i_arrive;
			    j2 = co.j_arrive -2;
			}
		}

	    if(f == 2)		//DROITE
		{	
		    if(co.j_arrive +2 < SIZE)
			{		
				
			    i = co.i_arrive;
			    j = co.j_arrive +1;

			    i2 = co.i_arrive;
			    j2 = co.j_arrive +2;
			}
		}
	    if(f == 3)		//BAS
		{
		    if(co.i_arrive + 2 < SIZE)
			{		
				

			    i = co.i_arrive +1;
			    j = co.j_arrive;

			    i2 = co.i_arrive +2;
			    j2 = co.j_arrive;
			}
		}
	    if(f == 4)		//HAUT
		{
		    if(co.i_arrive -2 >= 0)
			{		

					
			    i = co.i_arrive -1;
			    j = co.j_arrive;

			    i2 = co.i_arrive -2;
			    j2 = co.j_arrive;
			}
		}

		
	    if(i != -1){
		if(a -> contenu[i][j].piece == VICTIME ||
		   ( detecte_bord_chateau(a,i,j) == 0 && a -> contenu[i][j].piece == VICTIME2))
		    {
			if(a -> contenu[i2][j2].piece == AGRESSEUR || a -> contenu[i2][j2].piece == AGRESSEUR2)
			    {
		
				if(a -> contenu[i][j].piece == ROI) return -1;
 
				a -> contenu[i][j].piece = VIDE;
				f = 5;


			    }
		    }
	    }
		
	    f++;
	}


    return 0;
}

int capture_roi(Plateau *a , Coord co){
    int i= 0, j=0;
    int num;

    if(a -> contenu[co.i_arrive][co.j_arrive].piece == MOSCOVITE){
		
	if (co.i_arrive - 1 >= 0 && a-> contenu[co.i_arrive - 1][co.j_arrive].piece == ROI){
	    i = co.i_arrive -1;
	    j = co.j_arrive ;
	}
		
	if (co.i_arrive + 1 < SIZE && a -> contenu [co.i_arrive + 1][co.j_arrive].piece == ROI) {
	    i = co.i_arrive + 1;
	    j = co.j_arrive ;
	}

	if (co.j_arrive - 1 >= 0 && a -> contenu [co.i_arrive][co.j_arrive-1].piece == ROI) {
	    i = co.i_arrive;
	    j = co.j_arrive-1 ;
	}

	if (co.j_arrive + 1 < SIZE && a -> contenu [co.i_arrive][co.j_arrive+1].piece == ROI) {
	    i = co.i_arrive;
	    j = co.j_arrive +1 ;
	}

	num = detecte_bord_chateau(a,i,j);
		

	if ( num == 2) { 
	    if (a -> contenu[i][j - 1].piece == MOSCOVITE 
		&& a -> contenu[i][j + 1].piece == MOSCOVITE
		&& a -> contenu[i -1][j].piece == MOSCOVITE 
		&& a -> contenu[i+1][j].piece == MOSCOVITE) 

		{
		    return -1;

		}
	}

	else if ( num == 1 ) {
	    if (( a -> contenu[i][j - 1].piece == MOSCOVITE || a -> contenu[i][j - 1].chateau == 1 ) 
		&& ( a -> contenu[i][j +1].piece == MOSCOVITE || a -> contenu[i][j +1].chateau == 1 ) 
		&& ( a -> contenu[i +1][j].piece == MOSCOVITE || a -> contenu[i +1][j].chateau == 1 ) 
		&& ( a -> contenu[i - 1][j].piece == MOSCOVITE || a -> contenu[i - 1][j].chateau == 1 )) 
		{
			
		    return -1;
		}
	}
        
    }

    return 0;

}

    
