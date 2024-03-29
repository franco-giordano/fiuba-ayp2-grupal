/*
 * lectorArchivos.h
 *
 *  Created on: 9 may. 2018
 *      Author: frank
 */

#ifndef SRC_LECTORCSV_H_
#define SRC_LECTORCSV_H_

#include "Lista.h"
#include <string>
#include <fstream>
#include <sstream>

class LectorCSV {
private:
	Lista<std::string*>* datosGuardados;
	unsigned int parametrosPorLinea;

public:

	//Pre: Recibe la ruta del archivo CSV a analizar como rutaArchivo, y la 'cantidad de datos separados por coma por linea' como cantidadParametros.
	// Post: datosGuardados sera un puntero a una lista , donde cada elemento es una linea representada por un array.
	LectorCSV(std::string rutaArchivo, unsigned int cantidadParametros);

	//Post: Devuelve el puntero a la lista almacenada, dando control al usuario sobre sus datos.
	Lista<std::string*>* obtenerLista();

	//Post: Devuelve la cantidad de parametros por linea del CSV procesado.
	unsigned int obtenerCantParametros();

	~LectorCSV();

};

#endif
