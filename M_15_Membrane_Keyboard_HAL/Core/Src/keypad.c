/**
  ******************************************************************************
  * @file           : keypad.c
  * @brief          : APIs for keypad control
  ******************************************************************************
  */

#include "keypad.h"
#include "main.h"

// Matriz que mapea las posiciones de las teclas en el teclado a sus valores correspondientes.
uint8_t keypad_map[4][4] = {
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'},
};

/**
 * @brief This functions initialize the functionality of the keypad
 * Inicializa el teclado configurando las filas como altas. Esto significa que se establece un voltaje alto en las filas del teclado.
 */
void keypad_init(void)
{
	/* Set the rows high to be detected in the columns by rising interrupt */
	ROW_1_GPIO_Port->BSRR = ROW_1_Pin;
	ROW_2_GPIO_Port->BSRR = ROW_2_Pin;
	ROW_3_GPIO_Port->BSRR = ROW_3_Pin;
	ROW_4_GPIO_Port->BSRR = ROW_4_Pin;
}

/*
 * @brief This function checks which row was pressed
 * Verifica qué fila fue presionada en una columna específica
 * Lo hace activando una fila a la vez y comprobando si la columna sigue siendo alta
 * Si es así, entonces esa fila fue la que se presionó
 */
static uint8_t keypad_validate_column(GPIO_TypeDef *COLUMN_GPIO_Port, uint16_t COLUMN_Pin)
{
	uint8_t row = 0xFF;

	ROW_1_GPIO_Port->BSRR = ROW_1_Pin; // turn on row 1
	ROW_2_GPIO_Port->BRR = ROW_2_Pin;  // turn off row 2
	ROW_3_GPIO_Port->BRR = ROW_3_Pin;  // turn off row 3
	ROW_4_GPIO_Port->BRR = ROW_4_Pin;  // turn off row 4
	HAL_Delay(2); // wait for voltage to establish

	// Comprueba si el pin 1,2,3 o 4 (depende del pin que mande) está en alto -> Si está en alto significa que se presionó la columna 1,2,3 o 4 (depende del pin que mande)
	if (COLUMN_GPIO_Port->IDR & COLUMN_Pin) {
		row = 0; // if column x is still high -> row 1
	}

	ROW_1_GPIO_Port->BRR = ROW_1_Pin; 	// turn off row 1
	ROW_2_GPIO_Port->BSRR = ROW_2_Pin; 	// turn on row 2
	HAL_Delay(2); // wait for voltage to establish
	if (COLUMN_GPIO_Port->IDR & COLUMN_Pin) {
		row = 1; // if column x is still high -> row 2
	}

	ROW_2_GPIO_Port->BRR = ROW_2_Pin; 	// turn off row 2
	ROW_3_GPIO_Port->BSRR = ROW_3_Pin; 	// turn on row 3
	HAL_Delay(2); // wait for voltage to establish
	if (COLUMN_GPIO_Port->IDR & COLUMN_Pin) {
		row = 2; // if column x is still high -> row 3
	}

	ROW_3_GPIO_Port->BRR = ROW_3_Pin;	// turn off row 3
	ROW_4_GPIO_Port->BSRR = ROW_4_Pin; 	// turn on row 4
	HAL_Delay(2); // wait for voltage to establish
	if (COLUMN_GPIO_Port->IDR & COLUMN_Pin) {
		row = 3; // if column x is still high -> row 4
	}

	keypad_init(); // set the columns high again
	return row;
}

/**
 * @brief  This function debounces and identify keypad events.
 * @param  column_to_evaluate: the column where the event happened.
 * @retval 0xFF -> invalid key. [0x00 - 0x0F] -> valid key.
 */
uint8_t keypad_handler(uint16_t column_to_evaluate)
{
	// Se inicializa como valores de error 0xFF -> 255
	uint8_t key_pressed = 0xFF; // Value to return
	uint8_t row = 0xFF;

	/*** Debounce the key press (remove noise in the key) ***/
	#define KEY_DEBOUNCE_MS 300 /*!> Minimum time required for since last press */

	static uint32_t last_pressed_tick = 0;
	if (HAL_GetTick() <= (last_pressed_tick + KEY_DEBOUNCE_MS)) {
		// less than KEY_DEBOUNCE_MS since last press. Probably noise
		return key_pressed; // return 0xFF
	}
	last_pressed_tick = HAL_GetTick();

	/*** Check in which column the event happened ***/
	switch (column_to_evaluate) {
	case COLUMN_1_Pin:
		row = keypad_validate_column(COLUMN_1_GPIO_Port, COLUMN_1_Pin);
		if (row != 0xFF) {
			return keypad_map[row][0];
		}
	  break;

	case COLUMN_2_Pin:
		row = keypad_validate_column(COLUMN_2_GPIO_Port, COLUMN_2_Pin);
		if (row != 0xFF) {
			return keypad_map[row][1];
		}
		break;

	case COLUMN_3_Pin:
		row = keypad_validate_column(COLUMN_3_GPIO_Port, COLUMN_3_Pin);
		if (row != 0xFF) {
			return keypad_map[row][2];
		}
		break;

	case COLUMN_4_Pin:
		row = keypad_validate_column(COLUMN_4_GPIO_Port, COLUMN_4_Pin);
		if (row != 0xFF) {
			return keypad_map[row][3];
		}
		break;

	/*!\ TODO: Implement other column cases here */

	default:
		/* This should not be reached */
	  break;
	}

	return key_pressed; // invalid: 0xFF, valid:[0x00-0x0F]
}
