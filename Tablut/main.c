#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "deplacement.h"
#include "menu.h"

 
const int SIZE = 9;




int main()

{
    Plateau *plat = NULL;
    Coord co;
    int mode;


    plat = allocmat();	
    initialiser(plat);
    printf("\n----------------------");
    printf("\nBienvenue sur le jeu ! \n");
    printf("---------------------- \n\n");


    do
	{
	    Menu();
	    scanf("%d", &mode);
		
	} while ( mode != 3 && mode != 2 && mode != 1 );

    switch (mode)
	{
	case 1:
	    printf ("\nVous avez choisi le mode : Joueur contre joueur \n\n");
	    while(1)
		jvj(plat);
		
	    break;

	case 2 :
	    printf("\nVous avez choisi le mode : Joueur contre ordinateur\n\n");
	    while(1)
		jvpc(plat);

	case 3:
	    printf("\nFin du jeu\n");
	    exit(1);			
	    break;
	}

       


    return 0;

}
