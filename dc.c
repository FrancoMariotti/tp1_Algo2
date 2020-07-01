#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dc.h"
#include "strutil.h"
#include "validaciones.h"
#include "operaciones.h"



int main(int argc, char **argv){
	
	dc(stdin);
	
	return 0;
}

void dc(FILE* archivo){
	char* linea=NULL;
    size_t largo_linea=0;
    ssize_t leidos=-1;
    
    while((leidos=getline(&linea,&largo_linea, archivo)) != -1){
		if (linea[0] == FIN_LINEA){
			imprimir_error("ERROR\n");
			continue;
		}
		linea[leidos-1]=FIN_CADENA;
		char** cadenas=split(linea,' ');		
		interpretar_linea(cadenas);
		free_strv(cadenas);
	}
	free(linea);
}

void eliminar_elementos_pila(pila_t* pila,void destruir_datos(void*)){
	if(!destruir_datos)return;
	
	while(!pila_esta_vacia(pila)){
		destruir_datos(pila_desapilar(pila));
	}
}

void imprimir_resultado(pila_t* operandos){
	int* resultado=pila_desapilar(operandos);
	
	if(!pila_esta_vacia(operandos))imprimir_error("ERROR\n");
	else if(resultado)fprintf(stdout,"%d\n",*resultado);
	free(resultado);
}

void imprimir_error(char* error){
	fprintf(stdout, "%s",error);
}

bool es_numero_entero(char* cadena){
	
	size_t largo_cadena=strlen(cadena);
	
	size_t signo=0;
	
	if(cadena[0]==OPERADOR_RESTA || cadena[0]==OPERADOR_SUMA){
		if(largo_cadena==1)return false;
		signo=1;
	}
	
	for(size_t i=signo;i<largo_cadena;i++){
		if(!isdigit(cadena[i]))return false;
	}
		
	return true;
}

bool realizar_operacion(pila_t* operandos,char* operador){	
	
	int* operando1=pila_desapilar(operandos);
	
	if(!operando1)return true;
	
	int* resultado=malloc(sizeof(int));
	
	if(!resultado)return true;
	
	bool error_operacion=false;
	
	long long resultado_operacion=0l;
	
	if(!strcmp(operador,OPERADOR_RAIZ_CUADRADA)){
		if(validar_operacion_raiz(*operando1,&resultado_operacion))
			*resultado=(int)resultado_operacion;
		else error_operacion=true;
	}
	else{
		int* operando2=pila_desapilar(operandos);
	
		if(!operando2)error_operacion=true;
		
		else if(!strcmp(operador,OPERADOR_LOGARITMO)){	
			if(validar_operacion_logaritmo(*operando2,*operando1,&resultado_operacion))
				*resultado=(int)resultado_operacion;
			else error_operacion=true;
		}
		else if(operador[0]==OPERADOR_PRODUCTO){
			if(validar_operacion_producto(*operando2,*operando1,&resultado_operacion))
				*resultado=(int)resultado_operacion;
			else error_operacion=true;
		}
		else if(operador[0]==OPERADOR_SUMA){
			if(validar_operacion_suma(*operando1,*operando2,&resultado_operacion))
				*resultado=(int)resultado_operacion;
			else error_operacion=true;
		}
		else if(operador[0]==OPERADOR_RESTA){
			if(validar_operacion_resta(*operando1,*operando2,&resultado_operacion))
				*resultado=(int)resultado_operacion;
			else error_operacion=true;
		}
		else if(operador[0]==OPERADOR_DIVISION){
			if(validar_operacion_division(*operando1,*operando2,&resultado_operacion))
				*resultado=(int)resultado_operacion;
			else error_operacion=true;
		}
		else if(operador[0]==OPERADOR_POTENCIA){
			if(validar_operacion_potencia(*operando1,*operando2,&resultado_operacion))
				*resultado=(int)resultado_operacion;
			else error_operacion=true;
		}
		else if(operador[0]==OPERADOR_TERNARIO){
			int* operando3=pila_desapilar(operandos);
				
			if(operando3)*resultado=terna(*operando1,*operando2,*operando3);
			else error_operacion=true;
				
			free(operando3);
		}
		else error_operacion=true;	
		
		free(operando2);
	}
	
	free(operando1);
	
	if(error_operacion)free(resultado);
	else pila_apilar(operandos,resultado);
	
	return error_operacion;
}

void interpretar_linea(char** cadenas){
	
	pila_t* operandos=pila_crear();
	int contador=0;
	int contador_operadores=0;
	
	
	while(cadenas[contador]){
		if(cadenas[contador][0]==(char)0){
			contador++; 
			continue;
		}	
		if(es_numero_entero(cadenas[contador])){
			int* operando=malloc(sizeof(int));
			*operando=atoi(cadenas[contador]);
			pila_apilar(operandos,operando);
		}
		else{
			contador_operadores++;
			if(realizar_operacion(operandos,cadenas[contador])){
				eliminar_elementos_pila(operandos,free);
				imprimir_error("ERROR\n");
				break;
			}
		}
		contador++;
	}
	
	if(!contador_operadores) imprimir_error("ERROR\n");
	else imprimir_resultado(operandos);
	eliminar_elementos_pila(operandos,free);
	pila_destruir(operandos);
	
}
