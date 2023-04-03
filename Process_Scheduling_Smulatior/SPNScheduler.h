#pragma once
#include "ProcessorManager.h"
#include "Scheduler.h"
#include "Processor.h"
#include <queue>
#include <vector>
#include <memory>
#include <iostream>

struct SPNCompare
{
	bool operator()(std::shared_ptr<Process> one, std::shared_ptr<Process> other) {
		if (one->getCurBurstTime() == other->getCurBurstTime()) return one->getNo() > other->getNo();
		else return one->getCurBurstTime() > other->getCurBurstTime();
	}
};

class SPNScheduler : public Scheduler
{
private:
	std::priority_queue<std::shared_ptr<Process>, std::vector<std::shared_ptr<Process>>, SPNCompare> process_pq_;

public:
	SPNScheduler() : Scheduler() {}
public:
	void init() override {
		while (!process_pq_.empty())
		{
			process_pq_.pop();
		}
	}

	void logic(int total_tick) {
		auto psr_mgr = ProcessorManager::getInstance();
		std::unique_ptr<std::queue<std::shared_ptr<Process>>> enter_process = getEnterProcess(total_tick);

		while (!enter_process->empty())
		{
			std::shared_ptr<Process> process = enter_process->front();
			process_pq_.push(process);
			enter_process->pop();
		}

		while (!process_pq_.empty())
		{
			auto max_pair = psr_mgr->maxCurBurstTime();
			std::shared_ptr<Process> process = process_pq_.top();
			if (max_pair.second <= process->getCurBurstTime()) {
				break;
			}
			else {
				Processor& processor = psr_mgr->getProcessor(max_pair.first);
				if (max_pair.second != 987654321) {
					process_pq_.push(processor.getCurProcess());
				}
				processor.addProcess(process);
				process_pq_.pop();
			}

		}

		psr_mgr->tick();
	}
};

