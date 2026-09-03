#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
	int n=0,i;
	int b[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
int main()
{
	RCC->CR=0X83;
	RCC->CFGR=0X00;
	RCC->APB2ENR=0X1C; //PORTA,A,C - CLOCK ENABLE
	GPIOA->CRL=0X22222222;
	GPIOA->CRH=0X2222;
	GPIOB->CRL=0X02222888;//PB0 TO 2 ->INPUT (8); PB3 TO 3 ->OUTPUT(2)
	
	while(1)
	{
		GPIOB->ODR=0X08;//PA3=1;PA4=0;PA5=0;PA6=0
		if(GPIOB->IDR&1<<0)//to check where user pressed 1
		{
			GPIOA->ODR=b[1];
			i=1;
			n=(n*10)+i;
			while(GPIOB->IDR& (1<<0));
			delay(5000);
		}
		if(GPIOB->IDR&1<<1)
		{
			GPIOA->ODR=b[2];
			i=2;
			n=(n*10)+i;
			while(GPIOB->IDR& (1<<1));
			delay(5000);
		}
		if(GPIOB->IDR&1<<2)
		{
			GPIOA->ODR=b[3];
			i=3;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<2));
			delay(5000);
		}
		
		delay(10);
		GPIOB->ODR=0X10;//PA3=0;PA4=1;PA5=0;PA6=0
		if(GPIOB->IDR&1<<0)//to check where user pressed 4
		{
			GPIOA->ODR=b[4];
			i=4;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<0));
			delay(5000);
		}
		if(GPIOB->IDR&1<<1)
		{
			GPIOA->ODR=b[5];
			i=5;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<1));
			delay(5000);
		}
		if(GPIOB->IDR&1<<2)
		{
			GPIOA->ODR=b[6];
			i=6;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<2));
			delay(5000);
		}
		delay(10);
		
		
		GPIOB->ODR=0X20;//PA3=0;PA4=0;PA5=1;PA6=0
		if(GPIOB->IDR&1<<0)//to check where user pressed 7
		{
			GPIOA->ODR=b[7];
			i=7;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<0));
			delay(5000);
		}
		if(GPIOB->IDR&1<<1)
		{
			GPIOA->ODR=b[8];
			i=8;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<1));
			delay(5000);
		}
		if(GPIOB->IDR&1<<2)
		{
			GPIOA->ODR=b[9];
			i=9;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<2));
			delay(5000);
		}
		delay(10);
		
		GPIOB->ODR=0X40;//PA3=0;PA4=0;PA5=0;PA6=1;
		if(GPIOB->IDR&(1<<1))
		{
			GPIOA->ODR=b[0];
			i=0;
			n=(n*10)+i;
			while(GPIOB->IDR&1<<1);
			delay(5000);
		}
		delay(10);
	
		GPIOA->ODR=0X0E00 | b[n/1000];
		delay(1000);

		GPIOA->ODR=0X0D00 | b[(n/100)%10];
		delay(1000);

		GPIOA->ODR=0X0B00 | b[(n%100)/10];
		delay(1000);

		GPIOA->ODR=0X0700 | b[n%10];
		delay(1000);	
	
	}
}

/*
#include<stm32f10x.h>

void delay(uint32_t a)
{
	while(a--);
}
int n=0,i;
int b[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
int main()
{
	

	RCC->CR=0X83;
	RCC->CFGR=0X00;
	RCC->APB2ENR=0X1C;

	GPIOA->CRL=0X22222222;
	GPIOA->CRH=0X2222;
	GPIOB->CRL=0X02222888;


	while(1)
	{
		GPIOB->ODR=0X08;		// PB3=1; PB4=0; PB5=0; PB6=0

		if(GPIOB->IDR&(1<<0))	// 1
		{
			i=1;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<0));
			delay(5000);
		}

		if(GPIOB->IDR&(1<<1))	// 2
		{
			i=2;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<1));
			delay(5000);
		}

		if(GPIOB->IDR&(1<<2))	// 3
		{
			i=3;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<2));
			delay(5000);
		}


		delay(10);

		GPIOB->ODR=0X10;		// PB3=0; PB4=1; PB5=0; PB6=0

		if(GPIOB->IDR&(1<<0))	// 4
		{
			i=4;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<0));
			delay(5000);
		}

		if(GPIOB->IDR&(1<<1))	// 5
		{
			i=5;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<1));
			delay(5000);
		}

		if(GPIOB->IDR&(1<<2))	// 6
		{
			i=6;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<2));
			delay(5000);
		}


		delay(10);


		GPIOB->ODR=0X20;		// PB3=0; PB4=0; PB5=1; PB6=0

		if(GPIOB->IDR&(1<<0))	// 7
		{
			i=7;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<0));
			delay(5000);
		}

		if(GPIOB->IDR&(1<<1))	// 8
		{
			i=8;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<1));
			delay(5000);
		}

		if(GPIOB->IDR&(1<<2))	// 9
		{
			i=9;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<2));
			delay(5000);
		}


		delay(10);


		GPIOB->ODR=0X40;		// PB3=0; PB4=0; PB5=0; PB6=1

		if(GPIOB->IDR&(1<<1))	// 0
		{
			i=0;
			n=(n*10)+i;
			while(GPIOB->IDR&(1<<1));
			delay(5000);
		}

		delay(10);


	

		GPIOA->ODR=0X0E00 | b[n/1000];
		delay(1000);

		GPIOA->ODR=0X0D00 | b[(n/100)%10];
		delay(1000);

		GPIOA->ODR=0X0B00 | b[(n%100)/10];
		delay(1000);

		GPIOA->ODR=0X0700 | b[n%10];
		delay(1000);
	}
}
*/