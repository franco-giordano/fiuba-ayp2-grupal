#ifndef REALIZADORDEACCIONES_H_
#define REALIZADORDEACCIONES_H_

#include "Acciones.h"

class RealizadorDeAcciones{
private:
	unsigned int opcion;
public:
	/*
	 * post: Inicia la opcion en opcionElegida
	 */
	RealizadorDeAcciones();
	/*
	 * post: Dependiendo de la opcion ingresada, se realizar� la accion que se desee. Tambien recibe la dificultad para
	 * las acciones que dependan de ella
	 */
	void realizoAccion(unsigned int opcion, int dificultad);
	/*
	 * post: Le pregunta al jugador en qu� fila de su terreno desea realizar una accion, y la devuelve
	 */
	unsigned int obtenerFila();
	/*
	 * post: Le pregunta al jugador en qu� columna de su terreno desea realizar una accion, y la devuelve
	 */
	unsigned int obtenerColumna();
	/*
	 * post: Le pregunta al jugador en qu� terreno desea realizar una accion, y lo devuelve
	 */
	int obtenerTerreno();
	/*
	 * pre: La parcela tiene que estar libre, y el tiempo de recuperacion de la tierra tiene que ser 0
	 * post: Permite que el jugador compre un cultivo y lo siembre en una parcela, cambiando su estado a plantada
	 */
	void sembrar();
	/*
	 * pre: La parcela tiene que estar ocupada, y el tiempo de cosecha tiene que ser 0
	 * post: Libera la parcela del terreno elegido, y suma los creditos correspondientes a esa cosecha
	 */
	void cosechar();
	/*
	 * pre: La parcela tiene que estar ocupada y no estar regada en ese turno
	 * post: Riega la parcela del terreno deseado, descontando las unidades de riego correspondientes y cambiando el estado
	 * a regada
	 */
	void regar();
	/*
	 *
	 */
	void enviarCosecha();
	/*
	 *
	 */
	void comprarTerreno();
	/*
	 *
	 */
	void venderTerreno();
	/*
	 * post: Amplia la capacidad del tanque, y la dificultad modifica el precio de tal ampliacion
	 */
	void comprarCapacidadTanque(int dificultad);
	/*
	 * post: Amplia la capacidad del almacen, y la dificultad modifica el precio de tal ampliacion
	 */
	void comprarCapacidadAlmacen(int dificultad);
	/*
	 *
	 */
	void pasarTurno();
};

#endif /* REALIZADORDEACCIONES_H_ */