#include "Filas.h"

nodoD *crearNodoD(element a)
{
    nodoD *nuevo = (nodoD *)malloc(sizeof(nodoD));
    nuevo->dato = a;
    nuevo->ant = NULL;
    nuevo->sig = NULL;

    return nuevo;
}
void inicFila(Fila *F)
{

    (*F).pri = NULL;
    (*F).ult = NULL;
}

int FilaVacia(Fila F)
{
    if (F.pri == NULL)
    {
        return 1;
    }
    else
    {
        return 0; /// PONELO SIEMPRE FLACO
    }
}

void poneFila(Fila *F, element a)
{
    nodoD *nuevo = crearNodoD(a);
    if ((*F).pri == NULL)
    {

        (*F).pri = nuevo;
        (*F).ult = nuevo;
    }
    else
    {

        (*F).ult->sig = nuevo; //El que esta atras del ultimo ahora pasa a ser el nuevo
        nuevo->ant = (*F).ult; //El que esta adelante del ultimo
        (*F).ult = nuevo;      // Ahora el nuevo es el ultimo
    }
}
element sacaFila(Fila *F) ///Este Borra
{
    element dato;
    nodoD *aux;
    aux = (*F).pri;
    if ((*F).pri == (*F).ult) //Verifico que haya un solo elemento en la fila
    {
        (*F).pri = NULL; //Reacciono NULL
        (*F).ult = NULL;
    }
    else
    {
        (*F).pri = (*F).pri->sig; // Muevo el puntero del primero al siguiente de la fila
        (*F).pri->ant = NULL;     //"Aviso que no hay nadie adelante"
    }
    dato = aux->dato;
    free(aux);
    return dato;
}

element primeroFila(Fila F) //Este retorna
{
    return F.pri->dato;
}

element ultimoFila(Fila F)
{
    return F.ult->dato;
}
