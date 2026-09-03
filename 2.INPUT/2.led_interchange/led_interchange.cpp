#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
int main()
{
	int count=0;
	unsigned int on=0;
	unsigned int off=1;
	RCC->CR=0X00000083;
	RCC->CFGR=0X00000000;
	RCC->APB2ENR=0X00000004;
	GPIOA->CRL=0X00000002; //PA0-OUTPUT - 0010 -> 00 MEANS OUTPUT ; 10 MEANS 2MHZ
	GPIOB->CRL=0X00000888; //PB0 , PB1, PB2 - INPUT - 1000 -> 10 -INPUT
	while(1)
	{
		if(GPIOB->IDR & 1<<0)
		{
			GPIOA->ODR=on;//0X00000001;
			delay(100000);
			while(GPIOB->IDR & 1<<0);
		}
		
		if(GPIOB->IDR &1<<1)
		{
				GPIOA->ODR=off;
				delay(100000);	
			  while(GPIOB->IDR &1<<1);
		}
		if(GPIOB->IDR &1<<2)
		{
			count++;
			while(GPIOB->IDR &1<<2);
		}
		if(count%2==0)
		{
			on=1;
			off=0;		
		}
		else
		{
			on=0;
			off=1;
		}
	}
}
