#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <stdbool.h>

bool validar_rango_resultado(long long resultado);

bool validar_operacion_raiz(int operando,long long* extra);

bool validar_operacion_logaritmo(int base,int argumento,long long* extra);

bool validar_operacion_producto(int operando1,int operando2,long long* extra);

bool validar_operacion_suma(int operando1,int operando2,long long* extra);

bool validar_operacion_resta(int operando1,int operando2,long long* extra);

bool validar_operacion_division(int operando1,int operando2,long long* extra);

bool validar_operacion_potencia(int operando1,int operando2,long long* extra);

#endif // VALIDACIONES_H
