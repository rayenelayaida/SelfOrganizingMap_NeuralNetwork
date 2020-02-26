#ifndef __NEURONNE__
#define __NEURONNE__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"parseur.h"
#include"train.h"
#include"label.h"
#include <time.h>


typedef struct Data Data ;
typedef struct IrisData IrisData ;
typedef struct Neuronne Neuronne;

struct Neuronne {
	double *VectDouble;
	char *NomIris;
};


double* CalculVecteurMoyen(IrisData iris);

void AfficherVecteur(double *v,int tailleV);

Neuronne NouveauNeuronne(double *VectMoyen,int NbDouble);

Neuronne** ReseauDeNeuronne(double* VectMoyen,int NbLigne,int NbCol,int NbDouble);

void AfficherReseauNeuronne(Neuronne **N,int NbLigne,int NbCol,int NbDouble);

#endif
