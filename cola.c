#include "cola.h"
#include <stdlib.h>

typedef struct nodo{
	void* dato;
	struct nodo* prox; 
}nodo_t;

struct cola {
	nodo_t* prim;
	nodo_t* ult;
};

cola_t* cola_crear(void){
		
	cola_t* cola=malloc(sizeof(cola_t));
	
	if(!cola) return NULL;
	
	cola->prim=NULL;
	cola->ult=NULL;
	
	return cola;
}

nodo_t* nodo_crear(void* valor){
	nodo_t* nodo=malloc(sizeof(nodo_t));
	
	if(!nodo) return NULL;
	
	nodo->dato=valor;
	nodo->prox=NULL;
	
	return nodo;
}

bool cola_esta_vacia(const cola_t *cola){
	return cola->prim==NULL;
}

bool cola_encolar(cola_t *cola, void* valor){
	
	nodo_t* nodo_nuevo=nodo_crear(valor);
	
	if(!nodo_nuevo) return false;
	
	if(cola_esta_vacia(cola)){
		cola->prim=nodo_nuevo;
	}
	else{
		cola->ult->prox=nodo_nuevo;
	}
	cola->ult=nodo_nuevo;
	
	return true;
	
}

void* cola_ver_primero(const cola_t *cola){
	
	if(cola_esta_vacia(cola)) return NULL;
	
	return cola->prim->dato;
}

void* cola_desencolar(cola_t *cola){
	
	if(cola_esta_vacia(cola)) return NULL;
	
	nodo_t* desencolado=cola->prim;
	
	cola->prim=cola->prim->prox; 
	
	void* valor=desencolado->dato;

	free(desencolado);
	
	return valor;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	while(!cola_esta_vacia(cola)){
		void* dato=cola_desencolar(cola);
		if(destruir_dato){
			destruir_dato(dato);
		}
	}
	
	free(cola);
}
