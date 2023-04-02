#pragma once
#include "Processor.h"
#include <queue>
#include <list>
#include <memory>

class Scheduler
{
protected:
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
		logic(_total_tick);
	}
protected:
	std::unique_ptr<std::queue<std::shared_ptr<Process>>> getEnterProcess(int _total_tick) {
		std::unique_ptr<std::queue<std::shared_ptr<Process>>> result = std::make_unique<std::queue<std::shared_ptr<Process>>>();

		std::unique_ptr<std::list<Job>> jobs = JobSimulator::getInstance()->getJobs(_total_tick);
		
		for (Job& job : *jobs) {
			result->push(std::make_shared<Process>(job));
		}

		return std::move(result);
	}
};

