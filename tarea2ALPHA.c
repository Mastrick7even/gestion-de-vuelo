

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
    struct nodoarbol *padre;
} NODO;
//----------------------Prototipo de funciones----------------------------------
NODO *crearNodo(const char *nombre, const char *destino, int numReserva, NODO *padre);
NODO *insertarNodoABB(NODO *raiz, const char *nombre, const char *destino, int numReserva, NODO *padre);
NODO *busquedaPorNumeroReserva(NODO *raiz, int numeroReserva);
NODO *encontrarMinimo(NODO *raiz);
void recorrerArbolBusquedaPorDestino(NODO *raiz, char destinoIngresado[50], int *contador);
void eliminar(NODO *raiz, int numReserva);
void eliminarNodo(NODO *raiz);
void reemplazar(NODO *raiz, NODO *nuevoNodo);
void destruirNodo(NODO *nodo);
void ordenarReservas(NODO *raiz);
void liberarMemoria(NODO *raiz);
void validacionArbolVacio();
int validarNumReservaRepetido(NODO *raiz, int numeroReserva);
//------------------------------------------------------------------------------
int main()
{
    srand(time(NULL));
    NODO *raiz = NULL;
    int opcion, numReserva, i, bandera, contadorNodos = 0;
    char nombre[50], destino[50];
    do
    {
        system("cls");
    printf("\033[0;31m");
    printf("                ^    ^\n");
    printf("               / \\  //\\\n");
    printf("     |\\___/|      /   \\//  .\\\n");
    printf("     /O  O  \\__  /    //  | \\ \\\n");
    printf("    /     /  \\/_/    //   |  \\  \\\n");
    printf("   @___@'    \\/_   //    |   \\   \\\n");
    printf("      |       \\/_ //     |    \\    \\\n");
    printf("      |        \\///      |     \\     \\\n");
    printf("     _|_ /   )  //       |      \\     _\\\n");
    printf("   '/,_ _ _/  ( ; -.    |    _ _\\.-~        .-~~~^-. \n");
    printf("   ,-{        _      `-.|.-~-.           .~         `. \n");
    printf("    '/\\      /                 ~-. _ .-~      .-~^-.  \\ \n");
    printf("       `.   {            }                   /      \\  \\ \n");
    printf("     .----~-.\\        \\-'                 .~         \\  `. \\^-.\n");
    printf("    ///.----..>    c   \\             _ -~             `.  ^-`   ^-_ \n");
    printf("      ///-._ _ _ _ _ _ _}^ - - - - ~                     ~--,   .-~ \n");
    printf("                                                            /.-'\n");
    printf("\033[0m");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("          MENU DE RESERVAS AVENTURERAS\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf(" 1. Realizar reservas de vuelo.\n");
    printf(" 2. Cancelar reservas.\n");
    printf(" 3. Buscar reserva por destino.\n");
    printf(" 4. Buscar viaje por numero de reserva.\n");
    printf(" 5. Mostrar reservas ordenadas.\n");
    printf(" 6. Salir.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf(">> ");
        scanf("%d", &opcion);
        getchar();
        switch (opcion)
        {
        case 1: // Realizar reservas de vuelo
            system("cls");
            //-----------------Nombre------------------------
            printf("Cual es tu nombre honorable aventurero?\n>> ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0'; // Eliminar el caracter "enter" al final de la entrada del usuario

            //-------------------Destino----------------------
            printf("Hacia donde emprendes tu camino, %s?\n>> ", nombre);
            fgets(destino, sizeof(destino), stdin);
            destino[strcspn(destino, "\n")] = '\0';

            //-------------------Numero reserva--------------
            system("cls");
            //numReserva = rand() % 900 + 100;
            do{
                printf("Ingresa un token de 3 digitos para guardar tu reserva.\n>> ");
                scanf("%d", &numReserva);
                if(numReserva < 100 || numReserva > 999){
                    printf("Recuerda que debes ingresar un token de 3 digitos, intenta nuevamente.\n\nPresiona para continuar...");
                    getch();
                    system("cls");
                } else{
                    bandera = validarNumReservaRepetido(raiz, numReserva);
                    if(bandera == 1){
                        printf("Numero de reserva ya existe, intenta ingresando uno distinto.\n\nPresiona para continuar...");
                        getch();
                        system("cls");
                    } else{
                        printf("Ya estas anotado! Que tengas un buen viaje, %s!", nombre);
                        getch();
                    }
                }  
            }while((numReserva < 100 || numReserva > 1000) || bandera == 1); //Condicion para que el token solo sea de 3 digitos
            
            // Insertamos el nuevo nodo al arbol
            raiz = insertarNodoABB(raiz, nombre, destino, numReserva, NULL);
            contadorNodos++;
            break;
        case 2: // Cancelar reservas
            system("cls");
            if(raiz == NULL){
                validacionArbolVacio(raiz);
            }
            if(contadorNodos == 1){ //Condicional para borrar si solo queda un nodo en todo el arbol
                liberarMemoria(raiz);
                contadorNodos--;
                raiz = NULL;


                
            }
            else{
                printf("Digite el numero de reserva para gestionar la cancelacion del viaje.\n>> ");
                scanf("%d", &numReserva);
                eliminar(raiz, numReserva);
                contadorNodos--;
                getch();
            }
            break;
        case 3: // Buscar reserva por destino
            system("cls");
            if(raiz == NULL){
                validacionArbolVacio(raiz);
            }
            else{
                printf("Ingresa el destino para hacer una busqueda y comprobar si hay reservas hechas.\n>> ");
                fgets(destino, sizeof(destino), stdin);
                destino[strcspn(destino, "\n")] = '\0';

                // Convertir destino ingresado a mayusculas para hacer una mejor busqueda
                for (i = 0; destino[i] != '\0'; i++)
                {
                    destino[i] = toupper(destino[i]);
                }
                printf("Reservas que viajan con destino a: %s\n\n", destino);

                int contador = 0;
                recorrerArbolBusquedaPorDestino(raiz, destino, &contador);
                if (contador == 0)
                {
                    printf("\nNo existen reservas que viajan a ese destino.");
                }
                else
                {
                    printf("Busqueda exitosa.");
                }
                getch();
            }
            break;
        case 4: // Buscar por numero de reserva.
            system("cls");
            if(raiz == NULL){
                validacionArbolVacio(raiz);
            }
            else{
                int numeroReserva, bool;
                printf("Ingrese un numero de reserva para buscar si existe un viaje asociado.\n>> ");
                scanf("%d", &numeroReserva);
                bool = busquedaPorNumeroReserva(raiz, numeroReserva);
                if(bool == 0){

                } else {

                }
                getch();
            }
            
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
NODO *crearNodo(const char *nombre, const char *destino, int numReserva, NODO *padre)
{
    NODO *nuevo_nodo = (NODO *)malloc(sizeof(NODO));
    //------verificar si la asignación de memoria fue exitosa-----
    if (nuevo_nodo == NULL)
    {
        printf("Error al asignar memoria para el nuevo nodo.\n");
        return NULL;
    }
    nuevo_nodo->numReserva = numReserva;
    strcpy(nuevo_nodo->nombre, nombre);
    strcpy(nuevo_nodo->destino, destino);
    nuevo_nodo->left = NULL;
    nuevo_nodo->right = NULL;
    nuevo_nodo->padre = padre;

    return nuevo_nodo;
}

NODO *insertarNodoABB(NODO *raiz, const char *nombre, const char *destino, int numReserva, NODO *padre)
{
    // Caso base: si el nodo actual es NULL, significa que hemos encontrado el lugar.
    if (raiz == NULL)
    {
        return crearNodo(nombre, destino, numReserva, padre);
    }

    // Comparar el número de reserva del nuevo nodo con el número de reserva del nodo actual.
    if (numReserva < raiz->numReserva)
    {
        raiz->left = insertarNodoABB(raiz->left, nombre, destino, numReserva, raiz); // Llamar recursivamente al subárbol izquierdo
    }
    else if (numReserva > raiz->numReserva)
    {
        raiz->right = insertarNodoABB(raiz->right, nombre, destino, numReserva, raiz); // Llamar recursivamente al subárbol derecho
    }
    return raiz; // Retornar el puntero al nodo actual (sin cambios)
}

void recorrerArbolBusquedaPorDestino(NODO *raiz, char destinoIngresado[50], int *contador)
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
            printf("+---------------------------+\n");
            printf("| Nombre del aventurero: %s. |\n", raiz->nombre);
            printf("| N%c de reserva: %d.          |\n", 167, raiz->numReserva);
            printf("+---------------------------+\n\n");
            (*contador)++; // Aumentar el valor del contador en uno (puntero), dado que es una funcion void
        }
        recorrerArbolBusquedaPorDestino(raiz->left, destinoIngresado, contador);
        recorrerArbolBusquedaPorDestino(raiz->right, destinoIngresado, contador);
    }
}

NODO *busquedaPorNumeroReserva(NODO *raiz, int numeroReserva)
{
    if (raiz == NULL)
    {
        printf("No existen viajes asociados al numero de reserva ingresado.\n\n");
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
    else
    {
        printf("Busqueda existosa, datos de la reserva a continuacion.\n\n");
        printf("Nombre aventurero: %s.\n", raiz->nombre);
        printf("Destino: %s.\n\n", raiz->destino);
        return TRUE;
    }
}

int validarNumReservaRepetido(NODO *raiz, int numeroReserva)
{
    if (raiz == NULL)
    {
        return FALSE;
    }
    else if (numeroReserva > raiz->numReserva)
    {
        return validarNumReservaRepetido(raiz->right, numeroReserva);
    }
    else if (numeroReserva < raiz->numReserva)
    {
        return validarNumReservaRepetido(raiz->left, numeroReserva);
    }
    else
    {
        return TRUE;
    }
}

void eliminar(NODO *raiz, int numReserva)
{
    if (raiz == NULL)
    {
        printf("No existen reservas asociadas a su busqueda.");
        return;
    }
    else if (numReserva > raiz->numReserva)
    {
        return eliminar(raiz->right, numReserva);
    }
    else if (numReserva < raiz->numReserva)
    {
        return eliminar(raiz->left, numReserva);
    }
    else
    {
        eliminarNodo(raiz);
        printf("\nReserva cancelada.");
    }
}

// Para reemplazar un nodo por otro
void reemplazar(NODO *raiz, NODO *nuevoNodo)
{
    if (raiz->padre != NULL)
    { // Hay que asignarle su nuevo hijo al raiz->padre
        if (raiz->numReserva == raiz->padre->left->numReserva)
        {
            raiz->padre->left = nuevoNodo;
        } // para cuando el nodo tenga un hijo izquierdo
        else if (raiz->numReserva == raiz->padre->right->numReserva)
        {
            raiz->padre->right = nuevoNodo;
        } // para cuando el nodo tenga un hijo derecho
    }
    if (nuevoNodo != NULL)
    { // Hay que asignarle su nuevo padre
        nuevoNodo->padre = raiz->padre;
    }
}

// Destruir NODO
void destruirNodo(NODO *nodo)
{
    nodo->left = NULL;
    nodo->right = NULL;
    free(nodo);
}

// Eliminar el nodo encontrado
void eliminarNodo(NODO *nodoEliminar)
{
    // caso eliminar nodos con dos hijos
    if ((nodoEliminar->left != NULL) && (nodoEliminar->right != NULL))
    {
        NODO *menor = encontrarMinimo(nodoEliminar->right);
        nodoEliminar->numReserva = menor->numReserva;
        eliminarNodo(menor);
    }
    
    else if (nodoEliminar->left != NULL)// caso eliminar nodos con un solo hijo por izquierda
    {
        reemplazar(nodoEliminar, nodoEliminar->left);
        destruirNodo(nodoEliminar);
        
    }
    else if (nodoEliminar->right != NULL)// caso eliminar nodos con un solo hijo por derecha
    {
        reemplazar(nodoEliminar, nodoEliminar->right);
        destruirNodo(nodoEliminar);
    }
    else
    { // caso eliminar nodos hoja
        reemplazar(nodoEliminar, NULL);
        destruirNodo(nodoEliminar);
    }
}

// Funcion para determinar el nodo mas a la izquierda posible (predecesor)
NODO *encontrarMinimo(NODO *raiz)
{
    if (raiz == NULL)// si el arbol esta vacio
    {                
        return NULL; // retorno nulo
    }
    if (raiz->left)// si tiene hijo izquierdo
    {                                       
        return encontrarMinimo(raiz->left); // bajamos hasta el hijo mas izquierdo posible
    }
    else
    {
        return raiz;
    }
}

void validacionArbolVacio(){
    system("cls");
    printf("No existen reservas generadas recientemente :(");
    getch();
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
