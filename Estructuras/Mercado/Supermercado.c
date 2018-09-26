	/*
VERSION: 1.5

DESCRIPCION: Ejemplo de una atención de clientes en un supermercado 
el cual podrá cerrar sólo si has sido atendidos 100 clientes. 

COMPILACION: 
			gcc -o Supermercado Supermercado.c presentacionWin.c TADCola/TADCola(Din|Est|EstCirc).o (Si se tiene el objeto de la implementación)
			gcc -o Supermercado Supermercado.c presentacionWin.c TADCola/TADCola(Din|Est|EstCirc).c (Si se tiene el fuente de la implementación)

EJECUCION: Supermercado.exe
*/

//LIBRERIAS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include "presentacion.h"
//#include "TADColaEst.h"//EstCirc.h"
#include "TADColaDin.h"

//DEFINICION DE CONSTANTES
#define ANCHO 100             
#define ALTO  30    //Se piensa en una pantalla de 30 filas x 100 columnas
#define MARCO 176 


//PROGRAMA PRINCIPAL
int main()
{	
	BorrarPantalla();
	//Parte del código dedicada a establecer los valores de entrada para el supermercado.
	char nombre[30];
	int i, band, h;

	do
	{ 
		fflush(stdin); // Limpiar el buffer 
		printf("\n*Ingrese el nombre del supermercado:\t");
		gets(nombre);  
		i=0;
		band=0; //Variable bandera para espacios del nombre 
			
		for(; i<strlen(nombre); i++) // Recorre el nombre en busca de espacios 
		{
			if(nombre[i]==' ')
				band=band+1;   //Aumenta  cada vez que encuentra un espacio
		}
	
		if(band==0)
			printf("Felicidades :), nombre valido");
		else
			printf("ERROR:Nombre invalido :( , tiene %d espacio(s). Intentalo de nuevo!!!!",band);
	}
	while(band!=0);	// Si el numero de espacios es igual a cero, saldra del bucle 

	 	
	int numcaj; //Numero de cajeras 
	int caj; 
	int tiemcaj; // Tiempo de cajeras
	
	// Pide el numero de cajeras
	do{
		printf("\n\n*Ingrese el numero de cajeras:\t");
		scanf("%d",&numcaj);
	
		if(numcaj<=10) //El if verifica que el numero de cajeras este en un rango del 0 al 10
			printf("El numero de cajeras es %d",numcaj);
		else
			printf("ERROR: Numero de cajeras fuera de rango. Ingrese otro numero");				
	}
	while(numcaj>10);
		
	//El for imprimirá el numero de cajeras ingresado y pedirá el tiempo de atención de cada una. Con el do-while
	// se encargará de volver a pedir el tiempo en caso que sea menor a 10 ms

	for(caj=0; caj<numcaj; caj++) 
	{
		do{
			printf("\n\nIngrese el tiempo de atencion en ms para la cajera %d:\t",caj + 1);
			scanf("%d",&tiemcaj);
			if(tiemcaj%10!=0)
				printf("ERROR: el tiempo asignado a la cajera %d debe ser mayor/multiplo a 10 ms",caj);
		}
		while(tiemcaj%10!=0);
	}
		

	//Aquí el programa pedirá el tiempo de llegada de los clientes. El do-while se encargará de pedir el tiempo de nuevo
	//si es que es menor a 10 ms.
	int tclien;
	do{
		printf("\n\nIngrese el tiempo de llegada de los clientes:\t");
		scanf("%d",&tclien);
		if(tclien%10!=0)
			printf("ERROR: el tiempo asignado a la llegada de clientes debe ser mayor/ multiploa 10 ms");
	}
	while(tclien%10!=0);
	
	//Se borra la pantalla para iniciar con la presentacion
	//Se comienza con la presentacion de la simulacion, el siguiente for se encarga de poner el nombre del supermercado
	//de forma animada en la pantalla
	int filas,columnas,p;
	
	BorrarPantalla();
	
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
	MoverCursor(35,1);
	printf("SUPERMERCADO: %s",nombre);
	
	MoverCursor(2,3);
	printf(">>>LOS CLIENTES LLEGAN CADA: %d ms", tclien);
	
	MoverCursor(50,3);
	printf(">>>CAJAS DISPONIBLES: %d",numcaj);
	
	//Se crean las colas a usar en el supermercado y se inicializan

	unsigned int tiempo = 0; //Cuenta el tiempo que ha pasado
	unsigned int numcliente = 1; //Cuenta los clientes que han llegado	
	int c,a,j,k,fila = 0;
	cola caja[numcaj];
	elemento cliente;
	elemento caten[numcaj]; //representa al cliente que esta siendo atendido
	
	//Se inicializa la funcion srand
	srand(time(NULL));		
	cliente.n=0;

	for(c=0; c<numcaj; c++)
	{
		Initialize(&caja[c]);
		caten[c]=cliente;
	}
	
	while(1)
	{
		Sleep(50);
		tiempo++;

		//Llegada de clientes
		if(cliente.n<=100)
		{
			if(tiempo%tclien==0) //Si el tiempo es multiplo del tiempo de llegada de clientes
			{
				cliente.n=numcliente;
				numcliente++;
				fila=rand()%numcaj;
				Queue(&caja[fila], cliente);
				MoverCursor(3,7);
				printf("                                       ");
				MoverCursor(3,7);
				printf("Llego el cliente: %d a la caja %d", cliente.n, fila+1);
			}
		
			if(tiempo%tiemcaj==0)//Si el tiempo es multiplo del de atencion
			{
				for(a=0; a<numcaj; a++)
					{
						if(!Empty(&caja[a]))
						{	
							cliente=Dequeue(&caja[a]);
							MoverCursor(45,7);
							printf("                                       ");
							MoverCursor(45,7);
							printf("Atendi a: %d en la caja %d",cliente.n,a+1);
						}	
						else
						{
							MoverCursor(5,10);
							printf("No hay a quien atender en %d",a+1);
						}							
					} 	
			}
			
			
			for(j=0;j<numcaj;j++)
			{
				MoverCursor(2 ,10 + j*2 );
				printf("                                                                          ");
				MoverCursor(2 ,10 + j*2 );
				printf("%d Clientes en cj %d: [", Size(&caja[j]), j+1);
				
				for(k = 1; k <= Size(&caja[j]);k++)
				{
					cliente = Element(&caja[j], k);
					printf(" %d ", cliente.n);
				}
				printf("]");		
			}	
	
		}
		else
		{
			MoverCursor(5,25);
			printf("CAJAS CERRADAS");
			exit(0);
		}
	}

return 0;
}

