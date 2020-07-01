#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL	100

struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

pila_t* pila_crear(void){
	
	pila_t* pila = malloc(sizeof(pila_t));
	
	if(pila == NULL)return NULL;
	
	pila->capacidad = CAPACIDAD_INICIAL;
	
	pila->datos = malloc(sizeof(void*)*CAPACIDAD_INICIAL);
	
	if(pila->datos == NULL)
	{
		free(pila);
		return NULL;
	}
	
	pila->cantidad=0;
	
	return pila;
}

bool pila_redimensionar(pila_t* pila,size_t tam){
	
	void** aux = realloc(pila->datos,sizeof(void*)*tam);
	
	if(aux == NULL) return false;
	
	pila->datos = aux;
	pila->capacidad = tam;
	
	return true;
}

bool pila_apilar(pila_t *pila, void* valor){
	if(pila->cantidad+1 > pila->capacidad){
		if(!pila_redimensionar(pila,pila->capacidad*2)) return false; 
	}
	
	pila->cantidad+=1;
	pila->datos[pila->cantidad-1]=valor;
	
	return true;	
}

void* pila_ver_tope(const pila_t *pila){
	
	if(pila_esta_vacia(pila)) return NULL;
	return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila){
	
	if(pila_esta_vacia(pila)) return NULL;
	
	
	if(pila->cantidad > CAPACIDAD_INICIAL && pila->cantidad < pila->capacidad/4) 
		pila_redimensionar(pila,pila->capacidad/2);	
	
	void* dato = pila_ver_tope(pila);
	pila->cantidad-=1;
	return dato;
}

bool pila_esta_vacia(const pila_t *pila){
	return pila->cantidad == 0;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

