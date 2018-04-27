#include "include.h"


static flash_config_t s_flashDriver;
/*! @brief Buffer for readback */

static uint32_t pflashBlockBase = 0;
static uint32_t pflashTotalSize = 0;
static uint32_t pflashSectorSize = 0;


status_t  Flash_init()
{
	status_t result;
        flash_security_state_t securityStatus = kFLASH_SecurityStateNotSecure;
	memset(&s_flashDriver,0,sizeof(flash_config_t));
	result = FLASH_Init(&s_flashDriver);
	if(result!=kStatus_FLASH_Success)
		return result;
	flash_property_get();
        result = FLASH_GetSecurityState(&s_flashDriver, &securityStatus);
        if (kStatus_FLASH_Success != result)
        {
          return result;
        }
	return result;
}

void flash_property_get()
{
	
    FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflashBlockBaseAddr, &pflashBlockBase);
    FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflashTotalSize, &pflashTotalSize);
    FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflashSectorSize, &pflashSectorSize);
}

//size = {1,4}
status_t flash_write(uint8_t index,size_t size,uint8_t* point)
{
	status_t result;
        uint32_t  failAddr;
        uint32_t  failDat;
	uint32_t destAdrss = pflashBlockBase + (pflashTotalSize - (index * pflashSectorSize));

    result = FLASH_Erase(&s_flashDriver, destAdrss, pflashSectorSize, kFLASH_ApiEraseKey);
    if (kStatus_FLASH_Success != result)
	{
		return result;
	}
	
    result = FLASH_VerifyErase(&s_flashDriver, destAdrss, pflashSectorSize, kFLASH_MarginValueUser);
   if (kStatus_FLASH_Success != result)
	{
		return result;
	}

   	
    result = FLASH_Program(&s_flashDriver, destAdrss, point,size);
    if (kStatus_FLASH_Success != result)
	{
		return result;
	}
    
      result = FLASH_VerifyProgram(&s_flashDriver, destAdrss, size, point, kFLASH_MarginValueUser,
                                     &failAddr, &failDat);
        if (kStatus_FLASH_Success != result)
        {
            return result;
        }

	return result;	
}

void flash_read(uint8_t index,size_t size,uint8_t* data)
{
	
    uint32_t destAdrss = pflashBlockBase + (pflashTotalSize - (index * pflashSectorSize));
    SCB_CleanInvalidateDCache();
    for (uint32_t i = 0; i < size; i++)
    {
       data[i] = *(uint8_t*)(destAdrss + i);
    }

}
