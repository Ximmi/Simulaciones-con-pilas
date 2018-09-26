/* 

    Explicacion:
    Este programa simulara la ejecucion que realizan los procesos en un sistema operativo indicando cuales procesos
    se llevan a cabo y en que tiempo.
    */
 
#include <stdio.h>
#include <windows.h> //Funciona unicamente en Windows para usar la función Sleep()
#include <conio.h>
#include <string.h>
#include "TADColaDin.h"
//#include "TADColaEst.h"
//#include "TADColaEstCirc.h"

#define TIEMPO_BASE	1000			//Tiempo base en ms

#define TIEMPO_ATENCION	1		//Tiempo base en ms * 1

int main(){
	BorrarPantalla();
	elemento e,a,b;  //declaramos 3 estructuras, una se utilzara para almacenar datos generales y las otras 2 para datos auxiliares
	unsigned int tiempo=0;
	
 	cola de_ejecucion;    
	cola de_terminado;

	Initialize(&de_ejecucion);       //Inicilizamos ls 2 colas que necesitaremos
	Initialize(&de_terminado);
	
	//pedimos un entero n para fijar la cantidad de procesos a realizar
	int n;
	int cola; //variable usada asignar  un tiempo en cola inicial
	int m,i;   // utilizamos m para guardar el tamaño de cola

	printf("\n Ingresa el numero de procesos a realizar\n");
	scanf("%d",&n);

	//Aqui encolaremos los elementos, este variara dependiendo del numero de procesos puesto
	for( i=0; i<n; i++){
		//nota: en proceso y actividad usar _ y no un "espacio", de lo contrario se saltara dichos espacios
		printf("\nIngresa el nombre del proceso\n");
		scanf("%s",&e.proceso);
		printf("\nIngresa la actividad a realizar\n");
		scanf("%s",&e.actividad);
		printf("\nIngresa un ID\n");
		scanf("%s",&e.id);
		printf("\nIngresa el tiempo de tu proceso en segundos\n");
		scanf("%d",&e.tiempo);
		if (!Empty(&de_ejecucion)){
			cola=Size(&de_ejecucion);
			e.tejecu=(cola+1);}
			else
			e.tejecu=0;
			Queue(&de_ejecucion,e);
		
		}
		//aqui usaremos un ciclo para desencolar los datos de la cola e imprimirlos
		while (1){
			Sleep(TIEMPO_BASE);
			tiempo++;
			if(tiempo%TIEMPO_ATENCION==0){
				if (!Empty(&de_ejecucion)){
				e = Dequeue(&de_ejecucion);
				printf("\n****************************************");
				printf("\n\nEn ejecucion: %s", e.proceso);
				printf("\nActividad : %s", e.actividad);
				printf("\nID: %s", e.id);
			printf("\nConcluira en: %ds", e.tiempo);
				e.tiempo--;
				e.tejecu++;
				printf("\nSu tiempo en ejecucion es: %d",e.tejecu);
				printf("\n****************************************");
				//con este if evaluaremos si la cola no esta vacia, de ser podremos indicar que el proceso siguiente es el frente de la cola
				if (!Empty(&de_ejecucion)){
				a= Front(&de_ejecucion);
				printf("\n****************************************");
				printf("\nEl siguiente proceso es %s",a.proceso);
				printf("\n su id es %s",a.id);
				printf("\n concluira en %ds",a.tiempo);
				printf("\n lleva en ejecucion :%ds",e.tejecu);
				printf("\n****************************************");
				}
				//este if servira para  volver a encolar procesos que aun no acaben
				//de la misma manera e.taux servira para ir guardando un valor que nos servira para obtener el tiempo de cola
				if(e.tiempo!=0){  
				m=(Size(&de_ejecucion)+1);
				e.tejecu=(e.tejecu)+m;
				Queue(&de_ejecucion,e);
				// b es una estructura en donde guardaremos los datos del proceso anterior
				b= Final(&de_ejecucion);
				printf("\n****************************************");
				printf("\nEl proceso anterior fue %s",b.proceso);
				printf("\n su id es %s",b.id);
				printf("\n concluira en %ds",b.tiempo);
				printf("\n****************************************");
				}
				//
			//
				else if (e.tiempo==0){
				Queue(&de_terminado,e);
				b= Final(&de_terminado);
				printf("\n****************************************");
				printf("\nEl proceso anterior fue %s",b.proceso);
				printf("\n su id es %s",b.id);
				printf("\n concluira en %ds",b.tiempo);
				printf("\n****************************************");
				 }
			}
			//Si la cola es vacia imprimira los siguientes datos de la cola de finalizados
			else{
				if (!Empty(&de_terminado)){
					e = Dequeue(&de_terminado);
				printf("\n_______________________________________");
				printf("\nEl proceso: %s", e.proceso);
				printf("\n\nCuyo id es: %s", e.id);
				printf("\n\nTardo : %ds en terminarse", e.tejecu);
				printf("\n_______________________________________");
				
				}
				else 
				exit(1);}
				}} return 0;}
