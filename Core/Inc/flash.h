/*
 * flash.h
 *
 *  Created on: Feb 11, 2024
 *      Author: Arda Denizer
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

//TODO: flash bool type?
uint32_t Flash_Write_Data (uint32_t StartSectorAddress, uint32_t *Data, uint16_t numberofwords);
uint32_t Flash_Read_Data(void);

#endif /* INC_FLASH_H_ */
