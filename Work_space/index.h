#include "Filas.h"
#define littleTime 11
#define longTime 14
#define lowPriority 4

void mostrarPrimero(Fila *fila, Fila *aux);
void llenarFila(Fila *fila);
void mostrarInverso(Fila *fila , Fila *aux);
void showReverse (Fila *fila,Fila *aux);
void ponerPimero(Fila *fila, int dni);
element atenderAEleccion(Fila fila, int opt);
void borrarTurno(Fila *fila,int dni);
void fileLittleTime (Fila *fila, Fila *filaCorta);
void suspendLongTimes (Fila *fila, Fila *suspeded);
void serveCustomer(Fila *fila, Fila *suspended);
int saberPeticionesxCat(Fila *fila, char categoria[]);
int requestsLowPriority(Fila *fila);
//Funciones extras
int askDni();
int askOpt();
void categoria(int op, element *cat);
void view(element i);
void timeTurn(int op, element *time);
void reactivarSuspendido (Fila *fila, Fila *acomodar);
void cleanFile(Fila *fila);
//Menus
void menuCat();
void menuEmpresa();
void menuTiempo();