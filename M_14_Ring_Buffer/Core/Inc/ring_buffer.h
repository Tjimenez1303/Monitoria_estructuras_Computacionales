/*
 * ring_buffer.h
 *
 *  Created on: Oct 23, 2023
 *      Author: jChoc
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>

// Estructura Ring Buffer
typedef struct {
	uint8_t *buffer;  /*!\ Pointer to memory location */
	uint16_t head;    /*!\ To write new data */
	uint16_t tail;    /*!\ To read old data */

	uint16_t capacity;
	uint8_t is_full;

} ring_buffer_t;

// Definimos la función de inicialización del Ring buffer
void ring_buffer_init(ring_buffer_t *ring_buffer, uint8_t *buffer, uint16_t capacity);

// Definimos la función que agrega datos al Ring buffer
void ring_buffer_put(ring_buffer_t *ring_buffer, uint8_t data);

// Definimos la función que lee datos desde el Ring buffer
uint8_t ring_buffer_get(ring_buffer_t *ring_buffer, uint8_t *data);

// Definimos la  función que devuelve el tamaño actual del Ring buffer
uint16_t ring_buffer_size(ring_buffer_t *ring_buffer);

#endif /* INC_RING_BUFFER_H_ */
