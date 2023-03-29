#pragma once
#include "Scheduler.h"
#include "ProcessorManager.h"

class FcfsScheduler : public Scheduler
{
public:
    FcfsScheduler() : Scheduler() {}
public:
    void init() override {
        while (!process_queue_.empty())
        {
            process_queue_.pop();
        }
    }
    
    void logic(int total_tick) {
        auto psr_mgr = ProcessorManager::getInstance();
        
        while (psr_mgr->countAvailable() > 0 && !process_queue_.empty())
        {
            Process* process = process_queue_.front();
            psr_mgr->addProcess(process);
            process_queue_.pop();
        }

        psr_mgr->tick();
    }

};