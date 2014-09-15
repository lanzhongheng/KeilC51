
#ifndef SCHEDULE_H
#define SCHEDULE_H

void RegisterTask(uint8_t taskNum);

void RegisterPriorTask(uint8_t taskNum);

uint8_t GetReadyTsk();

uint8_t GetReadyPriorTsk();

void DeregisterTask(uint8_t taskNum);

uint8_t DeregisterPriorTask(uint8_t taskNum);

void ScheduleTask();

void LockSchMutex();

void UnlockSchMutex();

void IncIntNestCnt();

void DecIntNestCnt();

#endif	
