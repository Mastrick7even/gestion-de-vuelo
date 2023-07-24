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
                raiz = crearArbol();
            }
            else
            { // Insertamos nuevos nodos
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
    printf("\n\nPreorden: ");
    preorden(raiz);
    getch();
    treefree(raiz); // LIBERACION DE MEMORIA DEL ARBOL.
    return 0;
}

NODO *crearArbol()
{
    //-----------------Variables-------------
    NODO *raiz = (NODO *)malloc(sizeof(NODO));
    raiz->left = NULL;
    raiz->right = NULL;
    //-----------------Nombre------------------------
    printf("Cual es tu nombre honorable aventurero? ");
    // fflush(stdin);
    fgets(raiz->nombre, sizeof(raiz->nombre), stdin);
    raiz->nombre[strcspn(raiz->nombre, "\n")] = '\0'; // Sirve para eliminar el salto de línea final si existe

    //-------------------Destino----------------------
    printf("Hacia donde emprendes tu viaje, %s", raiz->nombre);
    // fflush(stdin);
    fgets(raiz->destino, sizeof(raiz->destino), stdin);
    raiz->destino[strcspn(raiz->destino, "\n")] = '\0';

    //-------------------Numero reserva--------------
    raiz->numReserva = rand() % 90 + 10;
    printf("Ya estas anotado! Que tengas un buen viaje, aventurero!");
    return raiz;
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

    //-----------------Nombre------------------------
    printf("Cual es tu nombre honorable aventurero? ");
    fgets(nuevoNodo->nombre, sizeof(nuevoNodo->nombre), stdin);
    nuevoNodo->nombre[strcspn(nuevoNodo->nombre, '\n')] = '\0';

    //-------------------Destino----------------------
    printf("Hacia donde emprendes tu viaje, %s", nuevoNodo->nombre);
    fgets(nuevoNodo->destino, sizeof(nuevoNodo->destino), stdin);
    nuevoNodo->destino[strcspn(nuevoNodo->destino, '\n')] = '\0';

    //-------------------Numero reserva--------------
    nuevoNodo->numReserva = rand() % 90 + 10;
    printf("Ya estas anotado! Que tengas un buen viaje, aventurero!");

    //--------------------ABB------------------------
    if (nuevoNodo->numReserva < raiz->numReserva)
    {
        raiz->left = insertarNodos(raiz->left);
    }
    else if (nuevoNodo->numReserva > raiz->numReserva)
    {
        raiz->right = insertarNodos(raiz->right);
    }
    return raiz;
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