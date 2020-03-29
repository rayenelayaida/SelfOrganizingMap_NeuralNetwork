#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"parseur.h"
#include"train.h"
#include"neuronne.h"
#include <time.h>

/***************************************************************************************************************/

int NombreLigneFichier(char *NomFichier){

    FILE *f = fopen(NomFichier,"r");
	size_t longueur = 0 ; 
	ssize_t retourGetLine; 
	char *Ligne = NULL ; 
	int cpt = 0 ;

while((retourGetLine = getline(&Ligne,&longueur,f)) != -1)
	{cpt ++ ;} fclose(f);
	return cpt; 
}

/***************************************************************************************************************/

int  NombreDouble(char* NomFichier){
    FILE *f = fopen(NomFichier,"r");
  	size_t longueur = 0 ;
    char *Ligne = NULL ; 
    int cpt = 0;
    const char *separateur = ",";
    double PartieDouble;
    char *PartieText;
    char *PartieCh;

    getline(&Ligne,&longueur,f);
    fclose(f);
    PartieCh = strtok ( Ligne, separateur );

    while ( PartieCh != NULL )
    {
        PartieDouble = strtod(PartieCh,&PartieText);
            if(PartieDouble!=0.0)
            {
                cpt ++ ;
            }
     
        PartieCh = strtok ( NULL, separateur );
    }
       return cpt ;
}

/***************************************************************************************************************/

IrisData InitIris(char *NomFichier){
	IrisData iris;
	iris.NombreElement = NombreLigneFichier(NomFichier);
	iris.NombreDouble = NombreDouble(NomFichier);
	iris.IrisTab = malloc(iris.NombreElement*sizeof(Data));
	return iris ;	
}

/***************************************************************************************************************/

Data ParserLigneDansTab(int NbDouble,char *Ligne){
    Data data;
    data.VectDouble = malloc(NbDouble*sizeof(double));
    data.Norme = 0;
    data.NomIris=NULL;
    int cpt = 0;
    int i;

    const char *separateur = ",";
    double PartieDouble;
    char *PartieText;
    char *PartieCh;

    // Avant normalisation
    PartieCh = strtok ( Ligne, separateur );

    while ( PartieCh != NULL )
    {
        PartieDouble = strtod(PartieCh,&PartieText);
            if(PartieDouble!=0.0)
            {
                data.VectDouble[cpt]= PartieDouble;
                data.Norme=data.Norme + pow(PartieDouble,2); 
                cpt ++ ;
            }
            else{
                    if(PartieText!=NULL)
                    {  
                        data.NomIris = malloc(strlen(PartieText)*sizeof(char));
                        strcpy(data.NomIris,PartieText);
                    }   
                 }
        
        PartieCh = strtok ( NULL, separateur );
    }

    data.Norme= sqrt(data.Norme);
   
    // normalisation du vecteur 
    for(i=0;i<NbDouble;i++)
    {  
        data.VectDouble[i]= data.VectDouble[i]/data.Norme;

    }

    return data;

}

/***************************************************************************************************************/

IrisData ParserFichierIris(char* NomFichier){
    IrisData iris;
    int i ;
    iris= InitIris(NomFichier);
    size_t longueur = 0 ;
    char *Ligne = NULL ;  
    ssize_t retourGetLine;
    FILE *f=fopen(NomFichier,"r");
    for(i=0;i<iris.NombreElement;i++)
    {   
        retourGetLine = getline(&Ligne,&longueur,f);
           
           if(retourGetLine!=(-1))
           {
                iris.IrisTab[i] = ParserLigneDansTab(iris.NombreDouble,Ligne);            
            }
    }
    fclose(f);
    return iris ;
}

/***************************************************************************************************************/

void AfficherStructure(IrisData iris){
    int i, j;
    printf("******************STRUCTURE TAB ********************\n ");
    printf("Nombre de vecteur de donnees : %d \n",iris.NombreElement );
    printf("Nombre de double: %d \n",iris.NombreDouble );
    printf("-----------Les vecteurs normalisés ------------ \n" );

    for(i=0;i<iris.NombreElement;i++)
    {   for(j=0;j<iris.NombreDouble;j++)
        {
            printf("(%f) ,",iris.IrisTab[i].VectDouble[j]);
        }

            printf("(%s) : NORME :  %f \n",iris.IrisTab[i].NomIris,iris.IrisTab[i].Norme);
    }

}

/***************************************************************************************************************/

void AfficherMatriceNomIris(Neuronne **N,int NbLigne,int NbCol)
{
    int i,j;
    for(j=0;j<NbLigne;j++)
    {  
        for(i=0;i<NbCol;i++)
        {   
            printf(" %s",N[j][i].NomIris);
        }
        printf(" \n");    
    }

}
