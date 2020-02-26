#ifndef __PARSEUR__
#define __PARSEUR__

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include <time.h>
#include"train.h"
#include"label.h"
#include"neuronne.h"


typedef struct Data Data ;
struct Data 
{	double *VectDouble;
	double Norme;
	char *NomIris;
};

typedef struct IrisData IrisData ;

struct IrisData{
	int NombreElement;
	Data *IrisTab;
	int NombreDouble;
};

typedef struct Neuronne Neuronne;



int NombreLigneFichier(char* NomFichier);

int  NombreDouble(char* NomFichier);

IrisData InitIris(char* NomFichier);

Data ParserLigneDansTab(int NbDouble,char *Ligne);

IrisData ParserFichierIris(char* NomFichier);

void AfficherStructure(IrisData iris);

void AfficherMatriceNomIris(Neuronne **N,int NbLigne,int NbCol);


#endif