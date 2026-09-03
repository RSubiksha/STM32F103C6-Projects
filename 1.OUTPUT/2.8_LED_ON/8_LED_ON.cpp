#include<stm32f10x.h>
int delay(uint32_t a)
{
	while(a--);
}
int main()
{
	RCC->CR=0X00000083;//1000 0011 - BIT 7-HSITRIM, BIT 1 - HSIRDY, BIT 0 - HSION
  RCC->CFGR = 0X00000000; //DEFAULT CONFIGURATION
	RCC->APB2ENR = 0X0000001C;// 0001 1100 - bit2- i/o port A clock enable ; bit 3 , bit 4 - port B and C clock enable
	GPIOA->CRL=0X22222222; // 0010 - 00: General purpose output push-pull ; 10: Output mode, max speed 2 MHz.
	//GPIOA->CRH=0X22222222;
	while(1)
	{
		GPIOA->ODR=0X0000FFFF; //FFFF - PORTA'S 8 PIN ON
		delay(100000);
		GPIOA->BRR=0X0000FFFF;//PORTA'S 8 PINS OFF
		delay(100000);
	}
	return 0;
}