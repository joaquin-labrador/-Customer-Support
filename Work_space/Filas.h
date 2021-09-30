//Librerias
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define element p


//Estructura
typedef struct p{

    long int dni;
    int timeTurn;
    int prioridad;
    char categoria[30];
}p;

typedef struct nodoD
{
    p dato;
    struct  nodoD * ant;
    struct nodoD * sig;    
}nodoD;

typedef struct Fila
{
    nodoD * pri;
    nodoD * ult; 
}Fila;

void inicFila(Fila * F);//
void poneFila(Fila * F, element a);//
element sacaFila(Fila * F);//quitar un elemento del principio de la fila
int FilaVacia(Fila F);//
nodoD *crearNodoD (element a);//
element ultimoFila (Fila F);//
element primeroFila (Fila F);//