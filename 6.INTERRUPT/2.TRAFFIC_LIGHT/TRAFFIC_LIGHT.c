#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
void enable()
{
	GPIOC->ODR |= 1<<14;
	delay(1000);
	GPIOC->BRR=1<<14;
	delay(1000);
}
void lcd(int rs,int value)
{
	if(rs)
	 GPIOC->ODR=(1<<15);
	else
		GPIOC->BRR=(1<<15);
	GPIOA->ODR=(GPIOA->ODR & 0XFF00) | ((value&0XF0)>>4);//GPIOA->ODR= ((value& 0XF0)>>4);
	enable();
	GPIOA->ODR=(GPIOA->ODR & 0XFF00) | ((value&0X0F));//GPIOA->ODR= (value& 0X0F);
	enable();	
	
}
void string(unsigned char *ptr)
{
	while(*ptr != '\0')
		lcd(1,*ptr++);
}
void EXTI9_5_IRQHandler() 
{                      
	if(EXTI->PR&(1<<8)) 
	{                 //PR = Pending Register
     GPIOB->ODR=0;		
		 GPIOB->BSRR=1<<2;
		 delay(100000);
		 EXTI->PR = 1<<8;
	}
	if(EXTI->PR&(1<<9))
	{
		//lcd(0,0X01);
		lcd(0,0X80);
		string("GREEN");
		delay(100000);
		EXTI->PR = 1<<9;
	}
}

//int b[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
int main()
{
	RCC->CR = 0X83;
	RCC->CFGR = 0X00;
	RCC->APB2ENR |= 1<<0 |1<<2 | 1<<3 |1<<4;
	GPIOA->CRL=0X00002222;
	GPIOB->CRL=0X222;
	GPIOB->CRH=0X88;
	GPIOC->CRH=0X22220000;
	lcd(0,0X02);
	lcd(0,0X28);
	lcd(0,0X0E);
	lcd(0,0X80);  
	AFIO->EXTICR[2]=0x00000011;//AFIO(Alternate Function I/O) determines which GPIO port is connected to each EXTI line.[1] ->PORTB
	//AFIO->EXTICR[2]=0x00000010;
	EXTI->IMR=(1<<8)| (1<<9);//Interrupt Mask Register->Allow EXTI0 to generate an interrupt.
	EXTI->FTSR=0;//Falling Trigger Selection Register.
	EXTI->RTSR=(1<<8) | (1<<9);//Rising Trigger Selection Register.
	NVIC_EnableIRQ(EXTI9_5_IRQn);//Nested Vectored Interrupt Controller.
	while(1)
	{
		GPIOB->ODR=0X00000001;
		delay(100000);
		GPIOB->ODR=0X00000002;
		delay(100000);
		GPIOB->ODR=0X00000004;
		delay(100000);
	}
}