#pragma once
#include "ProcessorManager.h"
#include "Scheduler.h"
#include "Processor.h"
#include <queue>
#include <vector>
#include <memory>
#include <iostream>

struct HRRNCompare
{
    bool operator()(std::shared_ptr<Process> one, std::shared_ptr<Process> other) {
        double rr_one = (double)(one->getWaitingTime() + one->getBurstTime()) / one->getBurstTime();
        double rr_other = (double)(other->getWaitingTime() + other->getBurstTime()) / other->getBurstTime();
        return rr_one < rr_other;
    }
};

class HRRNScheduler : public Scheduler
{
private:
    std::priority_queue<std::shared_ptr<Process>, std::vector<std::shared_ptr<Process>>, HRRNCompare> process_pq_;

public:
    HRRNScheduler() : Scheduler() {}
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

        while (!enter_process->empty()) {
            std::shared_ptr<Process> process = enter_process->front();
            process_pq_.push(process);
            enter_process->pop();
        }

        while (psr_mgr->countAvailable() > 0 && !process_pq_.empty())
        {
            std::shared_ptr<Process> process = process_pq_.top();
            process->setWaitingTime(total_tick);
            psr_mgr->addProcess(process);
            process_pq_.pop();
        }

        psr_mgr->tick();
    }
};