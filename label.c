
#include"parseur.h"
#include"train.h"
#include"neuronne.h"
#include <windows.h>
#include<string.h>


/***************************************************************************************************************/


void Couleur(int couleurDuTexte) 
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDuTexte);
}


/***************************************************************************************************************/


void Etiquetage(Neuronne **N, IrisData Iris,int NbLigne, int NbCol)
{
	double distance, distanceMin;

	int positionMin ;
	int i,j,k;
    	
    
    for(j=0;j<NbLigne;j++)
    {  
    	
        for(i=0;i<NbCol;i++)
        {   distanceMin= DistanceEucledienne(N[j][i].VectDouble,Iris.IrisTab[0].VectDouble,Iris.NombreDouble);
        	positionMin = 0;

        	for(k=0;k<Iris.NombreElement;k++)
        	{

        		distance = DistanceEucledienne(N[j][i].VectDouble,Iris.IrisTab[k].VectDouble,Iris.NombreDouble);
        		
        		if(distance < distanceMin)
        		{
        			distanceMin= distance;
        			positionMin = k;
        			


        		}

        		
        		
        	}
        	    
      			N[j][i].NomIris = malloc(strlen(Iris.IrisTab[positionMin].NomIris)*sizeof(char));
      			strcpy(N[j][i].NomIris,Iris.IrisTab[positionMin].NomIris);
				




        }
            
    }
}


/***************************************************************************************************************/


void AfficherMatriceNomIrisFinale(Neuronne **N,int NbLigne,int NbCol)
{
    int i,j;
    					

    for(j=0;j<NbLigne;j++)
    {      	

        for(i=0;i<NbCol;i++)
        {  
			

            if((strcmp(N[j][i].NomIris,"Iris-virginica") == 0)||(strcmp(N[j][i].NomIris,"Iris-virginica\n") == 0)||(strcmp(N[j][i].NomIris,"Iris-virginica\0") == 0))
            {	
            	
            	Couleur(1);
                printf(" V ");

            }

            if((strcmp(N[j][i].NomIris,"Iris-versicolor") == 0)||(strcmp(N[j][i].NomIris,"Iris-versicolor\n") == 0)||(strcmp(N[j][i].NomIris,"Iris-versicolor\0") == 0))
            {	
            	
            	Couleur(10);
                printf(" C ");
            }

            if((strcmp(N[j][i].NomIris,"Iris-setosa") == 0)||(strcmp(N[j][i].NomIris,"Iris-setosa\n") == 0)||(strcmp(N[j][i].NomIris,"Iris-setosa\0") == 0))
            {
            	Couleur(12);
                printf(" S ");

            }

            
        }
        printf("\n");    

    }

		
}