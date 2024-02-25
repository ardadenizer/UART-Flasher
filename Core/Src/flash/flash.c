/**
  ******************************************************************************
  * @file    flash.c
  * @brief   This file provides code for flash APIs.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) Arda Denizer.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "flash.h"

e_FlashReturnStatus Flash_Erase_Sectors(const uint8_t StartSector, const uint8_t SectorCount)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
    e_FlashReturnStatus RetStatus 	= FLS_ERASE_ERROR;
    e_FlashJobStatus JobStatus     	= JOB_STATUS_IN_PROGRESS;
    uint32_t *SectorError 			= NULL;

    if (StartSector <= START_SECTOR_LIMIT)
    {
    	RetStatus = FLS_COND_ERROR;
    }
    else
    {
    	/* Unlock the Flash to enable the flash control register access */
		HAL_FLASH_Unlock();

		/* Fill EraseInit structure */
		EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
		EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
		EraseInitStruct.Sector = StartSector;
		EraseInitStruct.NbSectors = SectorCount;

		// Erase Sectors, Blocking function
		// TODO: Experiment with while loop, when erasing is completed
		if (HAL_OK != HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError))
		{
			RetStatus = FLS_ERASE_ERROR;
			HAL_FLASH_Lock();
			return RetStatus;
		}
		else
		{
			/* Lock the Flash to disable the flash control register access */
			HAL_FLASH_Lock();
			JobStatus = JOB_STATUS_COMPLETED;
			RetStatus = FLS_OK;
		}
    }
    return RetStatus;
}

e_FlashReturnStatus Flash_Mass_Erase(void)
{
//	static FLASH_EraseInitTypeDef EraseInitStruct;
	e_FlashReturnStatus RetStatus 	= FLS_ERASE_ERROR;
//	e_FlashJobStatus JobStatus     	= JOB_STATUS_IN_PROGRESS;
//	uint32_t *SectorError 			= NULL;
	return RetStatus;
}

e_FlashReturnStatus Flash_Write_Syc (FlashAddressType StartAddress, uint8_t *Data, size_t DataLength)
{
    e_FlashReturnStatus RetStatus  = FLS_WRITE_ERROR;
    e_FlashJobStatus JobStatus     = JOB_STATUS_IN_PROGRESS;
    uint32_t DataIndex             = 0u;

    /* Unlock the Flash to enable the flash control register access */
    HAL_FLASH_Unlock();

    /* Program the user Flash area word by word */
    while (DataIndex < DataLength)
    {
        if (HAL_OK == HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, StartAddress, Data[DataIndex]))
        {
        	StartAddress += 1u; // Increment by the size of a byte
            DataIndex++;
        }
        else
        {
            RetStatus = FLS_WRITE_ERROR;
            return HAL_FLASH_GetError();
        }
    }

    /* Lock the Flash to disable the flash control register access */
    HAL_FLASH_Lock();
    JobStatus = JOB_STATUS_COMPLETED;

    return RetStatus;
}

e_FlashReturnStatus Flash_Read(FlashAddressType Address, void* Data, uint32_t Size )
{
	FlashAddressType* p_Address 	= (FlashAddressType*)Address;
	e_FlashJobStatus JobStatus   	=  JOB_STATUS_IN_PROGRESS;
	e_FlashReturnStatus	RetStatus 	= FLS_READ_ERROR;

	if ((NULL != p_Address) && ( Size > 0))
	{
		size_t numBytesToCopy = Size * sizeof(*Data);

		(void*)memcpy(Data,(void*)Address, numBytesToCopy);
		JobStatus   =  JOB_STATUS_COMPLETED;
		RetStatus	= FLS_OK;
	}
	else
	{
		RetStatus = FLS_COND_ERROR;
	}

	return RetStatus;
}

e_FlashReturnStatus Flash_Get_Voltage_Range(void)
{

}
