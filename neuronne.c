
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"parseur.h"
#include"train.h"
#include"label.h"
#include <time.h>
#include"neuronne.h"

/***************************************************************************************************************/


double* CalculVecteurMoyen(IrisData iris){   
    double *VectMoyen=malloc(iris.NombreDouble*sizeof(double));
    int i,j;
    for(j=0;j<iris.NombreDouble;j++)
    {
        for(i=0;i<iris.NombreElement;i++)
        {
            VectMoyen[j]=VectMoyen[j] + iris.IrisTab[i].VectDouble[j];

        }

            VectMoyen[j]=VectMoyen[j]/iris.NombreElement;
    }

    return VectMoyen ;
}


/***************************************************************************************************************/



Neuronne** ReseauDeNeuronne(double *VectMoyen,int NbLigne,int NbCol,int NbDouble){   
    int i,j;
    Neuronne **ReseauN = malloc(NbLigne*sizeof(Neuronne*));
    
    for(j=0;j<NbLigne;j++)
    {   ReseauN[j] =malloc(NbCol*sizeof(Neuronne));

        for(i=0;i<NbCol;i++)
        {   

           ReseauN[j][i]= NouveauNeuronne(VectMoyen,NbDouble);
            
        }
            
    }

    return ReseauN ; 
}

/***************************************************************************************************************/


Neuronne NouveauNeuronne(double *VectMoyen,int NbDouble){   
    int i;
    double Min,Max,x;
    Neuronne N ;
    N.NomIris= NULL ;
    N.VectDouble=malloc(NbDouble*sizeof(double));

    for(i=0;i<NbDouble;i++)
    {   
        Max= VectMoyen[i] + 0.05;
        Min= VectMoyen[i] - 0.05;
        N.VectDouble[i]= x =rand()/(double)RAND_MAX*(Max-Min)+Min;
      
        
    }

    return N ;
}

/***************************************************************************************************************/


void AfficherVecteur(double *v,int tailleV){   
    int i;
    for(i=0;i<tailleV;i++)
    { 
        printf(" (%f) , ",v[i] );

    }
}

/***************************************************************************************************************/

void AfficherReseauNeuronne(Neuronne **N,int NbLigne,int NbCol,int NbDouble)
{
   int i,j;
    
    for(j=0;j<NbLigne;j++)
    {  

        for(i=0;i<NbCol;i++)
        {   
            printf("---------------------------------------------------\n");

            AfficherVecteur(N[j][i].VectDouble,NbDouble);
            printf(" : %s\n",N[j][i].NomIris);
            

        }
            
    }



}

