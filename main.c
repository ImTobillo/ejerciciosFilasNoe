#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Fila.h"
#define turnosArch "turnos.bin"

/// estructuras

typedef struct nodo
{
    Turno trn;
    struct nodo* sig;
}nodo;

/// funciones

void inicLista (nodo** lista)
{
    *lista = NULL;
}

nodo* crearNodo (Turno dato)
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));
    aux->trn = dato;
    aux->sig = NULL;
    return aux;
}

void mostrarTurno (Turno trn)
{
    printf("NOMBRE: %s\n", trn.nombre);
    printf("DNI: %s\n", trn.dni);
    printf("NRO TURNO: %i\n", trn.nroTurno);
    printf("PRIORIDAD: %c\n", trn.prioridad);
    printf("TIPO TRAMITE: %s\n", trn.tipoTramite);
}

void mostrarLista (nodo* lista)
{
    while (lista)
    {
        mostrarTurno(lista->trn);
        lista = lista->sig;
    }
}

void insertarOrdenadoLista (nodo** lista, Turno dato)
{
    nodo* nuevo = crearNodo(dato);

    if (*lista)
    {
        if ((*lista)->trn.nroTurno > dato.nroTurno)
        {
            nuevo->sig = *lista;
            *lista = nuevo;
        }
        else
        {
            nodo* ant = *lista, *act = ant->sig;

            while (act && act->trn.nroTurno < dato.nroTurno)
            {
                ant = act;
                act = act->sig;
            }

            if (act)
            {
                ant->sig = nuevo;
                nuevo->sig = act;
            }
            else
                ant->sig = nuevo;
        }
    }
    else
        *lista = nuevo;
}

void despersistirYCargarLista (nodo** lista)
{
    FILE* fp = fopen (turnosArch, "rb");

    Turno turnBff;

    if (fp)
    {
        while (fread(&turnBff, sizeof(Turno), 1, fp))
            insertarOrdenadoLista(lista, turnBff);

        fclose(fp);
    }
    else
        printf("ERROR DE DATOS.\n");
}

void establecerBoxes (nodo** lista, Fila* b1, Fila* b2, Fila* b3)
{
    nodo* aux;

    while (*lista)
    {
        aux = *lista;

        if (aux->trn.prioridad == 's')
            agregar(b1, aux->trn);
        else if (strcmpi(aux->trn.tipoTramite, "Hogar") == 0)
            agregar(b2, aux->trn);
        else
            agregar (b3, aux->trn);

        *lista = (*lista)->sig;
        free(aux);
    }
}

void mostrarFila (Fila* f)
{
    Fila aux;
    inicFila(&aux);

    while (!filavacia(*f))
    {
        mostrarTurno(primero(*f));
        agregar(&aux, sacar(f));
    }

    while (!filavacia(aux))
        agregar(f, sacar(&aux));
}

void atenderEnBox (Fila* box)
{
    if (!filavacia(*box))
    {
        Turno atendido = sacar(box);

        if (atendido.prioridad == 's')
            printf("======== BOX 1 ========\n");
        else if (strcmpi(atendido.tipoTramite, "Hogar") == 0)
            printf("======== BOX 2 ========\n");
        else
            printf("======== BOX 3 ========\n");

        if (filavacia(*box))
            printf("== ULTIMO EN ATENDER ==\n");

        mostrarTurno(atendido);

        printf("=======================\n");
    }
}

void simularJornadaLaboral (Fila* box1, Fila* box2, Fila* box3)
{
    while (!filavacia(*box1) || !filavacia(*box2) || !filavacia(*box3))
    {
        atenderEnBox(box1);
        printf("\n");
        atenderEnBox(box2);
        printf("\n");
        atenderEnBox(box3);
        printf("\n");
    }
}

/// main

int main()
{
    nodo* lista;
    inicLista(&lista);

    despersistirYCargarLista(&lista);

    //mostrarLista(lista);

    Fila box1, box2, box3;
    inicFila(&box1);
    inicFila(&box2);
    inicFila(&box3);

    establecerBoxes(&lista, &box1, &box2, &box3);

    /*printf("\nBOX 1:\n");
    mostrarFila(&box1);
    printf("\nBOX 2:\n");
    mostrarFila(&box2);
    printf("\nBOX 3:\n");
    mostrarFila(&box3);*/

    simularJornadaLaboral(&box1, &box2, &box3);

    return 0;
}
