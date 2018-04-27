#ifndef __AETHERDRIVER_FLASH__
#define __AETHERDRIVER_FLASH__ 

extern void flash_read(uint8_t index,size_t size,uint8_t* data);
extern status_t flash_write(uint8_t index,size_t size,uint8_t* point);
extern void flash_property_get();
extern status_t  Flash_init();



#endif 
