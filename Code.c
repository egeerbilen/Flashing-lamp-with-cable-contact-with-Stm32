#include "stm32f10x.h"
int main()
{
		RCC -> APB2ENR |= (1<<4); 
		GPIOC -> CRH |=(1<<27);	
		GPIOC -> CRH &=~((1<<26)|(1<<25)|(1<<24)); 
		
		GPIOC -> CRH |=((1<<21)|(1<<20));	
		GPIOC -> CRH &=~((1<<23)|(1<<22));	

		GPIOC -> ODR |= (1<<13);  
    while(1){				
        while(!(GPIOC->IDR&(1<<14)));
        while(GPIOC->IDR&(1<<14));
        for(int i=0;i<5;i++)
        {
					GPIOC -> ODR |=(1<<13);	
					for(int j = 0; j<2000000 ;j++); 
					GPIOC -> ODR &=~(1<<13); 
					for(int j= 0; j<2000000 ;j++);
        }
			GPIOC -> ODR |= (1<<13); 

    }
}