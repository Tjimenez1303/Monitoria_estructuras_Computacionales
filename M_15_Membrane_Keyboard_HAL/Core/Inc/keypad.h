/*
 * keypad.h
 *
 *  Created on: Nov 8, 2023
 *      Author: saaci
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include <stdint.h>

void keypad_init(void);
uint8_t keypad_handler(uint16_t column_to_evaluate);


#endif /* INC_KEYPAD_H_ */
