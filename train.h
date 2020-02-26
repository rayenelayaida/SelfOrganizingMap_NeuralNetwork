
#ifndef __TRAIN__
#define __TRAIN__

#include<stdio.h>
#include<string.h>
#include<math.h>
#include"parseur.h"
#include <stdlib.h>
#include <time.h>
#include"label.h"
#include"neuronne.h"

 

typedef struct Data Data;

typedef struct IrisData IrisData;

typedef struct Neuronne Neuronne;

typedef struct ElementListe ElementListe;

typedef struct ElementListe{
	int NumCol;
	int NumLigne;
	ElementListe *Suivant;
}ElementListe;


typedef struct Liste{
	double DistanceMin;
	int NbNeuronne;
	ElementListe *PremierElement;
}Liste;



double DistanceEucledienne(double *v1,double *v2, int NbDouble);

Liste* initialisation();

void AjoutElementListe(Liste *L, int NumLigne, int NumCol);

void SuppressionElementListe(Liste *L);

ElementListe* BestMatchUnit (Neuronne ** N, int NbLigne, int NbCol,int NbDouble, double* VectD);

ElementListe* RetourElementList(Liste *l,int Position);

void Apprentissage(double AlphaInit,int rayon,Neuronne** Neur,IrisData Iris,int NbLigne, int NbCol);

void ApplicationRegleApprentissage(double *VectDonnee, double *VectNeur, int NbDouble, double Alpha);

void ApplicationRegleApprentissageRayon(int Rayon,int NumLigneBMU,int NumColBMU,double *VectDonnee,Neuronne **N, int NbDouble, double Alpha,int NbLigne, int NbCol);
void Melanger(int Tab[],int NombreElement);

#endif