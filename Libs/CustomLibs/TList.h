#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#ifndef TList_H
#define TList_H

namespace TList{
    struct TList{
        int info;
        TList *next, *prev;
    };

    TList* ListCreate();

    bool IsEmptyList(TList **list);

    //Añade un valor al inicio de la list
    void ListAdd(TList **list, int v);

    //Devuelve en consola los valores de la list
    void ListPrint(TList *list);

    //Devuelve en consola los valores de la list invertidos de orden
    void ListPrintReverted(TList *list);

    //Devuelve el número de datos que contiene la list
    int ListLength(TList* list);

    //Devuelve nodo buscando por el valor a encontrar
    TList* ListFind(TList *list, int info);

    //Extrae de la list el nodo pasado por parametro y lo devuelve desvinculado
    TList* ListExtract(TList **elemento_list);

    // //Elimina el nodo con el valor info introducido
    void ListRemove(TList **list, int info);

    void EmptyList(TList **list);
}

#endif

