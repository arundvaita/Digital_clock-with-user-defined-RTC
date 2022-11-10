#include<reg51.h>

#ifndef __TYPE.H__
#define __TYPE.H__

typedef   unsigned char uc_8;
typedef  char sc_8;
typedef  unsigned int ui_16;
typedef   int si_16;
#endif

void delayms(ui_16);


#ifndef __LCDLIB.H__
#define __LCDLIB.H__

idata enum command{right=6,left=7,lcd8=0x38,lcd4=0x28,clear=1,home=2,coff=0x0c,con=0x0e,cblink=0x0f};

void lcdset(uc_8); // will do all command modes, including initialising
void lcdprintc(uc_8);  
void lcdprints(sc_8*);
void lcdcursor(uc_8,uc_8);
void lcdprinti(si_16);
void lcdprintf(float);

extern idata ui_16 fp;

// additional library : lcdlib2.h
void lcdscroll(sc_8* ,uc_8,uc_8);  // should set upos, dpos, uopt, dopt in program  
void lcdrotate(sc_8* ,uc_8,uc_8); 

#endif
