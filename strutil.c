#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"
#define FIN_CADENA	'\0'


char* obtener_cadena(size_t tamanio_cadena){
	char* cadena=calloc(tamanio_cadena+1,sizeof(char));
	if(!cadena)return NULL;
	cadena[tamanio_cadena]=FIN_CADENA;
	return cadena;
}

char** split(const char* str, char sep){
	
	if(!str)return NULL;
	
	size_t longitud_cadena=strlen(str);
	size_t cantidad_subcadenas=2;
	
	for(int i_cadena=0;i_cadena<longitud_cadena;i_cadena++){
		if(str[i_cadena]==sep)cantidad_subcadenas++;
	}
	
	char** subcadenas=malloc(sizeof(char*)*cantidad_subcadenas);
	
	if(!subcadenas)return NULL;
	
	subcadenas[cantidad_subcadenas-1]=NULL;
	
	
	if(cantidad_subcadenas==2 || sep==FIN_CADENA) {
		subcadenas[0]=strdup(str);
		return subcadenas;
	}
	
	size_t contador_caracteres=0;
	size_t contador_subcadenas=0;
	
	for(int i_cadena=0;i_cadena<longitud_cadena;i_cadena++){
		
		if(str[i_cadena]==sep || i_cadena==longitud_cadena-1){
			char* subcadena=obtener_cadena(contador_caracteres);
			subcadenas[contador_subcadenas]=subcadena;
			contador_subcadenas++;
			contador_caracteres=0;
		}
		if(str[i_cadena]==sep && i_cadena==longitud_cadena-1){
			char* subcadena=obtener_cadena(contador_caracteres);
			subcadenas[contador_subcadenas]=subcadena;
			break;
		}
		
		contador_caracteres++;
	}
	
	contador_caracteres=0;
	contador_subcadenas=0;

	for(int i_cadena=0;i_cadena<longitud_cadena;i_cadena++){
		if(str[i_cadena]==sep){
			contador_subcadenas++;
			contador_caracteres=0; 
			continue;
		}
		subcadenas[contador_subcadenas][contador_caracteres]=str[i_cadena];
		contador_caracteres++;
	}
	return subcadenas;
}


char* join(char** strv, char sep){
	
	if(!strv)return NULL;
	
	size_t i_cadena=0;
	size_t i_subcadena=0;
	size_t contador_caracteres=1;
	
	while(strv[i_subcadena]){
		if(strv[i_subcadena][i_cadena]==FIN_CADENA){
			i_subcadena++;
			i_cadena=0;
			continue;
		}
		contador_caracteres++;
		i_cadena++;
	}
	
	size_t largo=i_subcadena+contador_caracteres;
	char* cadena=calloc(largo,sizeof(char));
	cadena[largo-1]=FIN_CADENA;
	
	i_cadena=0;
	i_subcadena=0;
	contador_caracteres=0;
	
	while(strv[i_subcadena]){
		if(contador_caracteres==largo-2)break;
		if((strv[i_subcadena])[i_cadena]==FIN_CADENA){
			cadena[contador_caracteres]=sep;
			i_subcadena++;
			contador_caracteres++;
			i_cadena=0;
			continue;
		}
		cadena[contador_caracteres]= strv[i_subcadena][i_cadena];
		contador_caracteres++;
		i_cadena++;
	}
	return cadena;
}

void free_strv(char* strv[]){
	int contador=0;
	while(strv[contador]){
		free(strv[contador]);
		contador++;
	}
	free(strv);
}
