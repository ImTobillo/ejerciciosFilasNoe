#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include <stdlib.h>

typedef struct
{
    char dni[10];
    char nombre[30];
    int nroTurno;
    char prioridad; //'s' o 'n'
    char tipoTramite[30]; //Hogar, Automotor
} Turno;

typedef struct nodoD
{
    Turno trn;
    struct nodoD* ant;
    struct nodoD* sig;
}nodoD;

typedef struct
{
    nodoD* prim;
    nodoD* ult;
}Fila;

void inicFila (Fila*);
int filavacia (Fila);
Turno primero (Fila);
Turno sacar (Fila*);
void agregar (Fila*, Turno);

#endif // FILA_H_INCLUDED
