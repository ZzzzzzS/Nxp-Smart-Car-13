#ifndef __AETHERDRIVER_GPIO__
#define __AETHERDRIVER_GPIO__

typedef enum{
    OUT=1,
    IN=0
}director;

typedef enum{
    LOW=0,
    HIGH=1
}Logic;

extern __ramfunc void gpio_init(GPIO_Type *base,uint32_t pin,director status,Logic level);
extern __ramfunc uint32_t gpio_read(GPIO_Type *base,uint32_t pin);
extern __ramfunc void gpio_write(GPIO_Type *base,uint32_t pin,Logic level);
extern __ramfunc void gpio_reserve(GPIO_Type *base,uint32_t pin);

#endif