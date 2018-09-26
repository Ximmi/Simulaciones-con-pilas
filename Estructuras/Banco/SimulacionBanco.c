/*  

    Versión: 1.6

    El programa recibirá 5 parametros núméricos enteros que serán en el siguiente orden
    -El número de cajeros disponibles: Debe ser entero entre 0 y 10 de lo contrario arrojará un error
    -La frecuencia con la que los cajeros atenderán a los clientes en ms
    -La frecuencia con la que llegan los clientes
    -Las frecuencias con las que llegan los usuarios
    -La frecuencia con la que llegan los clientes preferentes
    Todas las frecuencias deberan ser múltiplos de 10 o arrojará un error y detendrá el programa

    Salida: Una animación en gráficos de consola que representa la llegada y la etención de los clintes usuarios y
    preferentes en sus respectivas filas

    Compilación: gcc -o SimulacionBanco.c (TADColaDin/TADColaEst/TADColaEstCir).c PresentacionWin.c
    */


#include "presentacion.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
//#include "TADColaDin.h"
#include "TADColaEst.h"

#define ALTO 40
#define ANCHO 100
#define MARCO 178

int main()
{
	BorrarPantalla();
    printf("\n\n***Simulacion de un Banco***\n\n\n");

    //******************************************************************************************************

    //En esta parte del código se piden las variables indicadas en el problema
    int numCajeros, tiempoAtencion, frecClientes, frecUsuarios, frecPreferentes;

    printf("--Ingrese el numero de cajeros disponibles:    ");
    scanf("%d", &numCajeros);
    if (numCajeros > 10 || numCajeros < 0){
        printf("\n\n\n--Error: El numero de cajeros es invalido");
        exit(1);
    }

    printf("\n--Ingrese la frecuencia con la que se atiende:     ");
    scanf("%d", &tiempoAtencion);
    if(tiempoAtencion%10 != 0){
        printf("\n\n\n--Error: El valor del tiempo es invalido");
        exit(2);
    }


    printf("\n--Ingrese la frecuencia con la que llegan los clientes del banco:    ");
    scanf("%d", &frecClientes);
    if(frecClientes%10 != 0){
        printf("\n\n\n--Error: El valor del tiempo es invalido");
        exit(3);
    }

    printf("\n--Ingrese la frecuencia con la que llegan los usuarios del banco:    ");
    scanf("%d", &frecUsuarios);
    if(frecUsuarios%10 != 0){
        printf("\n\n\n--Error: El valor del tiempo es invalido");
        exit(4);
    }

    printf("\n--Ingrese la frecuencia con la que llegan los clientes preferentes del banco:    ");
    scanf("%d", &frecPreferentes);
    if(frecPreferentes%10 != 0){
        printf("\n\n\n--Error: El valor del tiempo es invalido");
        exit(5);
    }

    //******************************************************************************************************
    //Esta parte imprime todos los elementos estáticos de la interfaz gráfica

    BorrarPantalla();

    int filas, columnas;

    for (filas = 0; filas <= ALTO; filas++)
    {
        MoverCursor(0, filas);
        printf("%c", MARCO);
        MoverCursor(ANCHO, filas);
        printf("%c", MARCO);
    }

    for (columnas = 0; columnas <= ANCHO; columnas++)
    {
        MoverCursor(columnas, 0);
        printf("%c", MARCO);
        MoverCursor(columnas, ALTO);
        printf("%c", MARCO);
    }

    MoverCursor(2, 2);
    printf("Frecuencia de Atencion: cada %d ms", tiempoAtencion);

    MoverCursor(40, 2);
    printf("Tiempo:");

    MoverCursor(2, 6);
    printf("USUARIOS");

    MoverCursor(40, 6);
    printf("Frecuencia: cada %d ms", frecUsuarios);

    MoverCursor(80, 6);
    printf("Tamano:");

    MoverCursor(2, 13);
    printf("CLIENTES");

    MoverCursor(40, 13);
    printf("Frecuencia: cada %d ms", frecClientes);

    MoverCursor(80, 13);
    printf("Tamano:");

    MoverCursor(2, 20);
    printf("CLIENTES PREFERENTES");

    MoverCursor(40, 20);
    printf("Frecuencia: cada %d ms", frecPreferentes);

    MoverCursor(80, 20);
    printf("Tamano:");

    int l;

    for (l = 0; l <= 90; l++)
    {
        MoverCursor(2 + l, 7);
        printf("%c", 205);
        MoverCursor(2 + l, 9);
        printf("%c", 205);
        if(l%6 == 0)
        {
            MoverCursor(2 + l, 8);
            printf("%c", 186);
            MoverCursor(2 + l, 22);
            printf("%c", 186);
            MoverCursor(2 + l, 15);
            printf("%c", 186);
        }

        MoverCursor(2 + l, 14);
        printf("%c", 205);
        MoverCursor(2 + l, 16);
        printf("%c", 205);

        MoverCursor(2 + l, 21);
        printf("%c", 205);
        MoverCursor(2 + l, 23);
        printf("%c", 205);

        MoverCursor(2 + l, 34);
        printf("%c", 205);
        MoverCursor(2 + l, 38);
        printf("%c", 205);

        if (l%9 == 0)
        {
            MoverCursor(2 + l, 35);
            printf("%c", 186);
            MoverCursor(2 + l, 36);
            printf("%c", 186);
            MoverCursor(2 + l, 37);
            printf("%c", 186);

            if (l != 90)
            {
                MoverCursor(3+l, 36);
                printf("Caja %d", (l/9)+ 1);
            }

        }
    }

    MoverCursor(94,8);
    printf("->");

    MoverCursor(94,15);
    printf("->");

    MoverCursor(94,22);
    printf("->");

    for (l = (10 - numCajeros); l < 10; l++)
        {
            MoverCursor(3 + 9*l, 36);
            printf("Cerrado");
        }

    //******************************************************************************************************

    cola filaClientes, filaUsuarios, filaPreferentes;   //Estas pilas actuan como si fueran las distintas filas por categoría
    elemento cliente;

    Initialize(&filaClientes);
    Initialize(&filaUsuarios);
    Initialize(&filaPreferentes);

    //******************************************************************************************************
    //En esta parte del código se declara un while que correrá cada 10 ms

    long int tiempo = 0;    //contará cuantos ms han pasado
    long int numCliente = 1;    //contará el número total de clientes que han llegado y les asignará un numero segun su llegada
    long int numUsuario = 1;
    long int numPreferente = 1;

    int contPreferentes = 0;    //Contará cuandos clientes preferentes han pasado desde que el último cliente paso
    int contClientes = 0;   //Contará cuantos clientes y clientes preferentes pasaron desde el ultimo usuario

    elemento cajaAtendiendo[numCajeros];    //Este es un array que representa el cliente que se esta atendiendo en cierta caja en un
                                            //lapso determinado de tiempo
    cliente.nc = 0;
    cliente.t = 'N';

    for (l = 0; l < numCajeros; l++)
    {
        cajaAtendiendo[l] = cliente;
    }

    while (1)
    {
        Sleep(10);
        tiempo += 10;

        //******************************************************************************************************
        //Esta parte define el codigo que se encargara de la llegada de los clientes preferentes al banco

        if(tiempo%frecPreferentes == 0)
        {
            cliente.nc = numPreferente;
            numPreferente++;

            cliente.t = 'P';

            Queue(&filaPreferentes, cliente);
        }

        //******************************************************************************************************
        //Esta parte define el codigo que se encargara de la llegada de los clientes al banco

        if(tiempo%frecClientes == 0)
        {
            cliente.nc = numCliente;
            numCliente++;

            cliente.t = 'C';

            Queue(&filaClientes, cliente);
        }

        //******************************************************************************************************
        //Esta parte define el codigo que se encargara de la llegada de los usuarios al banco

        if(tiempo%frecUsuarios == 0)
        {
            cliente.nc = numUsuario;
            numUsuario++;

            cliente.t = 'U';

            Queue(&filaUsuarios, cliente);
        }

        //******************************************************************************************************
        //Esta parte define el codigo que se encargara del algoritmo de atención a los clientes

        if(tiempo%tiempoAtencion == 0)
        {
            if (numCajeros != 0)
            {

                //******************************************************************************************************
                //Hice la separación del codigo de cuando solo son una caja o son más por que cuando se trata de una sola caja,
                //no es posible para todos los casos, no dejar de atender a los clientes, pero no dejar pasar 5 clientes sin pasar
                //al menos un usuario, además de que en otros no permitiria que pasaran los preferentes

                if (numCajeros > 1)
                {
                    //Se declaró en esta parte que la fila numero 1 siempre le de prioridad a los clientes para cumplir con
                    //no dejar de atenderlos, sin embargo, cuando no hay clientes, atendera primero a preferentes y luego a
                    //usuarios respetando la regla de 1 usuario por cada 5 clientes

                    if(!Empty(&filaClientes))
                    {
                        cajaAtendiendo[0] = Dequeue(&filaClientes);
                        contClientes++;
                    }

                    else if((contClientes >= 5 && !Empty(&filaUsuarios)) || (Empty(&filaPreferentes) && !Empty(&filaUsuarios)))
                    {
                        cajaAtendiendo[0] = Dequeue(&filaUsuarios);
                        contClientes = 0;
                    }

                    else if(!Empty(&filaPreferentes))
                    {
                        cajaAtendiendo[0] = Dequeue(&filaPreferentes);
                        contClientes++;
                    }

                    //******************************************************************************************************
                    //En esta parte se define el comportamiento del resto de las cajas que seran dependiendo del caso
                    //de la 2 a la 10

                    int i;

                    for(i = 1; i < numCajeros; i++)
                    {
                        if (contClientes >= 5 && !Empty(&filaUsuarios))
                        {
                            cajaAtendiendo[i] = Dequeue(&filaUsuarios);
                            contClientes = 0;
                        }

                        else if(!Empty(&filaPreferentes))
                        {
                            cajaAtendiendo[i] = Dequeue(&filaPreferentes);
                            contClientes++;
                        }

                        else if(!Empty(&filaClientes))
                        {
                            cajaAtendiendo[i] = Dequeue(&filaClientes);
                            contClientes++;
                        }

                        else if(!Empty(&filaUsuarios))
                        {
                            cajaAtendiendo[i] = Dequeue(&filaUsuarios);
                            contClientes = 0;
                        }
                    }
                }

                //******************************************************************************************************
                //Esta parte define cuando solo hay un cajero disponible, como se mencionó antes es imposible para algunas
                //convinaciones de valores respetar las condiciones dadas, por lo que creé un algoritmo que se ajuste lo más posible

                else
                {
                    if (contClientes >= 5 && !Empty(&filaUsuarios))
                    {
                        cajaAtendiendo[0] = Dequeue(&filaUsuarios);
                        contClientes = 0;
                    }
                    else
                    {
                        if(contPreferentes >= 2 && !Empty(&filaClientes))
                        {
                            cajaAtendiendo[0] = Dequeue(&filaClientes);
                            contPreferentes = 0;
                            contClientes++;
                        }
                        else
                        {
                            if(!Empty(&filaPreferentes))
                            {
                                cajaAtendiendo[0] = Dequeue(&filaPreferentes);
                                contClientes++;
                                contPreferentes++;
                            }
                            else if (!Empty(&filaClientes))
                            {
                                cajaAtendiendo[0] = Dequeue(&filaClientes);
                                contClientes++;
                                contPreferentes = 0;
                            }
                            else if (!Empty(&filaUsuarios))
                            {
                                cajaAtendiendo[0] = Dequeue(&filaUsuarios);
                                contClientes = 0;
                            }
                        }
                    }
                }
            }
        }

        //******************************************************************************************************
        //En esta parte del codigo se encuentra la parte del algoritmo que va a imprimir el estado actual de las filas
        //y las cajas en pantalla con los gráficos de consola

        MoverCursor(48, 2);
        printf("%d ms", tiempo);

        for(l = 0; l < 15; l++)
        {
            MoverCursor(87 - l*6, 8);
            printf("     ");
            MoverCursor(87 - l*6, 15);
            printf("     ");
            MoverCursor(87 - l*6, 22);
            printf("     ");
        }

        MoverCursor(88, 6);
        printf("%d", Size(&filaUsuarios));

        MoverCursor(88, 13);
        printf("%d", Size(&filaClientes));

        MoverCursor(88, 20);
        printf("%d", Size(&filaPreferentes));

        for(l = 0; l < 15; l++)
        {
            if (Size(&filaUsuarios) - 1 >= l)
            {
                MoverCursor(87 - l*6, 8);
                printf("%c%d", Element(&filaUsuarios, l+1).t, Element(&filaUsuarios, l+1).nc);
            }
        }

        for(l = 0; l < 15; l++)
        {
            if (Size(&filaClientes) - 1 >= l)
            {
                MoverCursor(87 - l*6, 15);
                printf("%c%d", Element(&filaClientes, l+1).t, Element(&filaClientes, l+1).nc);
            }
        }

        for(l = 0; l < 15; l++)
        {
            if (Size(&filaPreferentes) - 1 >= l)
            {
                MoverCursor(87 - l*6, 22);
                printf("%c%d", Element(&filaPreferentes, l+1).t, Element(&filaPreferentes, l+1).nc);
            }
        }

        for (l = 0; l < numCajeros; l++)
        {
            MoverCursor(3 + 9*l, 33);
            printf("         ");

            MoverCursor(3 + 9*l, 33);
            if (cajaAtendiendo[l].t != 'N')
            {
                printf("%c%d", cajaAtendiendo[l].t, cajaAtendiendo[l].nc);
            }
            else
            {
                printf("Vacio");
            }
        }

        MoverCursor(0, 41);
        EsperarMiliSeg(1000);
    }

    //******************************************************************************************************

    return 0;
}
