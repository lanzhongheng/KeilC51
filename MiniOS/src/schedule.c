
#include <reg52.h>
#include "../include/system.h"
#include "../include/macro.h"

void UpdateTskQueue();

void UpdatePriorTskQueue();

int8_t CanSchedule();

void RegisterTask(uint8_t taskNum)
{
	uint8_t pos;
	for (pos = 0; pos < MAX_TSK_NUM; pos++)
	{
		if (0 == gTskQueue[pos])
		{
			gTskQueue[pos] = taskNum;
			gTCBs[taskNum].curTskStat = TSK_READY;
			break;
		}
	}
}

void RegisterPriorTask(uint8_t taskNum)
{
	uint8_t pos;
	for (pos = 0; pos < MAX_TSK_NUM; pos++)
	{
		if (0 == gPriorTskQueue[pos])
		{
			gPriorTskQueue[pos] = taskNum;
			gTCBs[taskNum].curTskStat = TSK_READY;
			break;
		}
	}

	gSCB.priorityFlag = PRIORITY_ON;
}

uint8_t GetReadyTsk()
{
	uint8_t taskNum;

	taskNum = gTskQueue[0];

	if (0 != taskNum)
	{
		UpdateTskQueue();
	}

	return taskNum;	
}

uint8_t GetReadyPriorTsk()
{
	uint8_t taskNum;

	taskNum = gPriorTskQueue[0];

	if (0 != taskNum)
	{
		UpdatePriorTskQueue();
	}

	if (0 == gPriorTskQueue[0])
	{
		gSCB.priorityFlag = PRIORITY_OFF;
	}

	return taskNum;	
}

void DeregisterTask(uint8_t taskNum)
{
	uint8_t pos;
	for (pos = 0; pos < MAX_TSK_NUM; pos++)
	{
		if (taskNum == gTskQueue[pos])
		{
			gTskQueue[pos] = 0;
			UpdateTskQueue();
			break;
		}
	}
}

uint8_t DeregisterPriorTask(uint8_t taskNum)
{
	uint8_t taskFound = 0;
	uint8_t pos;
	for (pos = 0; pos < MAX_TSK_NUM; pos++)
	{
		if (taskNum == gPriorTskQueue[pos])
		{
			taskFound = 1;
			gPriorTskQueue[pos] = 0;
			UpdatePriorTskQueue();
			break;
		}
	}

	if (0 == gPriorTskQueue[0])
	{
		gSCB.priorityFlag = PRIORITY_OFF;
	}

	return taskFound;
}

void UpdateTskQueue()
{
	uint8_t newPos;
	uint8_t oldPos;
	for (newPos = 0, oldPos = 0; oldPos < MAX_TSK_NUM; oldPos++)
	{
		if (0 != gTskQueue[oldPos])
		{
			gPriorTskQueue[newPos] = gPriorTskQueue[oldPos];
			newPos++; 
		}

		if (MAX_TSK_NUM - 1 == oldPos)
		{
			gPriorTskQueue[oldPos] = 0;
		}
	}
}

void UpdatePriorTskQueue()
{
	uint8_t newPos;
	uint8_t oldPos;
	for (newPos = 0, oldPos = 0; oldPos < MAX_TSK_NUM; oldPos++)
	{
		if (0 != gPriorTskQueue[oldPos])
		{
			gPriorTskQueue[newPos] = gPriorTskQueue[oldPos];
			newPos++; 
		}

		if (MAX_TSK_NUM - 1 == oldPos)
		{
			gPriorTskQueue[oldPos] = 0;
		}
	}
}

void ScheduleTask()
{
	EA = INT_OFF;

	if (!CanSchedule())
	{
		EA = INT_ON;
		return;
	}

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

	if (gSCB.curTskNum != gSCB.nextTskNum)
	{
		/*push current task data into task stack*/
		__asm PUSH ACC
		__asm PUSH B
		__asm PUSH PSW
		__asm PUSH AR0
		__asm PUSH AR1
		//__asm PUSH AR2
		//__asm PUSH AR3
		__asm PUSH AR4
		__asm PUSH AR5
		__asm PUSH AR6
		__asm PUSH AR7

		gTCBs[gSCB.curTskNum].taskSP = SP;
		gSCB.curTskNum = gSCB.nextTskNum;
		gSCB.nextTskNum = 0;
		SP = gTCBs[gSCB.curTskNum].taskSP;

		/*pop new task data from task stack*/
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
	}

	EA = INT_ON;
}

int8_t CanSchedule()
{
	if (SYS_ON != gSCB.sysRunningFlag)
	{
		return 0;
	}
	
	if (SCHMUTEX_ON == gSCB.schMutex)
	{
		return 0;
	}

	if (0 != gSCB.intNestCnt)
	{
		return 0;
	}

	if (SYS_SERVICE == gSCB.sysMode)
	{
		return 0;
	}

	if (0 != gSCB.timeSlice)
	{
		return 0;
	}

	return 1;
}

void LockSchMutex()
{
	EA = INT_OFF;
	gSCB.schMutex = SCHMUTEX_ON;
	EA = INT_ON;
}

void UnlockSchMutex()
{
	EA = INT_OFF;
	gSCB.schMutex = SCHMUTEX_OFF;
	EA = INT_ON;
}

void IncIntNestCnt()
{
	EA = INT_OFF;
	if (gSCB.intNestCnt < MAX_INTNEST_CNT)
	{
		gSCB.intNestCnt++;
	}
	EA = INT_ON;
}

void DecIntNestCnt()
{
	EA = INT_OFF;
	if (gSCB.intNestCnt > 0)
	{
		gSCB.intNestCnt--;
	}
	EA = INT_ON;
}
