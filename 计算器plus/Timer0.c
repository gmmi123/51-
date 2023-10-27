#include <REGX52.H>

/**
  * @brief  定时器）初始化，1毫秒 @11.0592MHz
  * @param  无
  * @retval 无
  */



void Timer0Init()
{
//	TMOD=0X01; //0000 0001
	TMOD&=0xF0;  //把TMOD的低四为清零，高四为保持不变
	TMOD|=0x01;  //把TMOD的最低位置1，高四为保持不变
	TF0=0;
	TR0=1;
	TH0=0xFC;	//设置定时初值
	TL0=0x66; //设置定时初值
	ET0=1;		//自动生成注意这3个值
	EA=1;			//
	PT0=0;		//
}


/*定时器模板
void Timer_Routine()	interrupt 1
{
	static unsigned int T0Count;
	TH0=0xFC;  //重新设置定时初始值
	TL0=0x66;		
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		P2_0=~P2_0;
	}
}


*/