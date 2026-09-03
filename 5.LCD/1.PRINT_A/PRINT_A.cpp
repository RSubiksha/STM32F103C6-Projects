#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
void enable()
{
	GPIOB->BSRR=1<<1;//enable pin is connected to PB1
	delay(10);
	GPIOB->BRR=1<<1;
	delay(10);
}
void lcd(int rs,int value)
{
	if(rs)
	GPIOB->BSRR=1<<0;
	else
	GPIOB->BRR=1<<0;
	GPIOA->ODR = 0x00 | value;
	enable();
}	
int main()
{
	RCC->CR=0X83;
	RCC->CFGR=0X00;
	RCC->APB2ENR=0X1C;
	GPIOA->CRL=0X22222222;
	GPIOB->CRL=0X22;
	lcd(0,0X38);
	lcd(0,0X0E);
	lcd(0,0X80);
	while(1)
	{
		lcd(0,0X80);
		lcd(1,'A');
		while(1);
	}
	return 0;
}