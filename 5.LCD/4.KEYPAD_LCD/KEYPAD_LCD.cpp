#include<stm32f10x.h>

void delay(uint32_t a)
{
	while(a--);
}

void enable()
{
	GPIOB->BSRR=1<<8;		// EN = PB8
	delay(1000);
	GPIOB->BRR=1<<8;
	delay(1000);
}

void lcd(int rs,int value)
{
	/*if(rs)
		GPIOB->BSRR=1<<9;	// RS = PB9
	else
		GPIOB->BRR=1<<9;

	GPIOA->ODR = 0x00 | value;  // 0x00000000  |  65 = 0x
	enable();
	*/
	if(rs)
		GPIOB->BSRR=1<<9;
	else
		GPIOB->BRR=1<<9;

	GPIOB->ODR &= ~0x00FF;
	GPIOB->ODR |= value;

	enable();
}

void string(char *ptr)
{
	while(*ptr)
		lcd(1,*ptr++);
}

int b[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};

int i=0;

int main()
{
	RCC->CR=0X83;
	RCC->CFGR=0X00;
	RCC->APB2ENR=0X1C;

	GPIOA->CRL=0X22222222;
	GPIOB->CRL=0X22222222;
	GPIOB->CRH=0X8822;

	lcd(0,0X38);
	lcd(0,0X0C);
	lcd(0,0X01);
	delay(50000);
	lcd(0,0X80);

	string("count:");

	while(1)
	{
		if(GPIOB->IDR & (1<<10))
		{
			if(i<9)
				i++;

			while(GPIOB->IDR & (1<<10));

			GPIOA->ODR=b[i];
			delay(50000);

			lcd(0,0X86);
			lcd(1,'0'+i);
		}

		if(GPIOB->IDR & (1<<11))
		{
			if(i>0)
				i--;

			while(GPIOB->IDR & (1<<11));

			GPIOA->ODR=b[i];
			delay(50000);

			lcd(0,0X86);
			lcd(1,'0'+i);
		}
	}
}