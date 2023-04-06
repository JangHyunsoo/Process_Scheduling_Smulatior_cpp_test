#pragma once
#include "Scheduler.h"
#include "ProcessorManager.h"
#include <queue>
#include <memory>

class RRScheduler : public Scheduler
{
private:
    std::queue<std::shared_ptr<Process>> process_queue_;
    int time_quantum_;
public:
    RRScheduler(int _time_quantum = 2) : Scheduler(), time_quantum_(_time_quantum) {}
    //RRScheduler() : Scheduler() {}
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

        while (psr_mgr->countQuantumAvailable() > 0 && !process_queue_.empty())
        {
            Processor& processor = psr_mgr->getQuantumAvailableProcessor();
            std::shared_ptr<Process> process = process_queue_.front();
            std::shared_ptr<Process> swap_process = processor.swapProcess(process);
            process->setQuantumtime(time_quantum_);
            process_queue_.pop();

            if (swap_process != nullptr) {
                process_queue_.push(swap_process);
            }
        }

        psr_mgr->tick();
    }
};