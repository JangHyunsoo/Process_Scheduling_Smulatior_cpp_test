#pragma once
#include "JobSimulator.h"
#include "ProcessorManager.h"
#include "Scheduler.h"
#include "FcfsScheduler.h"
#include <iostream>

class SchedulerManager
{
	// singleton part
private:
	static SchedulerManager* instance_;
	SchedulerManager() {}
	~SchedulerManager() {}
public:
	static SchedulerManager* getInstance() {		if (instance_ == nullptr) {
			instance_ = new SchedulerManager();
		}
		return instance_;
	}
private:
	int total_tick_;
	Scheduler* cur_scheduler_;
public:
	void init() {
		total_tick_ = 0;
		cur_scheduler_ = new FcfsScheduler();
		JobSimulator::getInstance()->init();
		ProcessorManager::getInstance()->init();
		cur_scheduler_->init();
	}
	void run() {
		while (!cur_scheduler_->isDone())
		{
			cur_scheduler_->tick(total_tick_);
			total_tick_++;
		}
		ProcessorManager::getInstance()->printHistory(total_tick_);
	}
};

SchedulerManager* SchedulerManager::instance_ = nullptr;