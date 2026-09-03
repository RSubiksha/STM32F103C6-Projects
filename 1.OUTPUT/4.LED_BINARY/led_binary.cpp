#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
int main()
{
	int i=0;
	RCC->CR=0X00000083;
	RCC->CFGR=0X00000000;
	RCC->APB2ENR=0X00000004;
	GPIOA->CRL=0X22222222;
	while(1)
	{
		for(i=0;i<=15;i++)
		{
			GPIOA->ODR=i;
			delay(100000);
		}
	}
	return 0;
}