#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
int main()
{
	int i=0,a=0,count=7;
	RCC->CR=0x00000083;
	RCC->CFGR=0x00000000;
	RCC->APB2ENR=0X00000004;
	GPIOA->CRL=0X22222222;
	while(1)
	{
		for(i=0;i<=7;i++)
		{
			GPIOA->ODR=1<<i|a;
			delay(10000);
		}
		a=a|1<<count--;
		if(count==0)
		{
			for(i=0;i<=7;i++)
			{
				GPIOA->ODR &= ~(1 << i);
				delay(100000);
			}
			a=0;count=7;
		}
		
	}
	return 0;
}