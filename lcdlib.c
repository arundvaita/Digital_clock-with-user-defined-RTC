#include "lcdlib.h"
// 8bit library
sbit RS=P3^4;
sbit RW=P3^5;
sbit EN=P3^6;

 idata ui_16 fp=3;   // float point, 


//data port  is P0

void  lcdset(uc_8 cmd)  // will do all command modes, including initialising
{
    if(cmd==lcd8)
    {
        EN=0;
        P0=0x38;
        RS=0;
        RW=0;
        EN=1;
        delayms(2);
        EN=0;
        lcdset(clear);
        lcdset(con);
    }
		
    else 
    {
				P0=cmd;
        RS=0;
        RW=0;
        EN=1;
        delayms(2);
        EN=0;
    }
}
void lcdprintc(uc_8 ch)
{
		P0=ch;
    RS=1;
    RW=0;
    EN=1;
    delayms(2);
    EN=0;
}
void lcdprints(sc_8* str)
{ 
    uc_8 i=0;
	if(str==0)
		return;
    while(str[i])
    lcdprintc(str[i++]);
      
} 
void lcdcursor(uc_8 r,uc_8 c)
{
    if(r==0)
        lcdset(0x80+c);
    else if(r==1)
        lcdset(0xC0+c);
}

void lcdprinti(si_16 num)
{
 idata   sc_8 i;
    idata uc_8 arr[6]={0};
	 if(num==0)
	{lcdprintc('0');
		return;
	}
		if(num<0)
	{lcdprintc('-');
		num=-num;
	}
    for(i=0;num;num/=10)
    {
        arr[i]=48+(num%10);
    
i++;
}
    i--;
	
		while(i>=0)
    {
        lcdprintc(arr[i]);
			i--;
    }
    
}

//
//void lcdprintf(float f)
//{
//  idata ui_16 n1;
//	idata ui_16 n2=10;
//	idata uc_8 i=0;
//	 if(f==0)
//	{lcdprintc('0');
//		return;
//	}
//	if(f<0)
//	{lcdprintc('-');
//		f=-f;
//	}
//	n1=f;
//	f=f-n1;
//   lcdprinti(n1);
//   lcdprintc('.');
//    
//   while(i++<fp)
//	 {
//		 n1=f*10;
//    	  if(n1==0)
//	        lcdprintc('0');
//	    else
//				lcdprinti(n1);
//			f=(f*10)-n1;
//    }
//}



  



