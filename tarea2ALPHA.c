#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct nodoarbol
{
    int numReserva;
    char nombre[40];
    char destino[40];
    struct nodoarbol *left;
    struct nodoarbol *right;
} NODO;
//----------------------Prototipo de funciones----------------------------------
NODO *crearArbol();
NODO *insertarNodos(NODO *raiz);
NODO *insertarABB(NODO *raiz, NODO *nuevoNodo);

//------------------------------------------------------------------------------
int main()
{
    NODO *raiz = NULL;
    srand(time(NULL));
    int opcion;
    do
    {
        system("cls");
        printf("Selecciones una accion a realizar: \n");
        printf("1. Realizar reservas de vuelo.\n");
        printf("2. Cancelar reservas.\n");
        printf("3. Buscar en los registros de reservas.\n");
        printf("4. Mostrar reservas por destino.\n");
        printf("5. Mostrar reservas ordenadas.\n");
        printf("6. Salir.\n");
        printf(">> ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1: // Realizar reservas de vuelo
            if (raiz == NULL)
            {
                system("cls");
                raiz = crearArbol();
            }
            else
            { // Insertamos nuevos nodos
                system("cls");
                raiz = insertarNodos(raiz);
            }
            break;
        case 2: // Cancelar reservas
            break;
        case 3: // Buscar en los registros de reservas
            break;
        case 4: // Mostrar reservas por destino
            break;
        case 5: // Mostrar reservas ordenadas
            break;
        case 6:
            printf("Saliendo del programa, gracias por su preferencia <3");
            break;
        default:
            printf("Opcion no valida, ingrese nuevamente.");
            getch();
            break;
        }
    } while (opcion != 6);
    printf("Preorden: ");
    preorden(raiz);
    getch();
    treefree(raiz); // LIBERACION DE MEMORIA DEL ARBOL.
    return 0;
}

NODO *crearArbol()
{
    //-----------------Variables-------------
    NODO *raiz = (NODO *)malloc(sizeof(NODO));
    char nombre[40];
    char destino[40];
    raiz->left = NULL;
    raiz->right = NULL;
    //-----------------Nombre------------------------
    printf("Cual es tu nombre honorable aventurero? ");
    fflush(stdin);
    gets(nombre);
    strcpy(raiz->nombre, nombre);

    //-------------------Destino----------------------
    printf("Hacia donde emprendes tu viaje, %s? ", nombre);
    fflush(stdin);
    gets(destino);
    strcpy(raiz->destino, destino);

    //-------------------Numero reserva--------------
    raiz->numReserva = rand() % 900;
    printf("Ya estas anotado! Que tengas un buen viaje, aventurero!");
    getch();
    return raiz;
}

NODO *insertarABB(NODO *raiz, NODO *nuevoNodo) {
    if (raiz == NULL) {
        // Caso base: si el nodo actual es NULL, significa que hemos encontrado el lugar
        // para insertar el nuevo nodo.
        return nuevoNodo;
    }

    // Comparar el número de reserva del nuevo nodo con el número de reserva del nodo actual.
    if (nuevoNodo->numReserva < raiz->numReserva) {
        raiz->left = insertarABB(raiz->left, nuevoNodo); // Llamar recursivamente al subárbol izquierdo
    } else if (nuevoNodo->numReserva > raiz->numReserva) {
        raiz->right = insertarABB(raiz->right, nuevoNodo); // Llamar recursivamente al subárbol derecho
    }

    // Importante: Si el número de reserva es igual, no hacemos nada para evitar duplicados.

    return raiz; // Retornar el puntero al nodo actual (sin cambios)
}

NODO *insertarNodos(NODO *raiz)
{
    NODO *nuevoNodo = (NODO *)malloc(sizeof(NODO));
    //------verificar si la asignación de memoria fue exitosa-----
    if (nuevoNodo == NULL)
    {
        printf("Error al asignar memoria para el nuevo nodo.\n");
        return raiz;
    }
    char nombre[40];
    char destino[40];
    //-----------------Nombre------------------------
    printf("Cual es tu nombre honorable aventurero? ");
    fflush(stdin);
    gets(nombre);
    strcpy(nuevoNodo->nombre, nombre);

    //-------------------Destino----------------------
    printf("Hacia donde emprendes tu viaje, %s? ", nombre);
    fflush(stdin);
    gets(destino);
    strcpy(nuevoNodo->destino, destino);

    //-------------------Numero reserva--------------
    nuevoNodo->numReserva = rand() % 900;
    printf("Ya estas anotado! Que tengas un buen viaje, aventurero!");
    getch();

    //--------------------ABB------------------------
    return insertarABB(raiz, nuevoNodo);
}

void preorden(NODO *raiz){
    if (raiz != NULL){
        printf(" %d ", raiz->numReserva);
        preorden(raiz->left);
        preorden(raiz->right);
    }
}

void treefree(NODO *raiz){
    if (raiz != NULL){
        treefree(raiz->left);
        treefree(raiz->right);
        free(raiz);
    }
}