#include"train.h"
#include"parseur.h"
#include"label.h"
#include"neuronne.h"






double DistanceEucledienne(double *v1,double *v2, int NbDouble)
{
    int i;
    double distance= 0.0;

    for(i=0;i<NbDouble;i++){
        distance = distance + pow(v1[i]-v2[i],2);
    }

    distance = sqrt(distance);

    return(distance);
}


/***************************************************************************************************************/
ElementListe* RetourElementList(Liste *L,int Position)
{
    int i=0;
    if(L==NULL)
    {
         exit(EXIT_FAILURE);
    }
    ElementListe *e = L->PremierElement;
    ElementListe *tmp = e ;

    while ((i<Position)&&(e->Suivant != NULL))
    {   tmp = e;
        e = e->Suivant;
        i++;
    }

    if(i==Position)
    {
        tmp->Suivant=e->Suivant;
        e->Suivant=NULL ;

    }



    return e ;
}

/***************************************************************************************************************/

void AjoutElementListe(Liste *L, int NumLigne, int NumCol)
{
    ElementListe *Nouveau = malloc(sizeof(*Nouveau));
    if (L == NULL || Nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Nouveau->NumLigne = NumLigne;
    Nouveau->NumCol = NumCol;
    Nouveau->Suivant = L->PremierElement; 
    L->PremierElement = Nouveau;
}
/***************************************************************************************************************/

void SuppressionElementListe(Liste *L)
{   ElementListe *aSupprimer;
    if (L == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while (L->PremierElement != NULL)
    {
        aSupprimer = L->PremierElement;
        L->PremierElement = L->PremierElement->Suivant;
        free(aSupprimer);
    }
}

/***************************************************************************************************************/

ElementListe* BestMatchUnit (Neuronne ** N, int NbLigne, int NbCol,int NbDouble, double* VectDonnee)
{  
    int i,j; 
    double distanceEuc;
    Liste *L = malloc(sizeof(Liste));
    L->NbNeuronne = 0;
    int position ;
    L->DistanceMin= DistanceEucledienne(VectDonnee,N[0][0].VectDouble,NbDouble);
    L->PremierElement = NULL;
    ElementListe *element ;

    for(j=0;j<NbLigne;j++)
    {  

        for(i=0;i<NbCol;i++)
        {   

            distanceEuc= DistanceEucledienne(VectDonnee,N[j][i].VectDouble,NbDouble);
            if( distanceEuc == L->DistanceMin) 
            {   // insertion en tete 
                AjoutElementListe(L,j,i);
                
             
                L->NbNeuronne ++ ;
               

            } 
            
            if(distanceEuc < L->DistanceMin)
            {   
                        // free les element de la liste

                        SuppressionElementListe(L);
                     
                        element = malloc(sizeof(ElementListe));
                        element->NumLigne = j;
                        element->NumCol = i;


                        element->Suivant = NULL;
                        L->NbNeuronne = 1;
                        L->DistanceMin= distanceEuc;
                        L->PremierElement = element;
                        
                        


            }
        


        }
            
    }

    position = rand()%(L->NbNeuronne);

    element = RetourElementList(L,position);

    return  element;

}

/***************************************************************************************************************/

void ApplicationRegleApprentissage(double *VectDonnee, double *VectNeur, int NbDouble, double Alpha)
{   int i;
    for(i=0;i<NbDouble;i++)
    {
        VectNeur[i]=VectNeur[i]+Alpha*(VectDonnee[i]-VectNeur[i]);
       

    }

}


/***************************************************************************************************************/

void Melanger(int Tab[],int NombreElement)
{       int tmp;
        int i;
        int random;
        srand(time(NULL));
        for (i=0;i<NombreElement;i++)
        {
            random = rand()%NombreElement;
           
            tmp = Tab[random];
            Tab[random]=Tab[i];
            Tab[i]=tmp;

        }

}
/***************************************************************************************************************/


void Apprentissage(double AlphaInit,int rayon,Neuronne** Neur,IrisData Iris,int NbLigne, int NbCol)
{ 
    double AlphaT;
    int i,j;
    
    ElementListe *e;
    int Tab[Iris.NombreElement];
    for(i=0;i<Iris.NombreElement;i++)
    {
        Tab[i]=i;
    }
    int NbIteration = (int)((500 * Iris.NombreDouble)/4);
    //phase 1   
	for(j=0;j<NbIteration;j++)  
	{  

	    AlphaT=AlphaInit*(1-(j/NbIteration));
	    Melanger(Tab,Iris.NombreElement);
	    for(i=0;i<Iris.NombreElement;i++)
	    {
	     
	            
		           
		      	 e = BestMatchUnit (Neur,NbLigne,NbCol,Iris.NombreDouble,Iris.IrisTab[Tab[i]].VectDouble);
		        
		        ApplicationRegleApprentissageRayon(rayon,e->NumLigne,e->NumCol,Iris.IrisTab[Tab[i]].VectDouble,Neur, Iris.NombreDouble,AlphaT,NbLigne,NbCol);
		        	
		        

		        
		        
		        
		      
		}
		    
		 
		     
	}

	        AlphaInit = AlphaInit/10;
	  
	        AlphaT = AlphaInit;
	        NbIteration = (int)((500 * Iris.NombreDouble)-((500 * Iris.NombreDouble)/4));



    //phase 2

	for(j=0;j<NbIteration;j++) 
	{

	    Melanger(Tab, Iris.NombreElement);
	    AlphaT=AlphaInit*(1-(j/NbIteration));
	    for(i=0;i<Iris.NombreElement;i++)
	    {
	       e = BestMatchUnit (Neur,NbLigne,NbCol,Iris.NombreDouble,Iris.IrisTab[Tab[i]].VectDouble);

	        ApplicationRegleApprentissageRayon(1,e->NumLigne,e->NumCol,Iris.IrisTab[Tab[i]].VectDouble,Neur, Iris.NombreDouble,AlphaT,NbLigne,NbCol);
	        
	    }
	       
	}



}



/***************************************************************************************************************/
void ApplicationRegleApprentissageRayon(int Rayon,int NumLigneBMU,int NumColBMU,double *VectDonnee,Neuronne **N, int NbDouble, double Alpha,int NbLigne, int NbCol)
{
    int i,j;
    for(j=NumLigneBMU-Rayon;j<=NumLigneBMU+Rayon;j++)
    {
        for(i=NumColBMU-Rayon;i<=NumColBMU+Rayon;i++)

        {
                 if((i>=0)&&(i<NbCol)&&(j>=0)&&(j<NbLigne))
                {
                 ApplicationRegleApprentissage(VectDonnee,N[j][i].VectDouble,NbDouble,Alpha);
              
                }

        }
    }

}

