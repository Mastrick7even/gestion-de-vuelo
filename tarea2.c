#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

typedef struct nodoarbol{
    int numReserva;
    char nombre[50];
    char destino[50];
    struct nodoarbol *left;
    struct nodoarbol *right;
} NODO;
//----------------------Prototipo de funciones----------------------------------
NODO *crearNodo(const char *nombre, const char *destino, int numReserva);
NODO *insertarNodoABB(NODO *raiz, const char *nombre, const char *destino, int numReserva);
NODO *eliminarNodoABB(NODO *raiz, int numeroReserva);
NODO *busquedaPorNumeroReserva2(NODO *raiz, int numeroReserva);
int validarNumReservaRepetido(NODO *raiz, int numeroReserva);
void recorrerArbolBusquedaPorDestino(NODO *raiz, char destinoIngresado[50], int *contador);
void ordenarReservas(NODO *raiz);
void liberarMemoria(NODO *raiz);
void validacionArbolVacio();
void menu();
void dragon1();
void dragonDespedida();
void dragonEliminar();
void DragonOrdenar();
void DragonBusqueda();
//------------------------------------------------------------------------------
int main(){
    srand(time(NULL));
    NODO *raiz = NULL;
    NODO *nodoEncontrado;
    int opcion, numReserva, i, bandera;
    char nombre[50], destino[50];
    do{
        menu();
        scanf("%d", &opcion);
        getchar();
        switch (opcion)
        {
        case 1: // Realizar reservas de vuelo
            system("cls");
            dragon1();
            //-----------------Nombre------------------------
            printf("\nCual es tu nombre honorable aventurero?\n>> ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0'; // Eliminar el caracter "enter" al final de la entrada del usuario

            //-------------------Destino----------------------
            printf("\nHacia donde emprendes tu camino, %s?\n>> ", nombre);
            fgets(destino, sizeof(destino), stdin);
            destino[strcspn(destino, "\n")] = '\0';

            //-------------------Numero reserva--------------
            system("cls");
            do{
                dragon1();
                printf("\nIngresa un token de 3 digitos para guardar tu reserva.\n>> ");
                scanf("%d", &numReserva);
                if(numReserva < 100 || numReserva > 999){
                    printf("Recuerda que debes ingresar un token de 3 digitos, intenta nuevamente.\n\nPresiona para continuar...");
                    getch();
                    system("cls");
                } else{
                    bandera = validarNumReservaRepetido(raiz, numReserva);
                    if(bandera == 1){
                        printf("\nNumero de reserva ya existe, intenta ingresando uno distinto.\n\nPresiona para continuar...");
                        getch();
                        system("cls");
                    } else{
                        printf("\nYa estas anotado! Que tengas un buen viaje, %s!", nombre);
                        getch();
                    }
                }  
            }while((numReserva < 100 || numReserva > 1000) || bandera == 1); //Condicion para que el token solo sea de 3 digitos
            
            // Insertamos el nuevo nodo al arbol
            raiz = insertarNodoABB(raiz, nombre, destino, numReserva);
            break;
        case 2: // Cancelar reservas
            system("cls");
            dragonEliminar();
            if (raiz == NULL){
                validacionArbolVacio(raiz);
            }
            else{
                printf("\nReservas ingresadas al sistema:\n\n");
                ordenarReservas(raiz);
                printf("Digite el numero de reserva para gestionar la cancelacion del viaje.\n>> ");
                scanf("%d", &numReserva);
                nodoEncontrado = busquedaPorNumeroReserva2(raiz, numReserva);
                if (nodoEncontrado == NULL){
                    printf("\nEl numero de reserva no existe.\n");
                }
                else
                {
                    raiz = eliminarNodoABB(raiz, numReserva);
                    system("cls");
                    dragonEliminar();
                    printf("\nReserva cancelada exitosamente.");
                }
                getch();
            }
            break;
        case 3: // Buscar reserva por destino
            system("cls");
            DragonBusqueda();
            if(raiz == NULL){
                validacionArbolVacio(raiz);
            }
            else{
                printf("\nIngresa el destino para hacer una busqueda y comprobar si hay reservas hechas.\n>> ");
                fgets(destino, sizeof(destino), stdin);
                destino[strcspn(destino, "\n")] = '\0';

                // Convertir destino ingresado a mayusculas para hacer una mejor busqueda
                for (i = 0; destino[i] != '\0'; i++){
                    destino[i] = toupper(destino[i]);
                }
                printf("\nReservas que viajan con destino a: %s\n\n", destino);

                int contador = 0;
                recorrerArbolBusquedaPorDestino(raiz, destino, &contador);
                if (contador == 0){
                    printf("\nNo existen reservas que viajan a ese destino.");
                }
                else{
                    printf("Busqueda exitosa.");
                }
                getch();
            }
            break;
        case 4: // Buscar por numero de reserva.
            system("cls");
            DragonBusqueda();
            if(raiz == NULL){
                validacionArbolVacio(raiz);
            }
            else{
                int numeroReserva;
                printf("\nIngrese un numero de reserva para buscar si existe un viaje asociado.\n>> ");
                scanf("%d", &numeroReserva);
                nodoEncontrado = busquedaPorNumeroReserva2(raiz, numeroReserva);
                if (nodoEncontrado == NULL){
                    printf("\nEl numero de reserva no existe.\n");
                }
                else{
                    printf("\nBusqueda existosa, datos de la reserva N%c%d a continuacion.\n", 167, numReserva);
                    printf("+---------------------------------------------------------------+\n");
                    printf("| Nombre aventurero: %s\n", nodoEncontrado->nombre);
                    printf("| Destino: %s\n", nodoEncontrado->destino);
                    printf("+---------------------------------------------------------------+\n\n");
                }
                printf("Presione una tecla para continuar...");
                getch();
            }
            break;
        case 5: // Mostrar reservas ordenadas
            if (raiz == NULL){
                validacionArbolVacio(raiz);
            }
            else{
                system("cls");
                DragonOrdenar();
                printf("\nLas reservas ordenadas ascendentemente: \n\n");
                ordenarReservas(raiz);
                getch();
            }
            break;
        case 6:
            system("cls");
            dragonDespedida();
            printf("\nSaliendo del programa, gracias por su preferencia <3\nMucha suerte en tu camino aventurero!\n");
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
NODO *crearNodo(const char *nombre, const char *destino, int numReserva){
    NODO *nuevo_nodo = (NODO *)malloc(sizeof(NODO));
    //------verificar si la asignación de memoria fue exitosa-----
    if (nuevo_nodo == NULL){
        printf("Error al asignar memoria para el nuevo nodo.\n");
        return NULL;
    }
    nuevo_nodo->numReserva = numReserva;
    strcpy(nuevo_nodo->nombre, nombre);
    strcpy(nuevo_nodo->destino, destino);
    nuevo_nodo->left = NULL;
    nuevo_nodo->right = NULL;

    return nuevo_nodo;
}

NODO *insertarNodoABB(NODO *raiz, const char *nombre, const char *destino, int numReserva){
    // Caso base: si el nodo actual es NULL, significa que hemos encontrado el lugar.
    if (raiz == NULL){
        return crearNodo(nombre, destino, numReserva);
    }

    // Comparar el número de reserva del nuevo nodo con el número de reserva del nodo actual.
    if (numReserva < raiz->numReserva){
        raiz->left = insertarNodoABB(raiz->left, nombre, destino, numReserva); // Llamar recursivamente al subárbol izquierdo
    }
    else if (numReserva > raiz->numReserva){
        raiz->right = insertarNodoABB(raiz->right, nombre, destino, numReserva); // Llamar recursivamente al subárbol derecho
    }
    return raiz; // Retornar el puntero al nodo actual (sin cambios)
}

NODO *eliminarNodoABB(NODO *raiz, int numeroReserva){
    if (raiz == NULL){
        return NULL; // El nodo no existe
    }

    // Buscar el nodo con el número de reserva
    if (numeroReserva < raiz->numReserva){
        raiz->left = eliminarNodoABB(raiz->left, numeroReserva);
    }
    else if (numeroReserva > raiz->numReserva){
        raiz->right = eliminarNodoABB(raiz->right, numeroReserva);
    }
    else{
        // Caso 1: El nodo es una hoja (no tiene hijos)
        if (raiz->left == NULL && raiz->right == NULL){
            free(raiz);
            return NULL;
        }
        // Caso 2: El nodo tiene solo un hijo (izquierdo o derecho)
        else if (raiz->left == NULL){
            NODO *temp = raiz->right;
            free(raiz);
            return temp;
        }
        else if (raiz->right == NULL){
            NODO *temp = raiz->left;
            free(raiz);
            return temp;
        }
        // Caso 3: El nodo tiene dos hijos
        else{
            // Encontrar el sucesor inorden (nodo con valor más pequeño en el subárbol derecho)
            NODO *sucesor = raiz->right;
            while (sucesor->left != NULL)
            {
                sucesor = sucesor->left;
            }

            // Copiar el valor del sucesor al nodo actual
            raiz->numReserva = sucesor->numReserva;
            strcpy(raiz->nombre, sucesor->nombre);
            strcpy(raiz->destino, sucesor->destino);

            // Eliminar el sucesor inorden
            raiz->right = eliminarNodoABB(raiz->right, sucesor->numReserva);
        }
    }
    return raiz;
}


void recorrerArbolBusquedaPorDestino(NODO *raiz, char destinoIngresado[50], int *contador){
    int i;
    char copiaTemporal[50] = ""; // Inicializar el string vacio
    if (raiz != NULL){
        for (i = 0; raiz->destino[i] != '\0'; i++){
            copiaTemporal[i] = toupper(raiz->destino[i]);
        }
        if (strcmp(copiaTemporal, destinoIngresado) == 0){
            printf("+---------------------------------------------+\n");
            printf("| Nombre del aventurero: %s \n", raiz->nombre);
            printf("| N%c de reserva: %d          \n", 167, raiz->numReserva);
            printf("+---------------------------------------------+\n\n");
            (*contador)++; // Aumentar el valor del contador en uno (puntero), dado que es una funcion void
        }
        recorrerArbolBusquedaPorDestino(raiz->left, destinoIngresado, contador);
        recorrerArbolBusquedaPorDestino(raiz->right, destinoIngresado, contador);
    }
}

NODO *busquedaPorNumeroReserva2(NODO *raiz, int numeroReserva){
    if (raiz == NULL){
        return NULL;
    }
    else if (numeroReserva > raiz->numReserva){
        return busquedaPorNumeroReserva2(raiz->right, numeroReserva);
    }
    else if (numeroReserva < raiz->numReserva){
        return busquedaPorNumeroReserva2(raiz->left, numeroReserva);
    }
    else{
        return raiz; // Retornar el puntero al nodo encontrado
    }
}

int validarNumReservaRepetido(NODO *raiz, int numeroReserva){
    if (raiz == NULL){
        return FALSE;
    }
    else if (numeroReserva > raiz->numReserva){
        return validarNumReservaRepetido(raiz->right, numeroReserva);
    }
    else if (numeroReserva < raiz->numReserva){
        return validarNumReservaRepetido(raiz->left, numeroReserva);
    }
    else{
        return TRUE;
    }
}

// Es lo mismo que ordenar el arbol de la forma INORDEN
void ordenarReservas(NODO *raiz){
    if (raiz != NULL)
    {
        ordenarReservas(raiz->left);
        printf("+---------------------------------------------+\n");
        printf("| N%c de reserva: %d          \n", 167, raiz->numReserva);
        printf("| Nombre del aventurero: %s \n", raiz->nombre);
        printf("| Destino: %s\n", raiz->destino);
        printf("+---------------------------------------------+\n\n");
        ordenarReservas(raiz->right);
    }
}

void liberarMemoria(NODO *raiz){
    if (raiz != NULL)
    {
        liberarMemoria(raiz->left);
        liberarMemoria(raiz->right);
        free(raiz);
    }
}
//---------------------------------ASCII ART----------------------------------------------

void validacionArbolVacio(){
    system("cls");
    printf("\033[34m                                      _   __,----'~~~~~~~~~`-----.__\n");
    printf("                                   .  .    `//====-_             ___,-' `\n");
    printf("                   -.            \\_|// .   /||\\\\  `~~~~`---.___./\n");
    printf("             ______-==.       _-~o~  \\/    |||  \\\\           _,'`\n");
    printf("       __,--'   ,=='||\\=_    ;_--~/_-'|-   |`\\   \\\\        ,'\n");
    printf("    _-'        '    |  \\\\`.   '-'~7  /-   /  ||   `\\.     /\n");
    printf("  .'    //// ||     |   \\\\ \\_    /  /-   /   ||      \   /\n");
    printf(" / ____  O-O--=     |     \\\\\\`-_/  /|- _/   ,||       \\ /\n");
    printf(",-'     ( ^ _/\\_ --_ \\     `==-/  `| \\'--===-'       _/'\n");
    printf("        /\\~-\\/  \\   `-|      /|    )-'\\~'      _,--~'\n");
    printf("       /|`/ _ \\_ \\    '-~~\\_/ |    |   `\\_   ,~             /\\\n");
    printf("      / | : U_/  /         /  \\     \\__   \\/~               `\\__\n");
    printf("      \\(__:__ \\_/      _,-' _/'\\ ,-'~____-'`-/                 ``===\\\n");
    printf("        =@=====       ((->/'    \\|||' `.     ~`-/ ,                _||\n");
    printf("       |       |                 \\_     ~\\      `^---|__i__i__\\--~'_/\n");
    printf("      /   |   |                 __-^-_    `)  \\.______________,-~'\n");
    printf("     /   /|   |                //,-'~~`__--^-  |-------~~~~~'\n");
    printf("     |  | |  |                        //,--~~`-\\\n");
    printf("     |__| |__|\n");
    printf("     /#_)  |#\\\033[0m\n");
    printf("\nNo existen reservas generadas :(");
    getch();
}

void menu(){
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
    printf("|              MENU DE RESERVAS AVENTURERAS              |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("| 1. Reservar un viaje en Dragon.                        |\n");
    printf("| 2. Cancelar reservas de viaje en Dragon.               |\n");
    printf("| 3. Buscar reserva por nombre del reino destino.        |\n");
    printf("| 4. Buscar viaje por numero de reserva.                 |\n");
    printf("| 5. Mostrar reservas ordenadas ascendentemente.         |\n");
    printf("| 6. Salir.                                              |\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf(">> ");
}

void dragon1(){
    printf("\033[32m                 ___====-_  _-====___\n");
    printf("           _--^^^#####//      \\\\#####^^^--_\n");
    printf("        _-^##########// (    ) \\\\##########^-_\n");
    printf("       -############//  |\\^^/|  \\\\############-\n");
    printf("     _/############//   (@::@)   \\\\############\\_\n");
    printf("    /#############((     \\\\//     ))#############\\\n");
    printf("   -###############\\\\    (oo)    //###############-\n");
    printf("  -#################\\\\  / VV \\  //#################-\n");
    printf(" -###################\\\\/      \\\\//###################-\n");
    printf("_#/|##########/\\######(   /\\   )######/\\##########|\\#_\n");
    printf("|/ |#/#/\\/#\\/  \\#/#\\##\\  |  |  /##/\\#/#  \\/\\#/#/#| \\|\n");
    printf("`  |/  V  V  `   V  \\#\\| |  | |/#/  V   '  V  V  \\|  '\n");
    printf("   `   `  `      `   / | |  | | \\   '      '  '   '\n");
    printf("                    (  | |  | |  )\n");
    printf("                   __\\ | |  | | /__\n");
    printf("                  (vvv(VVV)(VVV)vvv)\033[0m\n");
}

void dragonDespedida() {
    printf("\033[35m                     __/>^^^;:,       \n");
    printf("        __  __      /-.       :,/|/|  \n");
    printf("       /  \\/  \\  __/ ^         :,/ \\__\n");
    printf("      |        |(~             ;/ /  / \n");
    printf("      \\       {  `-'--._       / / ,<  ___\n");
    printf("       \\      /,__.   /=\\     /  _/  >|_'.\n");
    printf("        \\    /  `_ `--------'    __ / ',\\ \\ \n");
    printf("         \\  / ,_// ,---_____,   ,_  \\_  ,| |\n");
    printf("          \\/   `--' |=|           \\._/ ,/  |\n");
    printf("                     \\=\\            `,,/   |\n");
    printf("                      \\=\\            ||    /\n");
    printf("                       \\=\\____       |\\    \\\n");
    printf("                      / \\/    `     <__)    \\\n");
    printf("                      | |                    |\n");
    printf("                    ,__\\,\\                   /\n");
    printf("                   ,--____>    /\\.         ./\n");
    printf("                   '-__________>  \\.______/ \033[0m\n");
}

void dragonEliminar() {
    printf("\033[36m            _                                      _                   \n");
    printf("          _/(               <~\\  /~>               )\\_                 \n");
    printf("        .~   ~-.            /^-~~-^\\            .-~   ~.               \n");
    printf("     .-~        ~-._       : /~\\/~\\ :       _.-~        ~-.            \n");
    printf("  .-~               ~~--.__: \\0/\\0/ ;__,--~~               ~-.         \n");
    printf(" /                        ./\\. ^^ ./\\.                        \\        \n");
    printf(".                         |  ( )( )  |                         .       \n");
    printf("-~~--.        _.---._    /~   U``U   ~\\    _.---._        .--~~-       \n");
    printf("      ~-. .--~       ~~-|              |-~~       ~--. .-~             \n");
    printf("         ~              |  :        :  |_             ~                \n");
    printf("                        `\\,'  :  :  `./' ~~--._                        \n");
    printf("                       .(<___.'  `,___>),--.___~~-.                    \n");
    printf("                       ~ (((( ~--~ ))))      _.~  _)                   \n");
    printf("                          ~~~      ~~~/`.--~ _.--~                     \n");
    printf("                                      \\,~~~~~                           \033[0m\n");
}

void DragonOrdenar() {
    printf("\033[33m                 /           /                                               \n");
    printf("                /' .,,,,  ./                                                \n");
    printf("               /';'     ,/                                                   \n");
    printf("              / /   ,,//,`'`                                                  \n");
    printf("             ( ,, '_,  ,,,' ``                                                 \n");
    printf("             |    /@  ,,, ;\" `                                                 \n");
    printf("            /    .   ,''/' `,``                                                \n");
    printf("           /   .     ./, `,, ` ;                                               \n");
    printf("        ,./  .   ,-,',` ,,/''\\,'                                               \n");
    printf("       |   /; ./,,'`,,'' |   |                                                 \n");
    printf("       |     /   ','    /    |                                                 \n");
    printf("        \\___/'   '     |     |                                                 \n");
    printf("          `,,'  |      /     `\\                                                \n");
    printf("               /      |        ~\\                                              \n");
    printf("              '       (                                                        \n");
    printf("             :                                                                 \n");
    printf("            ; .         \\--                                                     \n");
    printf("          :   \\         ;\033[0m                                                   \n");
}

void DragonBusqueda() {
    printf("\033[32m                                                    __,\n");
    printf("                                       __...---`````_,\n");
    printf("           .-``-.     .-``-......__.-``   _.--``````  ___,\n");
    printf("          ^      :   :               -`````---````````_,\n");
    printf("          ^_      :  :....._                    _.-```\n");
    printf("           |`|-.   `.    o  ``-.__.-`````...````\n");
    printf("                `.   `...__. ,'.___.-```;:'\n");
    printf("                  `._     ; ;        .:'___,\n");
    printf("                     ````` ;        _...--`\n");
    printf("                  __..--```       -```-.\n");
    printf("         .|,|_.-``___....---```````--.._\\\n");
    printf("         `-,,--```     ..---```````--.\n");
    printf("                        `-.          ;).\n");
    printf("                           ;        ;'..)\n");
    printf(" __.-`|`-./                ;       ;).        \\.-`/8e.__\n");
    printf("__.   |   .                '      ;'..)       .  (88 8.__\n");
    printf("__:  /|\\  :_           __ ;      ;_          _: 8  )88:__\n");
    printf("   `/_|_\\'/ '-._      / /;      ;) \\     _.-' \\._/8*'\n");
    printf("          '.    ``-._/  |;     ;/   \\_.-``   ,'\n");
    printf("            `-.          \\;    ;\\         ,-'\n");
    printf("               `-._     /  ;   ; \\     ,-'\n");
    printf("                   `.__/    ;  ;  \\__,'\n");
    printf("                             ; ;).`.\n");
    printf("                              ;;'..)\n");
    printf("                               ;\033[0m\n");
}