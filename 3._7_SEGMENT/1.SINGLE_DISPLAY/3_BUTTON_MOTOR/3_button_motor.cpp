#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
int b[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
int i,count=0;
int main()
{
	RCC->CR=0X83;
	RCC->CFGR=0X00;
	RCC->APB2ENR=0X1C;
	GPIOA->CRL=0X22222222; // 8 PIN OUTPUT
	GPIOB->CRL=0X0888; //3 PIN - INPUT
	GPIOB->CRH=0X22222222; //2 PIN OUTPUT
	while(1)
	{
		if(GPIOB->IDR&1<<0)
		{
			i++;
			while(GPIOB->IDR&1<<0);
		}
		if(GPIOB->IDR&1<<1)
		{
			i--;
			while(GPIOB->IDR&1<<1);
		}
		if(GPIOB->IDR&1<<2)
		{
			for(count=i;count>=0;count--)
			{
				GPIOB->ODR=0X2000;
				GPIOA->ODR=b[count];
				delay(100000);
			}
			GPIOB->BRR=0X2000;
			i=0;
			while(GPIOB->IDR&1<<2);
		}
		GPIOA->ODR=b[i];
	}
}