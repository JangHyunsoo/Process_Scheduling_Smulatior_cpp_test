﻿#include <iostream>
#include <sstream>
#include "SchedulerManager.h"
#include "JobSimulator.h"
#include "ProcessorManager.h"

using namespace std;


int main()
{
	SchedulerManager::getInstance()->init(ScheduleWay::SPN);
	SchedulerManager::getInstance()->run();
}