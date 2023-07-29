#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct nodoarbol
{
    int numReserva;
    char nombre[50];
    char destino[50];
    struct nodoarbol *left;
    struct nodoarbol *right;
} NODO;
//----------------------Prototipo de funciones----------------------------------
NODO *crearArbol(char nombre[50], char destino[50], int numReserva);
NODO *crearNuevoNodo(NODO *raiz, char nombre[50], char destino[50], int numReserva);
NODO *insertarNodoABB(NODO *raiz, NODO *nuevoNodo);
int recorrerArbolBusquedaPorDestino(NODO *raiz, char destinoIngresado[50], int *contador);
void busquedaPorNumeroReserva(NODO *raiz, int numeroReserva);
void busquedaPorDestino(NODO *raiz, char destino[50]);
void ordenarReservas(NODO *raiz);
void liberarMemoria(NODO *raiz);
//------------------------------------------------------------------------------
int main()
{
    NODO *raiz = NULL;
    srand(time(NULL));
    int opcion, numReserva, i;
    char nombre[50], destino[50];
    do
    {
        system("cls");
        printf("Selecciones una accion a realizar: \n");
        printf("1. Realizar reservas de vuelo.\n");
        printf("2. Cancelar reservas.\n");
        printf("3. Buscar reserva por destino\n");
        printf("4. Buscar por numero de reserva.\n");
        printf("5. Mostrar reservas ordenadas.\n");
        printf("6. Salir.\n");
        printf(">> ");
        scanf("%d", &opcion);
        getchar();
        switch (opcion)
        {
        case 1: // Realizar reservas de vuelo
            if (raiz == NULL)
            {
                system("cls");
                //-----------------Nombre------------------------
                printf("Cual es tu nombre honorable aventurero?\n>> ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = '\0';

                //-------------------Destino----------------------
                printf("Hacia donde emprendes tu camino, %s?\n>> ", nombre);
                fgets(destino, sizeof(destino), stdin);
                destino[strcspn(destino, "\n")] = '\0';

                //-------------------Numero reserva--------------
                numReserva = rand() % 900 + 100;
                system("cls");
                printf("Ya estas anotado! Tu numero de reserva es el %d.\nQue tengas un buen viaje, %s!", numReserva, nombre);
                getch();
                raiz = crearArbol(nombre, destino, numReserva);
            }
            else
            { // Insertamos nuevos nodos
                system("cls");
                //-----------------Nombre------------------------
                printf("Cual es tu nombre honorable aventurero?\n>> ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = '\0';

                //-------------------Destino----------------------
                printf("Hacia donde emprendes tu viaje, %s?\n>> ", nombre);
                fgets(destino, sizeof(destino), stdin);
                destino[strcspn(destino, "\n")] = '\0';

                //-------------------Numero reserva--------------
                numReserva = rand() % 900 + 100;
                system("cls");
                printf("Ya estas anotado! Tu numero de reserva es el %d.\nQue tengas un buen viaje, aventurero!", numReserva);
                getch();
                crearNuevoNodo(raiz, nombre, destino, numReserva);
            }
            break;
        case 2: // Cancelar reservas
            break;
        case 3: // Buscar reserva por destino
            system("cls");
            printf("Ingresa el destino para hacer una busqueda y comprobar si hay reservas hechas.\n>> ");
            fgets(destino, sizeof(destino), stdin);
            destino[strcspn(destino, "\n")] = '\0';

            // Convertir destino ingresado a mayusculas para hacer una mejor busqueda
            for (i = 0; destino[i] != '\0'; i++)
            {
                destino[i] = toupper(destino[i]);
            }
            printf("Reservas que viajan con destino a: %s\n\n", destino);
            busquedaPorDestino(raiz, destino);
            getch();
            break;
        case 4: // Buscar por numero de reserva.
            system("cls");
            int numeroReserva;
            printf("Ingrese un numero de reserva para buscar si existe un viaje asociado.\n>> ");
            scanf("%d", &numReserva);
            void busquedaPorNumeroReserva(NODO * raiz, int numeroReserva);
            break;
        case 5: // Mostrar reservas ordenadas
            if (raiz == NULL)
            {
                system("cls");
                printf("No existen reservas generadas recientemente :(");
                getch();
            }
            else
            {
                printf("\nLas reservas ordenadas ascendentemente: ");
                ordenarReservas(raiz);
                getch();
            }
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
    // LIBERACION DE MEMORIA DEL ARBOL.
    liberarMemoria(raiz);
    return 0;
}

//---------------------------------------------------------------FUNCIONES----------------------------------------------------------------------------------------------------
void busquedaPorNumeroReserva(NODO *raiz, int numeroReserva)
{
    if (raiz == NULL)
    {
        printf("Arbol vacio");
        return FALSE;
    }
    else if (numeroReserva > raiz->numReserva)
    {
        return busquedaPorNumeroReserva(raiz->right, numeroReserva);
    }
    else if (numeroReserva < raiz->numReserva)
    {
        return busquedaPorNumeroReserva(raiz->left, numeroReserva);
    }
    else if (numeroReserva == raiz->numReserva)
    {
        printf("Busqueda existosa, datos de la reserva a continuacion.\n\n");
        printf("Nombre aventurero: %s.\n", raiz->nombre);
        printf("Destino: %s.\n\n", raiz->destino);
    }
    else
    {
        printf("No existen viajes asociados al numero de reserva ingresado.\n\n");
    }
}

NODO *crearArbol(char nombre[50], char destino[50], int numReserva)
{
    NODO *raiz = (NODO *)malloc(sizeof(NODO));
    //------verificar si la asignación de memoria fue exitosa-----
    if (raiz == NULL)
    {
        printf("Error al asignar memoria para el nuevo nodo.\n");
        return raiz;
    }
    strcpy(raiz->nombre, nombre);
    strcpy(raiz->destino, destino);
    raiz->numReserva = numReserva;
    raiz->left = NULL;
    raiz->right = NULL;
    return raiz;
}

NODO *insertarNodoABB(NODO *raiz, NODO *nuevoNodo)
{
    // Caso base: si el nodo actual es NULL, significa que hemos encontrado el lugar.
    if (raiz == NULL)
    {
        return nuevoNodo; // para insertar el nuevo nodo.
    }

    // Comparar el número de reserva del nuevo nodo con el número de reserva del nodo actual.
    if (nuevoNodo->numReserva < raiz->numReserva)
    {
        raiz->left = insertarNodoABB(raiz->left, nuevoNodo); // Llamar recursivamente al subárbol izquierdo
    }
    else if (nuevoNodo->numReserva > raiz->numReserva)
    {
        raiz->right = insertarNodoABB(raiz->right, nuevoNodo); // Llamar recursivamente al subárbol derecho
    }
    return raiz; // Retornar el puntero al nodo actual (sin cambios)
}

NODO *crearNuevoNodo(NODO *raiz, char nombre[50], char destino[50], int numReserva)
{
    NODO *nuevoNodo = (NODO *)malloc(sizeof(NODO));
    //------verificar si la asignación de memoria fue exitosa-----
    if (nuevoNodo == NULL)
    {
        printf("Error al asignar memoria para el nuevo nodo.\n");
        return raiz;
    }
    strcpy(nuevoNodo->nombre, nombre);
    strcpy(nuevoNodo->destino, destino);
    nuevoNodo->numReserva = numReserva;
    nuevoNodo->left = NULL;
    nuevoNodo->right = NULL;
    //--------------------ABB------------------------
    return insertarNodoABB(raiz, nuevoNodo);
}

void busquedaPorDestino(NODO *raiz, char destino[50])
{
    int contador = 0;
    if (raiz == NULL)
    {
        printf("No existen viajes reservados.");
    }
    recorrerArbolBusquedaPorDestino(raiz, destino, &contador);
    if (contador == 0)
    {
        printf("\nNo existen reservas que viajan a ese destino.");
    }
    else
    {
        printf("Busqueda exitosa.");
    }
}
int recorrerArbolBusquedaPorDestino(NODO *raiz, char destinoIngresado[50], int *contador)
{
    int i;
    char copiaTemporal[50] = ""; // Inicializar el string vacio
    if (raiz != NULL)
    {
        for (i = 0; raiz->destino[i] != '\0'; i++)
        {
            copiaTemporal[i] = toupper(raiz->destino[i]);
        }
        if (strcmp(copiaTemporal, destinoIngresado) == 0)
        {
            printf("Nombre aventurero: %s.\n", raiz->nombre);
            printf("N%c de reserva: %d.\n\n", 167, raiz->numReserva);
            (*contador)++; // Aumentar el valor del contador en uno (puntero), dado que es una funcion void
        }
        recorrerArbolBusquedaPorDestino(raiz->left, destinoIngresado, contador);
        recorrerArbolBusquedaPorDestino(raiz->right, destinoIngresado, contador);
    }
}

// Es lo mismo que ordenar el arbol de la forma INORDEN
void ordenarReservas(NODO *raiz)
{
    if (raiz != NULL)
    {
        ordenarReservas(raiz->left);
        printf(" %d ", raiz->numReserva);
        ordenarReservas(raiz->right);
    }
}

void liberarMemoria(NODO *raiz)
{
    if (raiz != NULL)
    {
        liberarMemoria(raiz->left);
        liberarMemoria(raiz->right);
        free(raiz);
    }
}
