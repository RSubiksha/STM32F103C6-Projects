#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
int main()
{
	int i=0;
	RCC->CR=0X00000083;//1000 0011 - BIT 7-HSITRIM, BIT 1 - HSIRDY, BIT 0 - HSION
	RCC->CFGR=0X00000000;//DEFAULT CONFIGURATION
	RCC->APB2ENR=0X0000001C;// 0001 1100 - bit2- i/o port A clock enable ; bit 3 , bit 4 - port B and C clock enable
	GPIOA->CRL=0X22222222;
	while(1)
	{
			for(i=0;i<=7;i++)
			{
				GPIOA->ODR=1<<i;
				delay(100000);
			}
	}
	return 0;
}