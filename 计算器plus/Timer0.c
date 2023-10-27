#include <REGX52.H>

/**
  * @brief  ��ʱ������ʼ����1���� @11.0592MHz
  * @param  ��
  * @retval ��
  */



void Timer0Init()
{
//	TMOD=0X01; //0000 0001
	TMOD&=0xF0;  //��TMOD�ĵ���Ϊ���㣬����Ϊ���ֲ���
	TMOD|=0x01;  //��TMOD�����λ��1������Ϊ���ֲ���
	TF0=0;
	TR0=1;
	TH0=0xFC;	//���ö�ʱ��ֵ
	TL0=0x66; //���ö�ʱ��ֵ
	ET0=1;		//�Զ�����ע����3��ֵ
	EA=1;			//
	PT0=0;		//
}


/*��ʱ��ģ��
void Timer_Routine()	interrupt 1
{
	static unsigned int T0Count;
	TH0=0xFC;  //�������ö�ʱ��ʼֵ
	TL0=0x66;		
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		P2_0=~P2_0;
	}
}


*/