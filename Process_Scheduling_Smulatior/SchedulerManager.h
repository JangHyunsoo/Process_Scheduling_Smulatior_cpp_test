#pragma once
#include "JobSimulator.h"
#include "ProcessorManager.h"
#include "Scheduler.h"
#include "FCFSScheduler.h"
#include "STRNScheduler.h"
#include <iostream>

enum class ScheduleWay {
	FCFS,
	RR,
	SPN,
	SRTN,
	HRRN
};

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
	void init(ScheduleWay _way) {
		total_tick_ = 0;
		assignScheduler(_way);
		JobSimulator::getInstance()->init();
		ProcessorManager::getInstance()->init();
		cur_scheduler_->init();
	}
	void run() {
		while (!cur_scheduler_->isDone())
		{
			cur_scheduler_->tick(total_tick_++);
			// ProcessorManager::getInstance()->printStat(total_tick_);
		}
		ProcessorManager::getInstance()->printHistory(total_tick_);
	}
private:
	void assignScheduler(ScheduleWay _way) {
		switch (_way)
		{
		case ScheduleWay::FCFS:
			cur_scheduler_ = new FCFSScheduler();
			break;
		case ScheduleWay::RR:
			cur_scheduler_ = new Scheduler();
			break;
		case ScheduleWay::SPN:
			cur_scheduler_ = new Scheduler();
			break;
		case ScheduleWay::SRTN:
			cur_scheduler_ = new STRNScheduler();
			break;
		case ScheduleWay::HRRN:
			cur_scheduler_ = new Scheduler();
			break;
		default:
			break;
		}
	}
};

SchedulerManager* SchedulerManager::instance_ = nullptr;