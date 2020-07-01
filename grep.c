#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grep.h"

int main(int argc, char **argv){
	
	if(!validar_entrada(argc,argv))return -1;
	
    FILE* archivo=stdin;
    
    if(argc==MAXIMO_PARAMETROS){
		archivo=fopen(argv[3],"r");
	
		if(!archivo){
			imprimir_error("No se pudo leer el archivo indicado\n");
			return -1;
		}
	}	
	
	grep(archivo,argv[1],(size_t)atoi(argv[2]));
	
	return 0;
}


void imprimir_error(char* error){
	fprintf(stderr, "%s",error);
}

bool validar_entrada(int argc, char **argv){
	
	if(argc<MINIMO_PARAMETROS || argc>MAXIMO_PARAMETROS){
		imprimir_error("Cantidad de parametros erronea\n");
		return false;
	}
	
	size_t cantidad_decimales=strlen(argv[2]);
	for(size_t i=0;i<cantidad_decimales;i++){
		if(argv[2][i]<48 || argv[2][i]>57){
			imprimir_error("Tipo de parametro incorrecto\n");
			return false;
		}
	}
	
	return true;
	
}

bool comparar_cadenas(char* cadena1,char* cadena2,size_t largo){
	for(int i=0;i<largo;i++)if(cadena1[i]!=cadena2[i])return false;
	return true;
}

bool encontrar_coincidencia(char* linea,char* cadena){
	size_t largo_linea=strlen(linea);
	size_t largo_cadena=strlen(cadena);
	
	for(size_t i=0;i<largo_linea;i++){
		if(linea[i]==cadena[0]&&(i+largo_cadena-1)<largo_linea){
			if(comparar_cadenas(linea+i,cadena,largo_cadena))return true;
		}
	}
	return false;
} 

char* copiar_cadena(char* cadena){
	size_t largo_cadena=strlen(cadena);
	
	char* copia_cadena=malloc(largo_cadena+1);
	
	copia_cadena[largo_cadena]=FIN_DE_CADENA;
	
	strcpy(copia_cadena,cadena);
	return copia_cadena;
}

void guardar_n_lineas_anteriores(cola_t* lineas,char* linea,size_t cantidad_lineas_anteriores,size_t* cantidad_lineas){
	
	if(!cantidad_lineas_anteriores)return;
	
	char* copia_linea=copiar_cadena(linea);
	
	cola_encolar(lineas,copia_linea);
	
	if(*cantidad_lineas==cantidad_lineas_anteriores){
		if(!cola_esta_vacia(lineas))free(cola_desencolar(lineas));
	}
	else *cantidad_lineas+=1;
}

void imprimir_lineas(cola_t* lineas){
	char* linea_desencolada=NULL;
	
	while(!cola_esta_vacia(lineas)){
		linea_desencolada=cola_desencolar(lineas);
		fprintf(stdout, "%s", linea_desencolada);
		free(linea_desencolada);
	}
}

void grep(FILE* archivo,char* subcadena,size_t cantidad_lineas_anteriores){
	char* linea=NULL;
    size_t largo_linea=0;
	cola_t* lineas=cola_crear();
	size_t contador_lineas=0;
	ssize_t leidos=-1;
	
	while((leidos=getline(&linea,&largo_linea, archivo)) != -1){
		
		if(encontrar_coincidencia(linea,subcadena)){
			char* copia_linea=copiar_cadena(linea);
			cola_encolar(lineas,copia_linea);
			imprimir_lineas(lineas);
			contador_lineas=0;
		}
		else guardar_n_lineas_anteriores(lineas,linea,cantidad_lineas_anteriores,&contador_lineas);
	}
	
	cola_destruir(lineas,free);
	free(linea);
	fclose(archivo);
}
