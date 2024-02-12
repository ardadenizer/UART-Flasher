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

typedef uint32_t FlashAddressType;

typedef enum
{
	JOB_STATUS_PENDING,
	JOB_STATUS_IN_PROGRESS,
	JOB_STATUS_COMPLETED,
	JOB_STATUS_ERROR
}e_FlashJobStatus;

typedef enum
{
  FLS_OK       = 0x00U,
  FLS_ERROR    = 0x01U,
  FLS_BUSY     = 0x02U,
  FLS_TIMEOUT  = 0x03U
} e_FlashReturnStatus;

uint32_t Flash_Write_Syc (uint32_t StartSectorAddress, uint32_t *Data, uint16_t numberofwords);

e_FlashReturnStatus Flash_Read(FlashAddressType Address, void* Data, uint32_t Size );

//SectorType Get_Sector(FlashAddressType StartSectorAddress )

#endif /* INC_FLASH_H_ */
