#ifndef __LABEL__
#define __LABEL__

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include <time.h>
#include"train.h"
#include <windows.h>
#include"parseur.h"
#include"neuronne.h"

typedef struct Data Data;

typedef struct IrisData IrisData;

typedef struct Neuronne Neuronne;

typedef struct ElementListe ElementListe;

typedef struct Liste  Liste;

void Couleur(int couleurDuTexte);

void Etiquetage(Neuronne **N, IrisData Iris,int NbLigne, int NbCol);

void AfficherMatriceNomIrisFinale(Neuronne **N,int NbLigne,int NbCol);




#endif