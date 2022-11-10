#include"lcdlib.h"

sbit splus=P2^0;
sbit smin=P2^1;
sbit sel=P2^2;
sbit bulb=P1^7;

/*
expected output
12:12:12 PM
MON 12/12/2020

*/
//default settings
	//idata uc_8 TM[3]={23,59,50},DT[3]={31,12,6},menu=0,var;  //(hr,mn,ss)(date,month,week) tmod 0 for 12hr,1 for 24hr  ,menu(0 home,1 alarm,2 stopwatch,3 timer),var for commion use
	//idata ui_16 YY=2021;

//leap test
//	idata uc_8 hr=23,mn=59,ss=50,DD=29,MM=2,WW=6,leap=0,tmod=0;  // tmod 0 for 12hr,1 for 24hr  
//	idata ui_16 YY=2024;


		idata uc_8 TM[3]={16,0,50},DT[3]={9,8,3},menu=0,var;  //(hr,mn,ss)(date,month,week) tmod 0 for 12hr,1 for 24hr  ,menu(0 home,1 alarm,2 stopwatch,3 timer),var for commion use
	idata ui_16 YY=2022;
	
	bit leap=0,tmod=0,stopwatch=0,timer=0;
	
	
	idata uc_8 AL[2]={16,15};     // (hr,mn) lcd deispalay (2nd row) and bulb on off, until button pressed or SW mn=5,
	idata uc_8 SW[3]={0,0,0};  // (hr,mn,ss)  stopwatch forward
	idata uc_8 TR[3]={6,6,6};    // (hr,mn,ss) timer revrese counnt
	



/*
automatically calculate set day,month... and leap year. print happy new year on new year day
*/

	idata uc_8 month[12][4]={"JAN","FEB","MAR","APR","MAY","JUN","JLY","AUG","SEP","OCT","NOV","DEC"}; 
	idata uc_8 week[7][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"}; 

void show();
	
	
void calander()
{
	if((DT[2]+1)==8)
		DT[2]=1;
	else
		DT[2]++;
	
	
	if(((YY%4)==0)&&(((YY%100)!=0)||((YY%400)==0) ))
		leap=1;
	else
		leap=0;
	
	if((DT[0]==28) && (DT[1]==2) && (leap!=1))
		DT[0]=1;
	else if((DT[0]==29) && (DT[1]==2) && (1==leap))
		DT[0]=1;
	else if((DT[0]==30) && ((DT[1]==4)||(DT[1]==6)||(DT[1]==9)||(DT[1]==11) ))
		DT[0]=1;
	else if((DT[0]==31) && ((DT[1]==1)||(DT[1]==3)||(DT[1]==5)||(DT[1]==7) ||(DT[1]==8)||(DT[1]==10)||(DT[1]==12)))
		DT[0]=1;	
	else 
		DT[0]++;

if(((DT[1]+1)==13)&&(DT[0]==1))
		DT[1]=1;
	else if(DT[0]==1)
		DT[1]++;
	if(((YY+1)==33000)&&(DT[1]==1)&&(DT[0]==1))   // yy limit check
		YY=2000;
	else if((DT[1]==1)&&(DT[0]==1) )
		YY++;
}


void clock()
{
	if(stopwatch==1)
	{
		if((SW[2]+1)==60)
		SW[2]=0;
	else 
		SW[2]++;
if(((SW[1]+1)==60)&&(SW[2]==0))
		SW[1]=0;
	else if(SW[2]==0)
		SW[1]++;
	if(((SW[0]+1)==24)&&(SW[1]==0)&&(SW[2]==0))
		SW[0]=0;
		else if((SW[1]==0)&&(SW[2]==0))
		SW[0]++;
	}
	
		if(timer==1)
	{
		if(TR[2]==0)
		TR[2]=59;
	else 
		TR[2]--;
if((TR[1]==0)&&(TR[2]==59))
		TR[1]=59;
	else if(TR[2]==59)
		TR[1]--;
	if((TR[0]==0)&&(TR[1]==59)&&(TR[2]==59))
		TR[0]=23;
		else if((TR[2]==59)&&(TR[1]==59))
		TR[0]--;
	}
	
	if((TM[2]+1)==60)
		TM[2]=0;
	else 
		TM[2]++;
if(((TM[1]+1)==60)&&(TM[2]==0))
		TM[1]=0;
	else if(TM[2]==0)
		TM[1]++;
	if(((TM[0]+1)==24)&&(TM[1]==0)&&(TM[2]==0))
	{
		TM[0]=0;
    calander();
	}
		else if((TM[1]==0)&&(TM[2]==0))
		TM[0]++;
	
	delayms(1000);
}

void lcdclock()
{
    lcdset(clear);
		lcdcursor(1,0);
		lcdprints(week[DT[2]-1]);
		lcdprintc(' ');
	if(DT[0]<10)
			lcdprinti(0);
		lcdprinti(DT[0]);
		lcdprintc(':');
		lcdprints(month[DT[1]-1]);
		lcdprintc(':');
		lcdprinti(YY);

		lcdcursor(0,0);
			if(tmod)
			{
				if(TM[0]<10)
			lcdprinti(0);
		  lcdprinti(TM[0]);
			}
				else
				{
					
					if((TM[0]==0)||(TM[0]==12))
						lcdprinti(12);
					else
				  {
						if(TM[0]<10)
						lcdprinti(0);
						lcdprinti(TM[0]%12);
					}
				}
					lcdprintc(':');
			lcdcursor(0,3);
			if(TM[1]<10)
			lcdprinti(0);
		  lcdprinti(TM[1]);
		  lcdprintc(':');
			lcdcursor(0,6);
			if(TM[2]<10)
			lcdprinti(0);
		  lcdprinti(TM[2]);
		  lcdprintc(' ');
			if((TM[0]>11)&&(tmod==0) )
			lcdprints("PM");
			else if(tmod==0)
				lcdprints("AM");	
}

void check()
{
	   if((splus==0)&&(smin==0))
		 {
			tmod=~tmod;
		 }
	
	else if(splus==0)
		{
			menu++;
			if(menu==4)
				menu=0;
			return;
		}
		else if(smin==0)
		{
			if(menu==0)
				menu=3;
			else
				menu--;
			return;
		}
		else if(sel==0)
		{
				
					
			if(menu==0)  // not done
			{
				for(var=0;var<3;var++) //  DT here 
				{
					while(1)
					{
						  show();
						lcdcursor(1,0);
							lcdprints("RESETING........");
						if(var==2)   // for seconds
							delayms(50);
						else
						clock();
						
						if(splus==0)
						{
							TM[var]++;
							if((TM[var]==24)&&(var==0))
								TM[var]=0;
							else if((TM[var]==60)&&(var!=0))
								TM[var]=0;
						}
						if(smin==0)
						{
							if((TM[var]==0)&&(var==0))
								TM[var]=23;
							else if((TM[var]=0)&&(var!=1))
								TM[var]=59;
							else
								TM[var]--;
						}
							if(sel==0)
								{
							bulb=0;
									clock();
									bulb=1;
						break;
						}
					 
						}
					}
				
				for(var=0;var<3;var++) //  must set date properly  incl yy mm dd day, not synchronized, ask any sugession
				{
					while(1)
					{
						  show();
						lcdcursor(0,0);
							lcdprints("RESETING........");
						clock();
						if(splus==0)
						DT[var]++;
				
						if(smin==0)
								DT[var]--;
						if((var==2)&&(DT[var]>7 && DT[var]<1))
							DT[var]=4;
							if(sel==0)
							{
							bulb=0;
									clock();
									bulb=1;
						break;
						}
					 
						}
					}
				while(1)
					{
						  show();
						lcdcursor(0,0);
							lcdprints("RESETING........");
						clock();
						if(splus==0)
						YY++;
				
						if(smin==0)
								YY--;
						if(sel==0)
						{
							bulb=0;
									clock();
									bulb=1;
						break;
						}
						}
					lcdset(clear);
				lcdprints("TIME RESETTED");		
        clock();						
			}
			else if(menu==1)
			{
				for(var=0;var<2;var++)
				{
					while(1)
					{
						  show();
						  lcdcursor(1,0);
						   lcdprints("RESETING........");
						clock();
						if(splus==0)
						{
							AL[var]++;
							if((AL[var]==24)&&(var==0))
								AL[var]=0;
							else if((AL[var]==60)&&(var==1))
								AL[var]=0;
						}
						if(smin==0)
						{
							if((AL[var]==0)&&(var==0))
								AL[var]=23;
							else if((AL[var]=0)&&(var==1))
								AL[var]=59;
							else
								AL[var]--;
						}
							if(sel==0)
							{
							bulb=0;
									clock();
									bulb=1;
						break;
						}
					 
						}
					}
					lcdset(clear);
				lcdprints("ALARM RESETTED");
			}				
				else if(menu==2)   // stop watch
				{
						stopwatch=~stopwatch;
						show();
						clock();
						if(sel==0)
						{	
						bulb=0;
									clock();
									bulb=1;
						 SW[0]=0;
							SW[1]=0;
							SW[2]=0;
						}
						
					}
		
				
			
			else if(menu==3)   // timer
			{
				timer=~timer;
						show();
						clock();
						if(sel==0)
						{
							
							bulb=0;
									clock();
									bulb=1;
							TR[0]=0;
							TR[1]=0;
							TR[2]=0;
						}
			}
			}
			
			
			return;
		}
		

void message()
{
	if((DT[1]==1)&&(DT[0]==1))
	{
			lcdset(clear);
		lcdcursor(1,0);
		lcdprints("HAPPY NEW YEAR ");
	}
	else if((DT[1]==12)&&(DT[0]==25))
	{
		lcdset(clear);
		lcdcursor(1,0);
		lcdprints("HAPPY CHRISTMAS ");
	}

	else
		lcdclock();
}
void show()
{
	switch(menu)
		{
			case 0:if((AL[0]==TM[0])&&(AL[1]==TM[1]))  // alarm can set snooze, alarm off time....
							{
									bulb=0;
								lcdset(clear);
							
								lcdcursor(1,0);
								lcdprints("WAKE UP ARUN..!!");
							}
							else if(TM[2]%5)
							lcdclock();
							else
							{
								bulb=1;
							message();
							}
							break;
			case 1: 	lcdset(clear);
								if(AL[0]<10)
								lcdprinti(0);
								lcdprinti(AL[0]);
								lcdprintc(':');
								if(AL[1]<10)
								lcdprinti(0);
							lcdprinti(AL[1]);
							lcdcursor(1,0);
							lcdprints("ALARM");			
                    break;
			case 2: 	lcdset(clear);
								if(SW[0]<10)
								lcdprinti(0);
								lcdprinti(SW[0]);
								lcdprintc(':');
								if(SW[1]<10)
								lcdprinti(0);
							lcdprinti(SW[1]);	
								lcdprintc(':');
								if(SW[2]<10)
								lcdprinti(0);
							lcdprinti(SW[2]);
							lcdcursor(1,0);
							lcdprints("STOPWATCH");												
										break;
			case 3: 	lcdset(clear);
								if(TR[0]<10)
								lcdprinti(0);
								lcdprinti(TR[0]);
								lcdprintc(':');
								if(TR[1]<10)
								lcdprinti(0);
							lcdprinti(TR[1]);	
							lcdprintc(':');
								if(TR[2]<10)
								lcdprinti(0);
							lcdprinti(TR[2]);										
							lcdcursor(1,0);
							lcdprints("TIMER");	
										break;								
							}
		}
	

void main()
{
lcdset(lcd8);
lcdset(coff);
	bulb=1;
	lcdset(clear);
	while(1)
	{
		clock();
		check();
		show();
	
}
}