#include "Filas.h"
#include "TpFilas.h"
int main(){
    int op;
    int dni;
    Fila cola;
    Fila aux;
    Fila timeLittle;
    Fila suspended;
    inicFila(&suspended);
    inicFila(&cola);
    inicFila(&aux);
    inicFila(&timeLittle);
   
    do{
        menuEmpresa();
        scanf("%d",&op);
        system("cls");
        switch (op)
        {
        case 1:
            llenarFila(&cola);
            system("cls"); 
            break;
        case 2:
            mostrarPrimero(&cola, &aux);
            system("pause");
            system("cls");
            break;
        case 3:
            dni = askDni();
            borrarTurno(&cola,dni);
            printf("Turno borrado DNI : %d \n",dni);
            printf("Fila actual: ");
            mostrarPrimero(&cola,&aux);
            system("pause");
            system("cls");
            break;
        case 4:
            fileLittleTime(&cola,&timeLittle);
            printf("Fila turnos cortos: \n");
            mostrarPrimero(&timeLittle,&aux);
            system("pause");
            system("cls");
            cleanFile(&timeLittle);
            break;
        case 5:
            suspendLongTimes(&cola,&suspended);
            printf("Turnos suspedidos\n");
            system("pause");
            system("cls");
            break;
        case 6:
            reactivarSuspendido(&cola,&suspended);
            printf("Turnos reactivados\n");
            system("pause");
            system("cls");
            break;
        case 7:
            serveCustomer(&cola,&suspended);
            break;
        case 8:
            printf("Seleccione la categoria que desea saber las peticiones\n");
            menuCat();
            int seleccion;
            element cat;
            do{
            scanf("%d",&seleccion);
            }while(seleccion > 4 || seleccion <= 0);
            categoria(seleccion,&cat);
            printf("La cantidad de peticiones de la categoria | %s | son | %d |\n",cat.categoria,saberPeticionesxCat(&cola,cat.categoria));
            system("pause");
            system("cls");
            break;
        case 9:
            printf("La cantidad con peticiones con la prioridad mas baja es | %d |",requestsLowPriority(&cola));
            system("pause");
            system("cls");
            break;
        case 10:
              break;
        default:
            break;
        }
    }while(op < 10 && op >= 0);

    return 0;

}

void llenarFila(Fila *fila){
    char s;
    element i;
    int seleccion = 0;

    do{
        printf("Ingrese un DNI a la fila \n");
        scanf("%d", &i.dni);
       do{  
           menuTiempo();
           scanf("%d",&seleccion);    
       }while(seleccion > 4 || seleccion <= 0);
        timeTurn(seleccion,&i);
        do{
           printf("Ingrese el nivel de prioridad del (1 al 4)\n");
           printf("Siendo 1 la prioridad mas alta y 4 la mas baja\n");
           scanf ("%d",&i.prioridad);
        } while (i.prioridad > 4   || i.prioridad <= 0);
        printf("\n");
        do{
            printf("Seleccione la categoria del turno\n");
            menuCat();
            scanf("%d",&seleccion); 
        }while(seleccion > 4 || seleccion <= 0);
        categoria(seleccion,&i);
        poneFila(fila,i);
        printf("Otro turno mas (S/N)\n");
        fflush(stdin);
        scanf("%c", &s);
        towlower(s);
        system("cls");
    } while (s == 's');
       
}
void mostrarPrimero(Fila *fila, Fila *aux){ //De forma recursiva
    element dato;
    if (!FilaVacia(*fila)){
        dato = primeroFila(*fila);
        view(dato);
        poneFila(aux, sacaFila(fila)); //Mando los datos a una fila auxiliar para no perder los datos
        mostrarPrimero(fila, aux);     //Llamada recursiva
        poneFila(fila, sacaFila(aux)); //Vuelvo a acomodar los datos en la fila
    }
}
void mostrarInverso(Fila *fila, Fila *aux){
    element dato;
    if (!FilaVacia(*fila)){
        dato = ultimoFila(*fila); // Utilizo la funcion MIA del TDA
        view(dato);
        poneFila(aux, sacaFila(fila));
        mostrarInverso(fila, aux);
        poneFila(fila, sacaFila(aux));
    }
}
void ponerPimero(Fila *fila, int dni){
    Fila aux;
    Fila primero;
    inicFila(&primero);
    inicFila(&aux);
    int flag = 0;

    while (!FilaVacia(*fila)) {
        if (primeroFila(*fila).dni == dni) {
            poneFila(&primero, sacaFila(fila));
            flag = 1;
        }
        else {
            poneFila(&aux, sacaFila(fila));
        }
    }
    if (flag == 0) {
        printf("Error!, el dni que usted a ingresado no se encuentra en la fila\n");
    }
    else{
        poneFila(fila, sacaFila(&primero));
        while (!FilaVacia(aux)){
            poneFila(fila, sacaFila(&aux));
        }
    }
}
element atenderAEleccion(Fila fila, int opt)
{
    if(opt == 1){
        return primeroFila(fila);
    }
    else
    return ultimoFila(fila);
}
void borrarTurno(Fila *fila,int dni){
    int flag = 0;
    Fila aux;
    inicFila(&aux);
    while(!FilaVacia(*fila)){
        if(primeroFila(*fila).dni == dni){
        sacaFila(fila);
        flag=1;
        }
        else
        poneFila(&aux,sacaFila(fila));
    }
    if(flag == 1){
        while(!FilaVacia(aux)){
            poneFila(fila,sacaFila(&aux));  
        }   
    }
    else
    printf("Error el Dni introducido no es encuentra en la fila");


}
//Pasar los elementos a una fila de tiempos menores o iguales a 10
void fileLittleTime (Fila *fila, Fila *filaCorta){
   
    Fila aux;
    inicFila(&aux);
    while(!FilaVacia(*fila)){
        if(primeroFila(*fila).timeTurn <= littleTime){
            poneFila(filaCorta,primeroFila(*fila));
            poneFila(&aux,sacaFila(fila));
        }
        else
        poneFila(&aux,sacaFila(fila));
    }
    while(!FilaVacia(aux)){
        poneFila(fila,sacaFila(&aux));
    }

}
void suspendLongTimes (Fila *fila, Fila *suspeded){
    Fila aux;
    inicFila(&aux);
    while(!FilaVacia(*fila)){
        if(primeroFila(*fila).timeTurn > longTime){
            poneFila(suspeded,sacaFila(fila));
        }
        else
        poneFila(&aux,sacaFila(fila));
    }
    while(!FilaVacia(aux)){
        poneFila(fila,sacaFila(&aux));
    }
}
void serveCustomer(Fila *fila, Fila *suspended){
    char siguiente;
    do{
    if(!FilaVacia(*fila)){
        printf("Informacion del siguiente cliente\n");
        view(primeroFila(*fila));
        system("pause");
        sacaFila(fila);
    }
    else{
        if(!FilaVacia(*suspended)){
            printf("Informacion del siguiente cliente\n");
            view(primeroFila(*suspended));
            system("pause");
            sacaFila(suspended);
        }
        else
            printf("\nNo hay mas nadie por atender\n\n");
    }
    printf("Desea atender al proximo cliente \n");
    fflush(stdin);
    scanf("%c",&siguiente);
    system("cls");
    }while(siguiente == 's');


}
int saberPeticionesxCat(Fila *fila, char categoria[]){
    int peticiones = 0;
    Fila aux; 
    inicFila(&aux);
    while(!FilaVacia(*fila)){
        if(strcmpi(primeroFila(*fila).categoria,categoria) == 0){
            peticiones ++;
        }
        poneFila(&aux,sacaFila(fila));
    }
    while(!FilaVacia(aux)){
        poneFila(fila,sacaFila(&aux));
    }
    return peticiones;
}
int requestsLowPriority(Fila *fila){
    int pet = 0;
    Fila aux;
    inicFila(&aux);
    while (!FilaVacia(*fila)){
        if(primeroFila(*fila).prioridad == lowPriority){
            pet ++;
        }
        poneFila(&aux,sacaFila(fila));
    }
    while(!FilaVacia(aux)){
        poneFila(fila,sacaFila(&aux));
    }
    return pet;
    
}
//Funciones extras
int askDni(){
    printf("Ingrese un DNI\n");
    int dni;
    scanf("%d", &dni);
    return dni;
}
int askOpt(){
    int option;
    do{
        printf("Atender al primero |1| atender al segundo |2|\n");
        scanf("%d",&option);
    } while (option !=1 && option !=2);
    return option;
    
}
void menuEmpresa (){
    printf("Elige la opcion que desea ejecutar\n");
    printf("(1) Agregar turno\n");
    printf("(2) Ver fila de turnos\n");
    printf("(3) Borrar turno\n");
    printf("(4) Ver fila de turnos cortos\n");
    printf("(5) Suspender turnos largos\n");
    printf("(6) Reactivar turnos suspedidos\n");
    printf("(7) Atender cliente/s\n");
    printf("(8) Saber peticiones por categoria\n");
    printf("(9) Cantidad de peticiones de menor prioridad\n");
    printf("(10) Salir\n");  
}
void view(element i){
    printf("Dni : %d \n",i.dni);
    printf("Tiempo : %d Min\n",i.timeTurn);
    printf("Prioridad : %d  \n",i.prioridad);
    printf("Categoria : %s\n",i.categoria);
    printf("--------------------------\n");
}
void menuCat(){
    printf("(1) Obra social\n");
    printf("(2) Renovacion Membrecia\n");
    printf("(3) Consultas\n");
    printf("(4) Otro\n");
}
void menuTiempo(){
    printf("Seleccione el tiempo del turno\n");
    printf("(1) 5 minutos\n");
    printf("(2) 10 minutos\n");
    printf("(3) 15 minutos\n");
    printf("(4) 20 minutos\n");
}
void categoria(int op, element *cat)
{
 
    switch (op)
    {
    case 1:
        strcpy(cat->categoria,"Obra social");
        break;
    case 2:    
        strcpy(cat->categoria,"Renovacion membrecia");
        break;
    case 3:
        strcpy(cat->categoria,"Consultas");
        break;
    case 4: 
         strcpy(cat->categoria,"Otro");
    default:
        break;
    }
 
}
void timeTurn(int op, element *time){
    switch (op) {
    case 1:
        time->timeTurn = 5;
        break;
    case 2:
        time->timeTurn = 10;
        break;
    case 3:
        time->timeTurn = 15;
        break;
    case 4:
        time->timeTurn = 20;
        break;
    default:
        break;
    }
}
void reactivarSuspendido (Fila *fila, Fila *acomodar){
    while(!FilaVacia(*acomodar)){
        poneFila(fila,sacaFila(acomodar));
    }
}
void cleanFile(Fila *fila){
    while(!FilaVacia(*fila)){
        sacaFila(fila);
    }
}
