#include <stdlib.h>
#include "operaciones.h"

int terna(int ultimo,int penultimo,int antepenultimo){
	if(!ultimo)return antepenultimo;
	return penultimo;
}

long long producto(int operando1,int operando2){
	return operando1*operando2;
}

long long suma(int operando1,int operando2){
	return operando1+operando2;
}

long long resta(int operando1,int operando2){
	return operando1-operando2;
}

long long division(int operando1,int operando2){
	return operando1/ operando2;
}

long long raiz_cuadrada(int operando1){
	
	if(operando1==0) return 0;
	if(operando1==1) return 1;
	
	int inicio=0;
	int final=operando1;
	
	int respuesta=0;
	
	while(inicio<=final){
		int medio=(final+inicio)/2;
		if(medio*medio==operando1)return medio;
		else if(medio*medio > operando1){
			final=medio-1;
		}
		else{
			respuesta=medio;
			inicio=medio+1;
		}
	}
	
	return respuesta;
}

long long logaritmo(int base,int argumento){
	
	int contador=0;
	for(int i=base;i<=argumento;i*=base)contador++;
	return contador;
}

long long _potencia(int base,int exponente){
	if(exponente==0)return 1;
	long long resultado=0;
	
	if(exponente%2==0){
		
		resultado=potencia(base,exponente/2);
		return resultado*resultado;
	}
	
	resultado=potencia(base,(exponente-1)/2);
	return base*resultado*resultado;
}

long long potencia(int base,int exponente){
	return _potencia(base,exponente);
}


