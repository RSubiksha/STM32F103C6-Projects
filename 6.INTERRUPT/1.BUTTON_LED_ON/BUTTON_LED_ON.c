#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
void EXTI0_IRQHandler() //When PA0 generates an interrupt, the processor automatically jumps to this function
{                       //EXTI0 -> EXTERNAL INTERRUPT LINE 0
	if(EXTI->PR&1<<0) //Did EXTI line 0 generate the interrupt?
	{                 //PR = Pending Register
		GPIOC->BRR=1<<13;//Turn OFF PC13 LED
		GPIOB->ODR=1<<0;//Turn ON PB0 LED
		delay(100000);
		GPIOB->BRR=1<<0;
	}
	EXTI->PR=1<<0;//which clears the pending condition for EXTI0.
}
int main()
{
	RCC->CR=0X83;
	RCC->CFGR=0X00;
	RCC->APB2ENR=1<<2|1<<0|1<<3|1<<4;
	GPIOA->CRL=0X00000008;//PA0 ->INPUT -> BUTTON
	GPIOB->CRL=0X00000002;//PB0 -> OUTPUT ->LED
	GPIOC->CRH=0X00200000;//PC13 ->OUTPUT ->LED
	AFIO->EXTICR[0];//AFIO(Alternate Function I/O) determines which GPIO port is connected to each EXTI line.[0] ->PORTA
	EXTI->IMR=1<<0;//Interrupt Mask Register->Allow EXTI0 to generate an interrupt.
	EXTI->FTSR=0;//Falling Trigger Selection Register.
	EXTI->RTSR=1<<0;//Rising Trigger Selection Register.
	NVIC_EnableIRQ(EXTI0_IRQn);//Nested Vectored Interrupt Controller.
	while(1)
	{
		GPIOC->ODR=1<<13;
	}
}

/*
2 LEDS , 1 BUTTON
WHEN U RUN THE CODE, LED CONNECTED TO PC13 WILL GLOW
WHEN U PRESS THE BUTTON, LED CONNECTED TO PB0 WILL GLOW (INTERRUPT)
*/