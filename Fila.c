#include "Fila.h"

nodoD* crearNodoD (Turno dato)
{
    nodoD* aux = (nodoD*)malloc(sizeof(nodoD));
    aux->trn = dato;
    aux->ant = NULL;
    aux->sig = NULL;
    return aux;
}

void inicFila (Fila* f)
{
    f->prim = NULL;
    f->ult = NULL;
}

int filavacia (Fila f)
{
    return (f.prim == NULL);
}

Turno primero (Fila f)
{
    return f.prim->trn;
}

Turno sacar (Fila* f)
{
    nodoD* aux = f->prim;
    Turno ret = aux->trn;

    if (f->prim == f->ult) /// si solo hay un dato
    {
        inicFila(f);
    }
    else
    {
        f->prim = f->prim->sig;
        f->prim->ant = NULL;
    }

    free(aux);
    return ret;
}

void agregar (Fila* f, Turno dato)
{
    nodoD* nuevo = crearNodoD(dato);

    if (f->prim) /// si fila tiene por lo menos un dato
    {
        f->ult->sig = nuevo;
        nuevo->ant = f->ult;
        f->ult = nuevo;
    }
    else
    {
        f->prim = nuevo;
        f->ult = nuevo;
    }
}

