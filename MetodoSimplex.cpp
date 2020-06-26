#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<malloc.h>
#define TAM 2

void llenar_Arreglo_Funcion_Objetivo();
void mostrar_FuncionObjetivo_Y_Restricciones(int filas);
void llenar_Matriz_Restricciones(int filas);
void llenar_Matriz_Tabla_Inicial(int filas, int columnas, int restricciones);
int Arreglo_Funcion_Objetivo[TAM];
int **Matriz_Restricciones=NULL,i,j;
int *Po_termino_Independiente=NULL;
//int **Matriz_Tabla_Inicial=NULL;

int main(){
	int opc, flag=0, cont=0;
	int N_Restricciones=0, filas=0, columnas=0;
	do{
		system("cls");
		printf("\n MAXIMIZACION...");
		printf("\n 1.- Ingresar funcion objetivo");
		printf("\n 2.- Ingresar restricciones");
		printf("\n 3.- Mostrar datos");
		printf("\n 4.- Generar tabla inicial");
		printf("\n 5.- Salir");
		printf("\n Ingrese su opcion: ");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				llenar_Arreglo_Funcion_Objetivo();
				cont++;
				break;
				
			case 2:
				printf("\n Cantidad de restricciones: ");
				scanf("%d",&N_Restricciones);
				llenar_Matriz_Restricciones(N_Restricciones);
				break;
				
			case 3:
					if(cont!=0 && N_Restricciones!=0)
					mostrar_FuncionObjetivo_Y_Restricciones(N_Restricciones);
					else
					printf("\n Ingresar funcion objetivo y restricciones...");
				break;
				
			case 4:
				if(cont!=0 && N_Restricciones!=0){
					filas=N_Restricciones+1; //N° de filas para la matriz inicial, restricciones o las variables de holguras (P.n) mas la fila (Z)
					columnas=TAM+N_Restricciones+2; //restricciones + cantidad de variables de holgura + cb
					llenar_Matriz_Tabla_Inicial(filas,columnas,N_Restricciones);
					cont=0; N_Restricciones=0;
				}else{
					printf("\n Ingresar funcion objetivo y restricciones...");
				}
				break;
				
			case 5:
				flag=1;
				break;
				
			default:
				printf("\n Opcion Invalida...");
				break;
		}
			if(!flag){
				printf("\n Presione una tecla para continuar...");
				getch();
			}
	}while(!flag);
	printf("\n\n Saliendo del programa...");
	getch();
}

void llenar_Arreglo_Funcion_Objetivo(){
	printf("\n");
	for(i=0; i<TAM; i++){
		printf("\n Elemento[%d]: ",i+1);
		scanf("%d",&Arreglo_Funcion_Objetivo[i]);
	}
}

void mostrar_FuncionObjetivo_Y_Restricciones(int filas){
	int columnas=0;
	printf("\n Funcion objetivo N.(Xn) + N.(Xn)...\n");
	printf("\n");
	for(i=0;i<TAM;i++){
		printf("%2d.(X%d) ",Arreglo_Funcion_Objetivo[i],i+1);
	}
	
	printf("\n");
	columnas=TAM;
	printf("\n Restricciones...");
	printf("\n");
	for(i=0;i<filas;i++){
		printf("\n Restriccion No. %d : ",i+1);
		for(j=0;j<columnas;j++){
			printf("[%2d ]",Matriz_Restricciones[i][j]);
		}
		printf(" = %d",Po_termino_Independiente[i]);
		printf("\n");
	}		
}

void llenar_Matriz_Restricciones(int filas){
	int columnas=0, cont=0;
	
	Matriz_Restricciones=(int**)malloc(sizeof(int)*filas);
	columnas=TAM; //TAM(CANTIDAD DE COLUMNAS)=2
	
	Po_termino_Independiente=(int*)malloc(sizeof(int)*filas);
	
	for(i=0;i<filas; i++)
	Matriz_Restricciones[i]=(int*)malloc(sizeof(int)*columnas); 
	
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
				printf("Restriccion [%d] \n Dato(variable): ",i+1);
				scanf("%d",&Matriz_Restricciones[i][j]);
		}
		printf("Termino idependiente: ");
		scanf("%d",&Po_termino_Independiente[i]);
		printf("\n");
	}	
}

void llenar_Matriz_Tabla_Inicial(int filas, int columnas, int restricciones){
	//Variables para la matriz inicial...
		int npos=0, contj=4, conti=0, posPo=0;
		int posfn=0, vector[restricciones*TAM];
		float Matriz_Tabla_Inicial[filas][columnas];
		
	//Variables para las iteracciones...
		int menor=0,aux, Po=1;
		float menor_div=10000;
		float result_div=0, Elemento_Pivote;
		int posicion_fila_pivote, posicion_columna_pivote, Iteracion=0;
		float Matriz_Tabla_Aux[filas][columnas], Nuevo_Elemento_Pivote, Ant_Elemento_Fila_Pivote;
		float Nuevo_Elemento_Fila, Ant_Elemento_Fila, Ant_Elemento_Fila_Columna_Pivote, Nuevo_Elemento_Fila_Pivote;
		
		/*
			CREACION DE LA TABLA INCIAL PARA POSTERIORMENTE GENERAR LAS ITERACIONES...
		*/
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				if((i==conti) && (j==contj)){
					Matriz_Tabla_Inicial[i][j]=1;
					contj++;
					conti++;
				}else{
					Matriz_Tabla_Inicial[i][j]=0;
				}
			}
		}
		
		for(i=0; i<restricciones; i++){
			for(j=0; j<TAM; j++){
				vector[npos]=Matriz_Restricciones[i][j];
				npos++;		
			}
		}
		free(Matriz_Restricciones); //liberar memoria asignada dinamicamente con el malloc a la matriz
		
		npos=0;
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				if((j==1) && (i!=filas-1)){
					Matriz_Tabla_Inicial[i][j]=Po_termino_Independiente[posPo];
					posPo++;
				}
				if((j>1) && (j<4) && (i!=filas-1)){
						Matriz_Tabla_Inicial[i][j]=vector[npos];
						npos++;
				} 
				if((i==filas-1)&&(j>1 && j<4)){
					Matriz_Tabla_Inicial[i][j]=(Arreglo_Funcion_Objetivo[posfn]*-1);	
					posfn++;
				}
			}
		}
		free(Po_termino_Independiente); //liberar memoria asignada dinamicamente con el malloc al vector
		
		printf("\n\n");
		printf("\n MATRIZ INICIAL...\n\n");
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				printf("\t( %.0f )",Matriz_Tabla_Inicial[i][j]);
			}
			printf("\n");
		}
		
		/*
			GENERAR ITERACIONES A PARTIR DE LA TABLA INICIAL...
		*/
		do{
			
		Iteracion++;	
		Nuevo_Elemento_Fila=0, Ant_Elemento_Fila=0, Ant_Elemento_Fila_Columna_Pivote=0, Nuevo_Elemento_Fila_Pivote=0;
		Nuevo_Elemento_Pivote=0, Ant_Elemento_Fila_Pivote=0;
		posicion_fila_pivote=0;Elemento_Pivote=0;
		menor=0,aux=0, posicion_columna_pivote=0;
		
	//Encontrar el menor de la fila Z (Columna pivote)
	for(i=0; i<filas; i++){
		for(j=0; j<columnas; j++){
			if(i==filas-1){ //fila -1 para acceder a la ultima fila(0-3) (fila=4-1)
				aux= Matriz_Tabla_Inicial[i][j]; 
				if(aux<menor){ //Verificar cual es el menor de la ultima fila, este nos permitira seguir iterando mientras sea menor que 0
					menor=aux;
					posicion_columna_pivote=j; //recuperamos la posicion de la columna pivote
				}
			}
		}
	}
	printf("\n el menor de la ultima fila (Z) = %d", menor);
	
	if(menor==0)
		break;
	
	//fila pivote o variable que sale
	for(i=0; i<filas-1; i++){
		for(j=0; j<columnas; j++){
			if(j==posicion_columna_pivote){
				result_div=Matriz_Tabla_Inicial[i][Po] / Matriz_Tabla_Inicial[i][j]; //dividir los elementos de la columna P0 / los elementos de la columna pivote
				//menor_div=result_div;
				if(result_div<menor_div && result_div>0){ //verificar cual es el menor valor positivo de la division
					menor_div=result_div;
					posicion_fila_pivote=i; //se recupera en que fila se encuentra le menor
				}
				printf("\n Fila pivote ---> Po / Columna pivote= %.2f",result_div);
			}
		}
	}
	
	Elemento_Pivote=Matriz_Tabla_Inicial[posicion_fila_pivote][posicion_columna_pivote];
	
	printf("\n menor de la fila pivote es: %.0f",menor_div);
	printf("\n La fila pivote es = %d", posicion_fila_pivote);
	printf("\n Elemento pivote es = %.2f",Elemento_Pivote);
	
	//Variable que sale "posicion_fila_pivote"
	//Variable que entra "posicion_columna_pivote"
	
	//Creacion de la tabla de la iteracion 1
	//Agregando los elementos de la fila pivote en matriz auxiliar
	for(i=0; i<filas; i++){
		for(j=0; j<columnas; j++){
			
			Ant_Elemento_Fila_Pivote=Matriz_Tabla_Inicial[posicion_fila_pivote][j]; //recuperar los valores de la fila pivote
			
			if(i==posicion_fila_pivote){ //Verificar si estamos en la posicion de la fila pivote para los nuevos elementos
				if(i==posicion_fila_pivote && j==0){ //ubicarnos en la columna cb de la fila pivote o variable que sale para agregar el elemento pivote
					Matriz_Tabla_Aux[posicion_fila_pivote][j]=Elemento_Pivote; //Asignar valor elemento pivote
				}
				else{
						Nuevo_Elemento_Pivote=Ant_Elemento_Fila_Pivote/Elemento_Pivote; //Calculo de los nuevos valores
						Matriz_Tabla_Aux[i][j]=Nuevo_Elemento_Pivote;
					}
			}
			
		}
	}
	
	//Agregando los otros nuevos elementos de las demas filas matriz auxiliar... 
	for(i=0; i<filas; i++){
		for(j=0; j<columnas; j++){
			Ant_Elemento_Fila_Columna_Pivote = Matriz_Tabla_Inicial[i][posicion_columna_pivote]; //Recuperamos los elementos anteriores que estan en la fila actual de la columna pivote de la tabla inicial
			Nuevo_Elemento_Fila_Pivote = Matriz_Tabla_Aux[posicion_fila_pivote][j]; //Nuevos elementos que se agregaron en la fila pivote a la matriz auxiliar 
			if(i!=posicion_fila_pivote){ //verificamos que no accedamos a la fila pivote para no reemplazar sus nuevos elementos
				if(j!=0){ //Exceptuando la primera columna para que agrege en orden los nuevos valores en la fila n 
					Ant_Elemento_Fila = Matriz_Tabla_Inicial[i][j]; 
					Nuevo_Elemento_Fila = Ant_Elemento_Fila - (Ant_Elemento_Fila_Columna_Pivote * Nuevo_Elemento_Fila_Pivote);
					Matriz_Tabla_Aux[i][j] = Nuevo_Elemento_Fila;
				}
			}
			
		}
	}
	
	for(i=0; i<filas; i++){
		for(j=0; j<columnas; j++){
			Matriz_Tabla_Inicial[i][j] = Matriz_Tabla_Aux[i][j];
		}
	}
	
	printf("\n\n");
	printf("\n Tabla Actualizada iteracion %d \n\n",Iteracion);
	for(i=0; i<filas; i++){
		printf("fila %d",i);
		for(j=0; j<columnas; j++){
			printf("\t[%.1f]",Matriz_Tabla_Inicial[i][j]);
		}
		printf("\n");
	}
	
	getch();
	
	}while(menor<0);
}
