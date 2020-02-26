
#include"parseur.h"
#include"train.h"
#include"label.h"
#include"neuronne.h"


int main(){


	/***********************   CONFIGURATION  *****************************************/

		char *NomFichierData = strdup("iris.data");

		int NombreLigneReseauNeuronne = 6 ;
		int NombreColonneReseauNeuronne = 10 ;
	
		double AlphaInitialePourAprentissage = 0.9;
		int RayonApprentissagePremierePhase = 3 ;


	/*********************************************************************************/

	
		srand(time(NULL));

		IrisData Iris;

		Iris = ParserFichierIris(NomFichierData);

		double *v= CalculVecteurMoyen(Iris);

		Neuronne ** N =  ReseauDeNeuronne(v,NombreLigneReseauNeuronne,NombreColonneReseauNeuronne,Iris.NombreDouble); 

		Apprentissage(AlphaInitialePourAprentissage,RayonApprentissagePremierePhase,N,Iris,NombreLigneReseauNeuronne,NombreColonneReseauNeuronne);

		Etiquetage(N,Iris,NombreLigneReseauNeuronne,NombreColonneReseauNeuronne);

		AfficherMatriceNomIrisFinale(N,NombreLigneReseauNeuronne,NombreColonneReseauNeuronne);


		//AfficherStructure(Iris); 

		//AfficherReseauNeuronne(N,NombreLigneReseauNeuronne,NombreColonneReseauNeuronne,Iris.NombreDouble); 

		//AfficherVecteur(v,Iris.NombreDouble);   

		//AfficherMatriceNomIris(N,NombreLigneReseauNeuronne,NombreColonneReseauNeuronne);


		free(N);



	return 0;
}

