/*
 * GPS.cpp
 *
 *  Created on: 26 jun. 2018
 *      Author: ailen-magali
 */
#include "GPS.h"

unsigned int GPS::minimoEntre(unsigned int elemento1, unsigned int elemento2) {

	unsigned int minimo;

	if (elemento1 < elemento2) {
		minimo = elemento1;
	} else {
		minimo = elemento2;
	}

	return minimo;
}

unsigned int GPS::obtenerPosicionDeNombre(std::string nombre) {
	unsigned int i = 0;
	bool encontrado = false;
	while (!encontrado && i < catalogoSemillas->obtenerCantidadDisponible()) {
		encontrado = catalogoSemillas->obtenerPosicion(i)->obtenerNombre() == nombre;
		i++;
	}
	return i - 1;
}

void GPS::removerInfinitos(ListaNombrada<unsigned int>*& lista) {
	ListaNombrada<unsigned int>* aux = new ListaNombrada<unsigned int>();
	lista->iniciarCursor();
	while (lista->avanzarCursor()) {
		if (lista->obtenerDatoCursor() < INFINITO) {
			aux->agregar(lista->obtenerNombreCursor(), lista->obtenerDatoCursor());
		}
	}

	delete lista;

	lista = aux;
}

GPS::GPS(std::string origenRecibido, CatalogoDe<Cultivo>* catalogoSemillas, CatalogoDe<Destino>* catalogoDestinos) {

	this->catalogoSemillas = catalogoSemillas;

	this->cantidadGrafos = catalogoSemillas->obtenerCantidadDisponible();

	this->origen = origenRecibido;

	this->grafos = new GrafoDirigidoPonderado*[cantidadGrafos];

	this->mejoresCostos = new ListaNombrada<unsigned int>*[cantidadGrafos];

	this->previosCadaCultivoCadaDestino = new Candidato<std::string>*[cantidadGrafos];

	for (unsigned int i = 0; i < cantidadGrafos; i++) {
		grafos[i] = new GrafoDirigidoPonderado(catalogoDestinos, catalogoSemillas->obtenerPosicion(i)->obtenerNombre());

		ListaNombrada<unsigned int>* mejoresCostosCultivoActual = this->hallarCaminoMinConDijkstra(i); //grafo en la posicion i

		this->removerInfinitos(mejoresCostosCultivoActual);

		mejoresCostos[i] = mejoresCostosCultivoActual;
	}
}

ListaNombrada<unsigned int>* GPS::hallarCaminoMinConDijkstra(unsigned int i) {

	GrafoDirigidoPonderado* grafo = this->grafos[i];

	unsigned int cantVertices = grafo->obtenerListaAdyacencia()->contarElementos();

	Candidato<std::string>* previosCultivoActual = new Candidato<std::string>[cantVertices];

	previosCadaCultivoCadaDestino[i] = previosCultivoActual;

	this->inicializarPrevios(previosCultivoActual, grafo->obtenerListaAdyacencia());

	ListaNombrada<ListaNombrada<unsigned int>*>* listaAdyacentes = grafo->obtenerListaAdyacencia();

	ListaNombrada<unsigned int>* mejoresCaminos;

	if (listaAdyacentes->yaExisteNombre(this->origen)) {
		unsigned int posOrigen = listaAdyacentes->obtenerPosicionConNombre(this->origen);

		ColaConPrioridad cola(listaAdyacentes, posOrigen);

		mejoresCaminos = cola.convertirColaAlistaNombrada();

		while (!cola.estaVacia()) {

			Candidato<std::string> raizRemovida = cola.removerRaiz();

			std::string nombreRaiz = raizRemovida.obtenerIdentificador();

			ListaNombrada<unsigned int>* adyacentesActual = listaAdyacentes->obtenerDatoDeNombre(nombreRaiz);

			adyacentesActual->iniciarCursor();

			while (adyacentesActual->avanzarCursor()) {

				std::string nombreAdyacenteActual = adyacentesActual->obtenerNombreCursor();

				unsigned int pesoAnterior = mejoresCaminos->obtenerDatoDeNombre(nombreAdyacenteActual);

				unsigned int pesoNuevo = raizRemovida.obtenerPeso() + adyacentesActual->obtenerDatoCursor();

				if (pesoNuevo < pesoAnterior) {

					mejoresCaminos->modificarDatoConNombre(nombreAdyacenteActual, pesoNuevo);

					unsigned int posDestino = listaAdyacentes->obtenerPosicionConNombre(nombreAdyacenteActual) - 1; //array arranca en 0, no en 1 como la lista

					unsigned int posRaiz = listaAdyacentes->obtenerPosicionConNombre(nombreRaiz) - 1;

					previosCultivoActual[posDestino].modificarPeso(posRaiz); //interpretar peso como la posicion en el array del previo

					if (cola.estaNombre(nombreAdyacenteActual)) {
						cola.mejorarPeso(nombreAdyacenteActual, pesoNuevo);
					}
				}
			}
		}
	} else {
		mejoresCaminos = new ListaNombrada<unsigned int>(); //Caso origen no tenga adyacentes
	}

	return mejoresCaminos;
}

Candidato<std::string>* GPS::obtenerPreviosPara(std::string nombreCultivo) {
	unsigned int pos = this->obtenerPosicionDeNombre(nombreCultivo);

	return this->previosCadaCultivoCadaDestino[pos];
}

ListaNombrada<unsigned int>* GPS::obtenerMejoresCostosPara(std::string nombreCultivo) {

	unsigned int pos = this->obtenerPosicionDeNombre(nombreCultivo);

	return mejoresCostos[pos];
}


void GPS::inicializarPrevios(Candidato<std::string>* array, ListaNombrada<ListaNombrada<unsigned int>*>* listaAdy) {
	listaAdy->iniciarCursor();
	for (unsigned int i = 0; i < listaAdy->contarElementos(); i++) {
		listaAdy->avanzarCursor();
		Candidato<std::string> nuevoPrevio(listaAdy->obtenerNombreCursor(), listaAdy->contarElementos());
		array[i] = nuevoPrevio;
	}
}

unsigned int GPS::cantVertices(std::string nombreCultivo) {

	unsigned int pos = this->obtenerPosicionDeNombre(nombreCultivo);

	return grafos[pos]->obtenerListaAdyacencia()->contarElementos();
}

GPS::~GPS() {
	for (unsigned int i = 0; i < cantidadGrafos; i++) {
		delete grafos[i];
		delete mejoresCostos[i];
		delete[] previosCadaCultivoCadaDestino[i];
	}
	delete[] grafos;
	delete[] mejoresCostos;
	delete[] previosCadaCultivoCadaDestino;
}
