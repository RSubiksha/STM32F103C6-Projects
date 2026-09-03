#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
int b[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
int j,i;
int main()
{
	RCC->CR=0X00000083;
	RCC->CFGR=0X00000000;
	RCC->APB2ENR=0X00000004;
	GPIOA->CRL=0X22222222;
	GPIOA->CRH=0X22222222;
	while(1)
	{
		for(i=0;i<=1000;i++)
		{
			for(j=0;j<30;j++)
			{
				GPIOA->ODR = 0X0100 | b[i/10];
				delay(1000);
				GPIOA->BRR = 0X0100;
				GPIOA->ODR = 0X0200 | b[i%10];
				delay(1000);	
				GPIOA->BRR = 0X0200;
				GPIOA->ODR = 0X0400 | b[9-(i/10)];
				delay(1000);	
				GPIOA->BRR = 0X0400;
				GPIOA->ODR = 0X0800 | b[9-(i%10)];
				delay(1000);	
        GPIOA->BRR = 0X0800;				
			}
		}
	}
	return 0;
}