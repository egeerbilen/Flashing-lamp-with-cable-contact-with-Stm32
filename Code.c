#include "stm32f10x.h"
void SysTick_Handler(void){
	if(GPIOC -> ODR | (0<<13)){
		GPIOC -> ODR &=~ (1<<13);
	}
	else {
		GPIOC -> ODR |= (1<<13);
	}
}
void EXTI15_10_IRQHandler(void){
	if((EXTI -> PR & (1<<14)) != 0){
		SysTick -> LOAD = 50*(72000000/8000);       
		SysTick -> CTRL=3;
		EXTI -> PR |= (1<<14);
	}
}
int main()
{
	RCC -> APB2ENR |= ((1<<4)|1); 
	GPIOC-> CRH |= ((1<<27));
	GPIOC -> CRH &=~ ((1<<24)|(1<<25)|(1<<26));
	GPIOC -> CRH |= ((1<<20)|(1<<21));
	GPIOC -> CRH &=~ ((1<<23)|(1<<22));
	AFIO->EXTICR[3] |= 1<<9;
	AFIO->EXTICR[3] &=~ ((1<<11)|(1<<10)|(1<<8)); 
	EXTI->FTSR |= 1<<14; 
	EXTI->RTSR |= 1 <<14; 
	EXTI->IMR |= 1<<14; 
	NVIC_EnableIRQ(EXTI15_10_IRQn);  
	while(1){ }
}
