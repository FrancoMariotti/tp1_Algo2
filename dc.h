#ifndef DC_H
#define DC_H

#include <stdbool.h>
#include "pila.h"

#define FIN_LINEA	'\n'
#define FIN_CADENA	'\0'
#define OPERADOR_LOGARITMO	"log"
#define OPERADOR_RAIZ_CUADRADA	"sqrt"
#define OPERADOR_TERNARIO	63
#define OPERADOR_SUMA	43
#define OPERADOR_RESTA	45
#define OPERADOR_DIVISION	47
#define OPERADOR_PRODUCTO	42
#define OPERADOR_POTENCIA	94

void dc(FILE* archivo);

void eliminar_elementos_pila(pila_t* pila,void destruir_datos(void*));

void imprimir_error(char* error);

bool es_numero_entero(char* cadena);

bool realizar_operacion(pila_t* operandos,char* operador);

void interpretar_linea(char** cadenas);

#endif // DC_H
