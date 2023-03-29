#pragma once
#include "Processor.h"

class Scheduler
{
protected:
	std::queue<Process> process_queue_;
	bool is_done_;
public:
	Scheduler() : is_done_(false) {}
	virtual ~Scheduler() {}

	bool isDone() {
		return is_done_;
	}

	virtual void init(){}
	virtual void logic(int _total_tick) {}
	void tick(int _total_tick) {
		addProcess(_total_tick);
		logic(_total_tick);
	}
	void addProcess(int _total_tick) {
		auto jobs = JobSimulator::getInstance()->getJobs(_total_tick);
		for (auto job : jobs) {
			process_queue_.push(Process(job));
		}
	}
};

