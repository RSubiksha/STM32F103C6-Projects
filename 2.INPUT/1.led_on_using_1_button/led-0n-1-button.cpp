#include <stm32f10x.h>              // Include STM32F10x microcontroller header file
int delay(uint32_t a)               // Create a software delay function
{
    while(a--);                     // Decrease 'a' until it becomes zero
}
int loop=0;
int main()                          // Main program starts here
{
    RCC->CR = 0x00000083;           // Configure RCC Clock Control Register -          internal osc upto 16 MHz
    RCC->CFGR = 0x00000000;         // Configure system clock and bus prescalers
    RCC->APB2ENR = 0x0000001C;      // Enable clock for GPIOA, GPIOB and GPIOC
                                    // Bit 2 = GPIOA clock
                                    // Bit 3 = GPIOB clock
                                    // Bit 4 = GPIOC clock
    GPIOA->CRL = 0x00000002;        // Configure PA0 as 2 MHz push-pull outputs
    GPIOB->CRL = 0x00000008;        //- pb0- input
    while(1)                        // Infinite loop: program runs continuously
    {
			if(GPIOB->IDR&1<<0)
			{
				loop=1;
			}
			if(loop==1)
			{
        GPIOA->ODR = 0x00000001;    // Set PA0 HIGH
        delay(100000);              // Wait for some time
        GPIOA->BRR = 0x00000001;    
        delay(100000);              // Wait for some time before repeating
			}
			loop=0;
    }
}