#ifndef GREP_H
#define GREP_H
#include <stdbool.h>
#include "cola.h"

#define MAXIMO_PARAMETROS	4
#define MINIMO_PARAMETROS	3
#define FIN_DE_CADENA	'\0'

void grep(FILE* archivo,char* subcadena,size_t cantidad_lineas_anteriores);

void imprimir_error(char* error);

bool validar_entrada(int argc, char **argv);

bool comparar_cadenas(char* cadena1,char* cadena2,size_t largo);

bool encontrar_coincidencia(char* linea,char* cadena);

char* copiar_cadena(char* cadena);

void guardar_n_lineas_anteriores(cola_t* lineas,char* linea,size_t cantidad_lineas_anteriores,size_t* cantidad_lineas);

void imprimir_lineas(cola_t* lineas);

#endif // GREP_H
