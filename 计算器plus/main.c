#include <REGX52.H>
#include "Nixie.h"
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"
#include "MatrixKey.h"

#define vain 24

#define minus  20
#define letter_H 21
#define letter_E 22
#define letter_L 23
#define letter_r 25


unsigned char MatrixKeyNum,KeyNum,ShowNum,Err,i,Zero,NixieShowSelect,End,FloatSymbol,MinusNumSymbol,FloatSelect,Omod;
unsigned long in,m;
double ONum,Result;
unsigned char FloatNum[]={10,11,12,13,14,15,16,17,18,19};

unsigned char MatrixKeyNumMeaning[]={      vain,
																		 7,8,9,vain,
                                     4,5,6,vain,
	                                   1,2,3,vain,
																		 0,    vain,vain,vain};//MatrixKeyNumMeaning[MatrixKeyNum]如此，可以解释矩阵按键代表的意思
unsigned char NixieShow[]={vain,vain,vain,vain,vain,vain,vain,vain,vain,vain,vain,vain,vain,vain,vain,vain,vain};

void NixieShowCls()
{
	for(i=0;i<9;i++)
	{
		  NixieShow[i]=vain;
			NixieShowSelect=0;
	}
}


void NixieNuminput(unsigned char Data)
{
	if(NixieShowSelect<8 && FloatSymbol!=1)
	{
		NixieShowSelect++;
		NixieShow[NixieShowSelect+8]=Data;
	}
	if(NixieShowSelect<8 && FloatSymbol==1)
	{
//	  NixieShowSelect++;
		NixieShow[NixieShowSelect+8]=Data;
		FloatSymbol=2;
	}
	
	
}

void main()
{
	
	Timer0Init();
	NixieNuminput(letter_H);
	NixieNuminput(letter_E);
	NixieNuminput(letter_L);
	NixieNuminput(letter_L);
	NixieNuminput(0);
	Delay(300);
				NixieShowCls();
				ONum=0;
				End=0;
				Err=0;
	NixieNuminput(minus);
		Delay(50);
	NixieNuminput(minus);
		Delay(50);
	NixieNuminput(minus);
		Delay(50);
	NixieNuminput(minus);
		Delay(50);
	NixieNuminput(minus);
		Delay(50);
	NixieNuminput(minus);
		Delay(50);
	NixieNuminput(minus);
		Delay(50);
	NixieNuminput(minus);
		Delay(50);
							NixieShowCls();
				ONum=0;
				End=0;
				Err=0;




	
	while(1)
	{
		
		KeyNum=Key();
		if(KeyNum==1)
		{
			NixieShowCls();
			ONum=0;
			FloatSymbol=0;
			MinusNumSymbol=0;
			Err=0;
			Zero=0;


		}
		
		MatrixKeyNum=MatrixKey();//获取矩阵按键的输入
		if(MatrixKeyNum)
		{
			if(End==1)
			{
				NixieShowCls();
				ONum=0;
				End=0;
				Err=0;
				Zero=0;
			}
			for(i=1;i<10;i++)
			{
				if(MatrixKeyNumMeaning[MatrixKeyNum]==i&&Zero!=1)
				{
					NixieNuminput(i);
					ONum*=10;
					ONum+=MatrixKeyNumMeaning[MatrixKeyNum];
					if(MinusNumSymbol==1){MinusNumSymbol=2;}
					Zero=0;
				}
				
			}
						if(MatrixKeyNumMeaning[MatrixKeyNum]==0&&Zero!=1)
				{
					NixieNuminput(0);
					ONum*=10;
					ONum+=MatrixKeyNumMeaning[MatrixKeyNum];
					if(MinusNumSymbol==1){MinusNumSymbol=2;}
					if(NixieShowSelect==1){Zero=1;}
					if(MinusNumSymbol==2&&NixieShowSelect==2){Zero=1;}
				}

			
			if(MatrixKeyNum==14&&FloatSymbol!=2&&NixieShowSelect!=0)
			{					
				FloatSymbol=1;
				NixieNuminput(FloatNum[NixieShow[NixieShowSelect+8]]);
				FloatSelect=NixieShowSelect;
								Zero=0;

			}
			if(MatrixKeyNum==12&&MinusNumSymbol!=2&&NixieShowSelect==0)
			{
								if(End==1)
				{				
				NixieShowCls();
				ONum=0;
				End=0;
				Err=0;
				Zero=0;
					}

				MinusNumSymbol=1;
				NixieNuminput(minus);

			}
			
			
			
			if(MatrixKeyNum==4||MatrixKeyNum==8||MatrixKeyNum==12||MatrixKeyNum==16&&NixieShowSelect!=0)

			{
				if(FloatSymbol!=1&&MinusNumSymbol!=1&&Omod!=4&&Omod!=8&&Omod!=12&&Omod!=16)
				{
					

							if(FloatSymbol==2)
							{
							
								for(i=0;i<NixieShowSelect-FloatSelect;i++)
								{
									ONum*=0.1;
									FloatSymbol=0;
								}
							}
						if(MinusNumSymbol==2)
						{
							ONum*=-1;
								MinusNumSymbol=0;
						}
									Result=ONum;
									End=1;
								for(i=0;i<9;i++)
							{
								NixieShow[i]=vain;
							}

					
				}
			}
			
			switch(MatrixKeyNum)
			{
				case 4:if(FloatSymbol!=1&&MinusNumSymbol!=1&&NixieShowSelect!=0&&Omod==0){Omod=4;}break;
				case 8:if(FloatSymbol!=1&&MinusNumSymbol!=1&&NixieShowSelect!=0&&Omod==0){Omod=8;}break;
				case 12:if(FloatSymbol!=1&&MinusNumSymbol!=1&&NixieShowSelect!=0&&Omod==0){Omod=12;}break;
				case 16:if(FloatSymbol!=1&&MinusNumSymbol!=1&&NixieShowSelect!=0&&Omod==0){Omod=16;}break;

			}
			if(MatrixKeyNum==15&&Omod!=0&&FloatSymbol!=1&&MinusNumSymbol!=1&&NixieShowSelect!=0)
			{
				
				
			if(FloatSymbol==2)
				{
				
					for(i=0;i<NixieShowSelect-FloatSelect;i++)//
					{
						ONum*=0.1;
					}
				}
			if(MinusNumSymbol==2)
			{
				ONum*=-1;
			}

				
				switch(Omod)
				{
					case 4:if(ONum!=0){Result=Result/ONum;Omod=0;}else{Err=1;}break;
					case 8:Result=Result*ONum;Omod=0;break;
					case 12:Result=Result-ONum;Omod=0;break;
					case 16:Result=Result+ONum;Omod=0;break;
				}
				if(Err==0)
        {
					NixieShowCls();
				if(Result<0)
				{
					NixieNuminput(minus);
					Result*=-1;
				}

				in=Result;
				
			//	NixieNuminput(in);
				m=in/10000000%10;
				if(in>=10000000){NixieNuminput(m);}
				m=in/1000000%10;
				if(in>=1000000){NixieNuminput(m);}
				m=in/100000%10;
				if(in>=100000){NixieNuminput(m);}
				m=in/10000%10;
				if(in>=10000){NixieNuminput(m);}
				m=in/1000%10;
				if(in>=1000){NixieNuminput(m);}
				m=in/100%10;
				if(in>=100){NixieNuminput(m);}
				m=in/10%10;
				if(in>=10){NixieNuminput(m);}
				m=in/1%10;
				if(in>=1){NixieNuminput(m);}
				if(in<=1&&m==0){NixieNuminput(m);}
				in=Result*100;
				m=in%100;
				if(m>=1){NixieShowSelect--;in=Result;m=in/1%10;NixieNuminput(FloatNum[m]);in=Result*10;m=in%10;NixieNuminput(m);}
				in=Result*100;
				m=in%10;
				if(m>=1){NixieNuminput(m);}
				

				

				
				
				End=1;
				FloatSymbol=0;
				MinusNumSymbol=0;
			}
				else if(Err==1)
				{
					NixieShowCls();
				 NixieNuminput(letter_E);
	       NixieNuminput(letter_r);
	       NixieNuminput(letter_r);

				}

				
				
			}
			
			
			
						
						
		}
	}
}

void Timer_Routine()	interrupt 1
{
	static unsigned int T0Count;
	TH0=0xFC;  //重新设置定时初始值
	TL0=0x66;		
	T0Count++;
	if(T0Count>=5)
	{
		T0Count=0;
		Nixie(1,NixieShow[1+NixieShowSelect]);
		Nixie(2,NixieShow[2+NixieShowSelect]);
		Nixie(3,NixieShow[3+NixieShowSelect]);
		Nixie(4,NixieShow[4+NixieShowSelect]);
		Nixie(5,NixieShow[5+NixieShowSelect]);
		Nixie(6,NixieShow[6+NixieShowSelect]);
		Nixie(7,NixieShow[7+NixieShowSelect]);
		Nixie(8,NixieShow[8+NixieShowSelect]);
	}
}


