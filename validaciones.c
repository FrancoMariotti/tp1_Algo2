#include <limits.h>
#include "validaciones.h"
#include "operaciones.h"


bool validar_rango_resultado(long long resultado){
	return resultado>= INT_MIN &&resultado<= INT_MAX;
}

bool validar_operacion_raiz(int operando,long long* extra){
	
	if(operando >=0){
		long long resultado = raiz_cuadrada(operando);
		if(validar_rango_resultado(resultado)){
			*extra=(int)resultado;
			return true;
		}
	}
	return false;
}

bool validar_operacion_logaritmo(int base,int argumento,long long* extra){
	
	if(base > 0 && base!=1 && argumento>0){
		long long resultado = logaritmo(base,argumento);
		if(validar_rango_resultado(resultado)){
			*extra=resultado;
			return true;
		}
	}
	return false;
}
bool validar_operacion_producto(int operando1,int operando2,long long* extra){
	
	long long resultado = producto(operando1,operando2);
	if(validar_rango_resultado(resultado)){
		*extra=resultado;
		return true;
	}
	return false;
}

bool validar_operacion_suma(int operando1,int operando2,long long* extra){
	
	long long resultado = suma(operando1,operando2);
	if(validar_rango_resultado(resultado)){
		*extra=resultado;
		return true;
	}
	return false;
}

bool validar_operacion_resta(int operando1,int operando2,long long* extra){
	
	long long resultado = resta(operando1,operando2);
	if(validar_rango_resultado(resultado)){
		*extra=resultado;
		return true;
	}
	return false;
}

bool validar_operacion_division(int operando1,int operando2,long long* extra){
	if(operando2!=0){
		long long resultado = division(operando1,operando2);
		if(validar_rango_resultado(resultado)){
			*extra=resultado;
			return true;
		}
	}
	return false;
}

bool validar_operacion_potencia(int operando1,int operando2,long long* extra){
	if(operando2 < 0)return false;
	
	if(operando1!=0 || operando2!=0){
		long long resultado = potencia(operando1,operando2);
		if(validar_rango_resultado(resultado)){
			*extra=resultado;
			return true;
		}
	}
	return false;
}

