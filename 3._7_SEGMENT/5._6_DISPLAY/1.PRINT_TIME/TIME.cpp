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
	
	GPIOA->ODR=(GPIOA->ODR & 0XFF00) | ((value&0XF0)>>4);//GPIOA->ODR= ((value& 0XF0)>>4);
	enable();
	GPIOA->ODR=(GPIOA->ODR & 0XFF00) | (value&0X0F);//GPIOA->ODR= (value& 0X0F);
	enable();
}
void string(char *p)
{
	while(*p)
		lcd(1,*p++);
}
int i,j,k,n,m,run;
int b[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
int main()
{
	RCC->CR=0X83;
	RCC->CFGR=0X00;
	RCC->APB2ENR |= 1<<2 | 1<<3 | 1<<4;
	GPIOA->CRL=0X2222;
	GPIOA->CRH=0X888;
	GPIOB->CRL=0X22222222;
	GPIOB->CRH=0X22222222;
	GPIOC->CRH=0X22220000;
	lcd(0,0X02);
	lcd(0,0X28);
	lcd(0,0X0E);
	lcd(0,0XC0);
int h, min, sec;
int ph=0,pmin=0,psec=0; 
while(1)
{
							if(GPIOA->IDR & (1<<8))
							{
								run=1;
								h=ph;
								min=pmin;
								sec=psec;
								lcd(0,0X01);
								string("RUNNING");
								delay(10000);
							}

if(run)	
{
    for(h=ph; h<24 &&  run; h++)
    {
      for(min=pmin; min<60 && run; min++)
      {
         for(sec=psec; sec<60 && run; sec++)
         {
            for(m=0; m<10 && run; m++)
            {
							if(GPIOA->IDR & (1<<9))
							{
								run=0;
								//lcd(0,0X01);
								ph=h;
								pmin=min;
								psec=sec;
								lcd(0,0X80);
								string("PAUSE..");
								delay(10000);
								continue;
							}
							if(GPIOA->IDR & (1<<10))
							{
								run= h= min = sec =0;
						    ph=0,pmin=0,psec=0; 
								lcd(0,0X01);
								string("RESET");
								delay(10000);
								run=1;
								break;
							}
							GPIOB->ODR=0X3E00 ;
							GPIOB->ODR|= b[h/10];//PB15 TO PB8 - 0011 1110 ->0X3E 
              delay(100);

              GPIOB->ODR=0X3D00 | b[h%10];//0011 1101 ->0X3D
              delay(100);

              GPIOB->ODR=0X3B00 | b[min/10];//0011 1011 -> 0X3B 
              delay(100);

              GPIOB->ODR=0X3700 | b[min%10];//0011 0111 -> 0X37
              delay(100);
							
              GPIOB->ODR=0X2F00 | b[sec/10];//0010 1111 -> 0X2F
              delay(100);

              GPIOB->ODR=0X1F00 | b[sec%10];//0001 1111 -> 0X1F
              delay(100);
							
							lcd(0,0XC8);
							lcd(1,'0'+(h/10));
							lcd(1,'0'+h%10);
							lcd(1,':');
							lcd(1,'0'+(min/10));
							lcd(1,'0'+ min%10);
							lcd(1,':');
							lcd(1,'0'+(sec/10));
							lcd(1,'0'+sec%10);

           }
        }
     }
  }
}			
}
}