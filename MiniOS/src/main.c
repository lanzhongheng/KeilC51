
#include <reg52.h>
#include "../include/init.h"
#include "../include/system.h"
#include "../include/schedule.h"
#include "../include/macro.h"

void SystemOn();

void main()
{
	InitSystem();

	SystemOn();	
}

/***********************/

void SystemOn()
{
	gSCB.sysRunningFlag = SYS_ON;
	gSCB.sysMode = SYS_RUNNING;
	
	SysTimerOn();
	
	EA = INT_OFF;

	if (0 == gSCB.nextTskNum)
	{
		if (PRIORITY_ON == gSCB.priorityFlag)
		{
			gSCB.nextTskNum = GetReadyPriorTsk();
		}
		else
		{
			gSCB.nextTskNum = GetReadyTsk();
		}
	}

	gSCB.timeSlice = SYS_TIMESLICE;
	gSCB.curTskNum = gSCB.nextTskNum;
	gSCB.nextTskNum = 0;
	SP = gTCBs[gSCB.curTskNum].taskSP;

	/*pop task stack data*/
	__asm POP AR7
	__asm POP AR6
	__asm POP AR5
	__asm POP AR4
	//__asm POP AR3
	//__asm POP AR2
	__asm POP AR1
	__asm POP AR0
	__asm POP PSW
	__asm POP B
	__asm POP ACC
	
	EA = INT_ON;
	
}

/***********************/

void Task0()
{
	while (1)
	{
		//TODO
	}
}

void Task1()
{
	while (1)
	{
		//TODO
	}
}

void Task2()
{
	while (1)
	{
		//TODO
	}
}

void Task3()
{
	while (1)
	{
		//TODO
	}
}

void Task4()
{
	while (1)
	{
		//TODO
	}
}
