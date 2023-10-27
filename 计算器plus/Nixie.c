#include <REGX52.H>
#include "Delay.h"
unsigned char NixieTable[]={
	0x3f,   0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	0xbf,   0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,
	0x40,0x76,0x79,0x38,0x00,0x31
};

void Nixie(unsigned char Location,Select)//œ‘ æ
{
	P2_5=0;
	switch(Location)
	{		
		case 8:	P2_2=0;P2_3=0;P2_4=0;break;
		case 7:	P2_2=1;P2_3=0;P2_4=0;break;
		case 6:	P2_2=0;P2_3=1;P2_4=0;break;
		case 5:	P2_2=1;P2_3=1;P2_4=0;break;
		case 4:	P2_2=0;P2_3=0;P2_4=1;break;
		case 3:	P2_2=1;P2_3=0;P2_4=1;break;
		case 2:	P2_2=0;P2_3=1;P2_4=1;break;
		case 1:	P2_2=1;P2_3=1;P2_4=1;break;	
	}
	P0=NixieTable[Select];
	Delay(1);//∂ØÃ¨œ‘ æ
	P0=0x00;//
}