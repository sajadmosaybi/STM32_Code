/*
 * Lib.h
 *
 *  Created on: Feb 13, 2025
 *      Author: micha_koki
 */

#ifndef INC_LIB_H_
#define INC_LIB_H_

#include "stdbool.h"

extern struct Uart{
	bool Event_Flag;
	bool ready;
	uint8_t Rx_buffer[1];
	uint8_t ptr;
	uint8_t buffer[20];
	uint8_t command[20];


}Uart;


#endif /* INC_LIB_H_ */
