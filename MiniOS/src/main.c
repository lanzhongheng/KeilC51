
#include <reg52.h>
#include "../include/init.h"
#include "../include/system.h"

void SystemOn();

void main()
{
	InitSystem();

	SystemOn();	
}

/***********************/

void SystemOn()
{
	/*get task number from task queue*/
	gSCB.nextTskNum = gTskQueue[1];
	gSCB.curTskNum = gSCB.nextTskNum;
	
	/*get task entry from TCB*/
	SP = gTCBs[gSCB.curTskNum].taskSP;
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
