#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

extern int SIZE;			

Plateau *allocmat(void)
{
    int i = 0;
    Plateau *tab = NULL;

    tab = malloc(sizeof(Plateau));

    tab -> contenu = malloc(SIZE * sizeof(int*));

    for(i = 0; i < SIZE; i++)

	tab -> contenu[i] = malloc(2*SIZE * sizeof(int));


    if(tab == NULL)
	{
	    printf("allocmat : erreur alloc \n");
	    exit(EXIT_FAILURE);
	}
	

    return tab;

}

void liberer(Plateau *a)
{
    int i;

    for(i = 0; i < SIZE; i++)
	{
	    if(a-> contenu[i])
		free(a -> contenu[i]);
	}

    free(a -> contenu);

    free(a);

}

void initialiser(Plateau *a)
{
    int i = 0,j = 0;

    for(i = 0; i < SIZE; i++)
	{
	    for (j = 0; j < SIZE; j++)
		{
		    a -> contenu[i][j].piece = VIDE;
		    a -> contenu[i][j].chateau = 0;
		
		}
	}

    placer_pions(a);						
}


void afficher(Plateau *a)			
{
    int i,j;
									
	
    printf(" ");
    for(i = 0; i < SIZE ; i++)
	{
	    printf("%d ",i);
		
	}

    printf("\n");

	
    for(i = 0; i <= SIZE*2 ; i++)
	printf("-");

    printf("\n");


    for(i = 0; i < SIZE; i++)
	{	

	    for (j = 0; j <= SIZE; j++)
		{   
			
		    if(j == SIZE ) printf("| %d",i);
		    else printf("|");

		    if(j != SIZE)
			{
			    switch(a -> contenu[i][j].piece)
				{
				case 2:
				    printf("S");
				    break;
				case 3: 
				    printf("M");
				    break;
				case 1: 
				    printf("K");
				    break;
				default:
				    printf(" ");
				}
			}
		}

	    printf("\n");
	}
	

    for(i = 0; i <= SIZE*2 ; i++)
	printf("-");
    printf("\n");
}


void placer_pions(Plateau *a)
{
    int m = SIZE /2,bord = m/2;
    int i,j,f=0;


    while(f != 4)
	{	

	    if(f < 2)
		{
		    if( f == 0)
			{
			    i = m;
			    j = -1;
			}
		    j++;
		} 
	    else if(f >=2)
		{
		    if(f == 2)
			{
			    i = -1;
			    j = m;
			}
		    i++;
		}
	    if(j == 0 || j == SIZE-1)
		{
		    a-> contenu[i-1][j].piece = MOSCOVITE;
		    a-> contenu[i+1][j].piece = MOSCOVITE;
			
		    f++;
		}
	    if(i == 0 || i == SIZE-1)
		{
		    a-> contenu[i][j-1].piece = MOSCOVITE;
		    a-> contenu[i][j+1].piece = MOSCOVITE; 

		    f++;
		}

	    if((i >= bord && i <= bord+m) && (j >= bord && j <= bord+m))
		{
		    a-> contenu[i][j].piece = SUEDOIS;
		    a-> contenu[i][j].chateau = 1;			
		}
	    else
		{
		    a-> contenu[i][j].piece = MOSCOVITE;
		}
	}
    a -> contenu[m][m].piece = ROI;
    a -> contenu[m][m].chateau = 2;

	
}

