#pragma once
#include "Scheduler.h"
#include "ProcessorManager.h"
#include <queue>
#include <memory>

class FCFSScheduler : public Scheduler
{
private:
    std::queue<std::shared_ptr<Process>> process_queue_;
public:
    FCFSScheduler() : Scheduler() {}
public:
    void init() override {
        while (!process_queue_.empty())
        {
            process_queue_.pop();
        }
    }
    
    void logic(int total_tick) {
        auto psr_mgr = ProcessorManager::getInstance();
        std::unique_ptr<std::queue<std::shared_ptr<Process>>> enter_process = getEnterProcess(total_tick);
        
        while (!enter_process->empty()) {
            std::shared_ptr<Process> process = enter_process->front();
            process_queue_.push(process);
            enter_process->pop();
        }

        while (psr_mgr->countAvailable() > 0 && !process_queue_.empty())
        {
            std::shared_ptr<Process> process = process_queue_.front();
            psr_mgr->addProcess(process);
            process_queue_.pop();
        }

        psr_mgr->tick();
    }

};