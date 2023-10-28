#include "ring_buffer.h"

/**
 * @brief Esta función inicializa la estructura de control de Ring buffer

 * 	@param 	ring_buffer: 	Puntero a una estructura de tipo de Ring buffer
 * 	@param  buffer: 		Puntero a un arreglo que se utilizará como buffer real
 * 	@param	capacity: 		Valor de la capacidad máxima del Ring buffer
*/
void ring_buffer_init(ring_buffer_t *ring_buffer, uint8_t *buffer, uint16_t capacity)
{
	ring_buffer->buffer = buffer; // Se asigna a la estructura ring_buffer donde encontrará el buffer de datos
	ring_buffer->capacity = capacity; // Se asigna la capacidad máxima del Ring buffer

	ring_buffer->head = 0; // Se inicializa la head del Ring buffer
	ring_buffer->tail = 0; // Se inicializa la cola del Ring buffer
	ring_buffer->is_full = 0; // Se inicializa la bandera para saber si hay datos en el buffer
}


/**
 * @brief This function adds a data in the ring buffer
 *
 * @param ring_buffer: 	Puntero a una estructura de tipo de Ring buffer
 * @param data: 		Valor que va a ser añadido al Ring buffer
*/
void ring_buffer_put(ring_buffer_t *ring_buffer,uint8_t data)
{
	// Coloca el valor "data" en la posición actual que va la head
	ring_buffer->buffer[ring_buffer->head] = data;

	// Incrementamos el puntero de escritura al siguiente elemento y si ya se superó la capacidad máxima del Ring buffer  lo rebobina al principio
	ring_buffer->head = (ring_buffer->head + 1) % ring_buffer->capacity;

	// Verificamos si el Ring buffer está lleno
	if (ring_buffer->is_full != 0){
		// Si el Ring buffer está lleno incrementamos la cola y se devuelve al principio si es necesario
		ring_buffer->tail = (ring_buffer->tail + 1) % ring_buffer->capacity;
	}

	// Verificamos si la cabeza alcanzó la cola
	if (ring_buffer->head == ring_buffer->tail){
		ring_buffer->is_full = 1;
	}
}


/**
 * @brief Esta función lee los datos del Ring buffer
 *
 * @param ring_buffer: 	Puntero a una estructura de tipo de Ring buffer
 * @param data: 		Puntero a la dirección en la que se escribirán los datos
*/
uint8_t ring_buffer_get(ring_buffer_t *ring_buffer, uint8_t *data)
{
	// Verificamos si el buffer está lleno || Verificamos si hay datos para leer
	if ((ring_buffer->is_full != 0) || (ring_buffer->tail != ring_buffer->head)){

		// Asigna el valor en la posición actual de la cola a la dirección de memoria donde se escribirán los datos
		*data = ring_buffer->buffer[ring_buffer->tail];

		// Incrementamos la cola y se devuelve al principio si es necesario
		ring_buffer->tail = (ring_buffer->tail + 1) % ring_buffer->capacity;

		// Indicamos que el Ring buffer ya no está lleno
		ring_buffer->is_full = 0;

		// Se capturaron exitosamente los datos del Ring buffer
		return 1;
	}
	// No hay datos válidos o está vacío en el ring_buffer
	return 0;
}


/**
 * @brief Esta función devuelve el tamaño del Ring buffer
*/
uint16_t ring_buffer_size(ring_buffer_t *ring_buffer)
{
	uint16_t size = 0;

	/* Verificamos que el buffer no esté lleno y verificamos que la cola sea menor o igual que la cabeza -> Si se cumplen ambas condiciones
	 *significa que el Ring buffer no está en un estado circular
	 *y se puede calcular el tamaño directamente como la diferencia entre la cabeza y la cola
	*/
	if ((ring_buffer->is_full == 0) && (ring_buffer->tail <= ring_buffer->head)) {

		// Calculamos el tamaño
		size = ring_buffer->head - ring_buffer->tail;
	}
	else { // El Ring buffer está en un estado circular

		// Calculamos el tamaño
		size = ring_buffer->head + (ring_buffer->capacity - ring_buffer->tail);
	}

	return size;
}
