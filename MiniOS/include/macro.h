
#ifndef MACRO_H
#define MACRO_H

/*system mode*/
#define	SYS_STOP		0x00
#define	SYS_RUNNING		0x01
#define	SYS_EXCL		0x02
#define	SYS_SERVICE		0x04

/*task status*/
#define	TSK_READY		0x01
#define	TSK_DELAY		0x02
#define	TSK_WAIT_INT	0x20
#define	TSK_HANGUP		0x40

/*flags*/
#define	SYS_ON			0xff
#define	SYS_OFF			0x00
#define	PRIORITY_ON		0xff
#define	PRIORITY_OFF	0x00
#define	INT_ON			0x01
#define	INT_OFF			0x00
#define	TIMEOUT_ON		0xff
#define	TIMEOUT_OFF		0x00
#define SCHMUTEX_ON		1
#define SCHMUTEX_OFF	0	


#endif
