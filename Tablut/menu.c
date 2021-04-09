#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "deplacement.h"
#include "menu.h"
#include "time.h"

extern int SIZE;

void Menu()
{
    printf ("MENU : \n\n");
    printf ("[1] - Partie : Joueur contre joueur\n");
    printf ("[2] - Partie : Joueur contre ordinateur\n");
    printf ("[3] - Quitter le jeu \n\n");
    printf ( "Tapez le numero de votre choix : \n\n");
}


void fin_jeu(Plateau *a,Coord co)
{
    if(capture_pions(a,co) == -1 || capture_roi(a,co) == -1)
	{
	    printf("\nLe Roi a ete capture ! \n");
	    printf("\nLes Assaillants gagnent la partie ! \n");


	    liberer(a);

	    exit(1);
	}

    if ( a-> contenu[co.i_arrive][co.j_arrive].piece == ROI) {

	if ( co.j_arrive == SIZE - 1
	     || co.j_arrive == 0       
	     || co.i_arrive ==  0        
	     || co.i_arrive == SIZE - 1)  
	    {
		 
		printf ( "\nLe Roi s'est echappe \n");
		printf ( "\nLes Defenseurs gagnent la partie ! \n");


		liberer(a);

		exit(1);
	    }
    }

}

Coord saisie_coord(Coord co)
{
    printf("\nCoordonnees de depart : \n");
    
    scanf("%d",&co.i_depart);
    scanf("%d",&co.j_depart);

    printf("\nCoordonnes d'arrive ? \n");
    scanf("%d",&co.i_arrive);
    scanf("%d",&co.j_arrive);

    return co;
}

void jvj(Plateau *a)
{
    Coord joueur2,joueur1;
    int val,val2;

    
    if(joueur1.j != 1 && joueur1.j != 2 )
	{
	    do{
		printf ("Joueur 1, choississez votre camps : \n1 : Defenseur (Suedois)  \n2 : Assaillant (Moscovites) \n");
		scanf("%d",&joueur1.j);
	
	    }while(joueur1.j != 1 && joueur1.j != 2);

    
	    if(joueur1.j == 1) joueur2.j = 2;
	    else joueur2.j = 1;
	    
	    afficher(a); 	
	}
    
    do{
	
	printf("Joueur 1 veuillez entrer des coordonnees\n");
	joueur1 = saisie_coord(joueur1);

	val = validite_deplacement(a,joueur1);
		
	if(val != 1) message(val);

    }while(val != 1);
	
       
    
    deplacement_pions(a,joueur1);
    

    do{
	printf("Joueur 2 veuillez entrer des coordonnees \n");
	joueur2 = saisie_coord(joueur2);


	val2 = validite_deplacement(a,joueur2);
	
	if(val2 != 1) message(val2);

    }while(val2 != 1);
	 
    deplacement_pions(a,joueur2);
    
}


void jvpc (Plateau *a)
{
    Coord joueur1, bot;
    int val;
  
    
    if (joueur1.j != 1 && joueur1.j != 2)
	{
	    do {
		printf ( "Joueur, choississez votre camps : \n1 : Defenseur (Suedois)  \n2 : Assaillant (Moscovites) \n");
		scanf ("%d", &joueur1.j);
	
	    }while(joueur1.j != 1 && joueur1.j != 2);
      
	    if(joueur1.j == 1) bot.j = 2;
	    else bot.j = 1;

	    afficher(a); 	
	} 
    

    do{
      

      
	printf("Joueur, veuillez entrer des coordonnées : \n");
      
	joueur1 = saisie_coord(joueur1);

	val = validite_deplacement(a,joueur1);

	if(val != 1) message(val);
    }
    while(val != 1);

  
    deplacement_pions(a,joueur1);
  


 

  
    bot =  bot_rdm(a,bot);

    printf("\nLe bot deplace une piece... \n\n");
  
    deplacement_pions(a,bot);

  
 
}



Coord  bot_rdm(Plateau *a,Coord co)
{
    int i=0,j=0, h_v = 1;
    int PIECE;
    
    srand(time(NULL));
	
    if(co.j == 1) PIECE = SUEDOIS;
    else PIECE = MOSCOVITE;
    
    do{
	do{
	    co.i_depart = rand()%9; 
	    co.j_depart = rand()%9;
	 	  
	}while(a -> contenu[co.i_depart][co.j_depart].piece != PIECE);
	
	h_v = rand()%1;

	if (h_v == 1) { 	
	    
	    co.i_arrive = rand()%9; 
	    co.j_arrive = co.j_depart;
	 
	}
	else{			
	    
	    co.i_arrive = co.i_depart; 
	    co.j_arrive = rand()%9;
	 
	}
    }
    while(validite_deplacement(a,co) != 1);

   
    return co;
}
