#ifndef  __PAD_H__
#define	 __PAD_H__
#include "sys.h" 

#define  PADPULLDOWN	1
#define  PADPULLUP		0

void PadInit( u8 psc );

u8	 PadScan( u8 mode );


#endif
