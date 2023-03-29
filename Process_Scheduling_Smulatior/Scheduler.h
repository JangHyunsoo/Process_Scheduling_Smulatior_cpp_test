#pragma once
#include "Processor.h"
#include <queue>
#include <list>

class Scheduler
{
protected:
	std::queue<Process*> process_queue_;
	bool is_done_;
public:
	Scheduler() : is_done_(false) {}
	virtual ~Scheduler() {}

	bool isDone() {
		bool psr_mgr_done = ProcessorManager::getInstance()->isDone();
		bool shd_mgr_done = JobSimulator::getInstance()->isDone();
		return psr_mgr_done && shd_mgr_done;
	}

	virtual void init(){}
	virtual void logic(int _total_tick) {}
	void tick(int _total_tick) {
		addProcess(_total_tick);
		logic(_total_tick);
	}
	void addProcess(int _total_tick) {
		std::list<Job>& jobs = JobSimulator::getInstance()->getJobs(_total_tick);
		
		for (Job& job : jobs) {
			process_queue_.push(new Process(job));
		}
	}
};

