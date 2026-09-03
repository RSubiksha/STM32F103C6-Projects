#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
void enable()
{
	GPIOC->ODR|=1<<14;
	delay(100);
	GPIOC->BRR=1<<14;
	delay(100);
}
void lcd(int rs,int value)
{
	if(rs)
		GPIOC->ODR=1<<15;
	else
		GPIOC->BRR=1<<15;
	
	GPIOA->ODR=((value & 0XF0)>>4);
	enable();
	GPIOA->ODR=(value & 0X0F);
	enable();
	
}
void string(char *p)
{
	while(*p)
		lcd(1,*p++);
}
int i=0,j;
int b[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
int main()
{
	RCC->CR=0X83;
	RCC->CFGR=0X00;
	RCC->APB2ENR=0X1C;
	GPIOA->CRL=0X22222222;
	GPIOB->CRL=0X22222222;
	GPIOB->CRH=0X22222222;
	GPIOC->CRH=0X22222222;
	lcd(0,0X02);
	lcd(0,0X28);
	//lcd(0,0X01);
	//delay(50000);
	lcd(0,0X0E);
	lcd(0,0XC0);
	string("count:");
	while(1)
	{
		for(i=0;i<10000000;i++)
		{
			for(j=0;j<5;j++)
			{
				GPIOB->ODR=0XFE00 | b[i/1000];
				delay(100);
				
				GPIOB->ODR=0XFD00 | b[(i/100)%10];
				delay(100);
				
				GPIOB->ODR=0XFB00 | b[(i%100)/10];
				delay(100);
				
				GPIOB->ODR=0XF700 | b[(i%10)];
				delay(100);
				
				GPIOB->ODR=0XEF00 | b[9-(i/1000)];
				delay(100);
				
				GPIOB->ODR=0XDF00 | b[9-((i/100)%10)];
				delay(100);
				
				GPIOB->ODR=0XBF00 | b[9-((i%100)/10)];
				delay(100);
				
				GPIOB->ODR=0X7F00 | b[9-(i%10)];
				delay(100);
		/* LCD */
    lcd(0,0XC6);

    lcd(1,'0'+(i/1000)%10);
    lcd(1,'0'+(i/100)%10);
    lcd(1,'0'+(i/10)%10);
    lcd(1,'0'+i%10);

    lcd(1,'0'+(9-(i/1000)%10));
    lcd(1,'0'+(9-(i/100)%10));
    lcd(1,'0'+(9-(i/10)%10));
    lcd(1,'0'+(9-i%10));
			}
		}
	}
}