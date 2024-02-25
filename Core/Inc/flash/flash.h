/*
 * flash.h
 *
 *  Created on: Feb 11, 2024
 *      Author: Arda Denizer
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include <stdint.h>
#include <string.h>
#include "stm32f4xx_hal.h"

#define START_SECTOR_LIMIT (4u)

typedef uint32_t FlashAddressType;

typedef enum
{
	JOB_STATUS_PENDING,
	JOB_STATUS_IN_PROGRESS,
	JOB_STATUS_COMPLETED,
	JOB_STATUS_ERROR
}e_FlashJobStatus;


//TODO: Conditions not correct, read/write error...
typedef enum
{
  FLS_OK       		= 0x00U,
  FLS_READ_ERROR    = 0x01U,
  FLS_WRITE_ERROR   = 0x02U,
  FLS_ERASE_ERROR   = 0x03U,
  FLS_COND_ERROR    = 0x04U,
  FLS_BUSY     		= 0x05U,
  FLS_TIMEOUT  		= 0x06U
} e_FlashReturnStatus;

e_FlashReturnStatus Flash_Write_Syc (FlashAddressType StartAddress, uint8_t *Data, size_t DataLength);

e_FlashReturnStatus Flash_Read(FlashAddressType Address, void* Data, uint32_t Size );

e_FlashReturnStatus Flash_Erase_Sectors(uint8_t StartSector,uint8_t SectorCount);

e_FlashReturnStatus Flash_Mass_Erase(void);

e_FlashReturnStatus Flash_Get_Voltage_Range(void);

//SectorType Get_Sector(FlashAddressType StartSectorAddress )

#endif /* INC_FLASH_H_ */
