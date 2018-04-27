#include "MKV58F24.h"
#include "AetherDriver_GPIO.h"

__ramfunc void gpio_init(GPIO_Type *base,uint32_t pin,director status,Logic level)
{
    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
                 | SIM_SCGC5_PORTB_MASK
                 | SIM_SCGC5_PORTC_MASK
                 | SIM_SCGC5_PORTD_MASK
                 | SIM_SCGC5_PORTE_MASK );
                 
    switch((uint32_t)base){
        case (uint32_t)GPIOA:
            PORTA->PCR[pin] = (PORTA->PCR[pin] & ~PORT_PCR_MUX_MASK)|(1U<<PORT_PCR_MUX_SHIFT);
            break;
        case (uint32_t)GPIOB:
            PORTB->PCR[pin] = (PORTB->PCR[pin] & ~PORT_PCR_MUX_MASK)|(1U<<PORT_PCR_MUX_SHIFT);
            break;
        case (uint32_t)GPIOC:
            PORTC->PCR[pin] = (PORTC->PCR[pin] & ~PORT_PCR_MUX_MASK)|(1U<<PORT_PCR_MUX_SHIFT);
            break;
        case (uint32_t)GPIOD: 
            PORTD->PCR[pin] = (PORTD->PCR[pin] & ~PORT_PCR_MUX_MASK)|(1U<<PORT_PCR_MUX_SHIFT);
            break;
        case (uint32_t)GPIOE: 
            PORTE->PCR[pin] = (PORTE->PCR[pin] & ~PORT_PCR_MUX_MASK)|(1U<<PORT_PCR_MUX_SHIFT);
            break;
    }
    
    if(status){
        base->PDDR |= (1U<<pin);
        if(level==HIGH)
        {
          base->PDOR |= (1U<<pin);
        }else{
          base->PDOR &= ~(1U<<pin);
        }
    }else{
        base->PDDR &= ~(1U<<pin);
    }
}

__ramfunc void gpio_write(GPIO_Type *base,uint32_t pin,Logic level)
{
    if(level==HIGH)
    {
        base->PDOR |= (1U<<pin);
    }else{
        base->PDOR &= ~(1U<<pin);
    }
}

__ramfunc uint32_t gpio_read(GPIO_Type *base,uint32_t pin)
{
    return (((base->PDIR) >> pin) & 0x01U);
}

__ramfunc void gpio_reserve(GPIO_Type *base,uint32_t pin)
{
    base->PTOR |=(1U<<pin);
}
