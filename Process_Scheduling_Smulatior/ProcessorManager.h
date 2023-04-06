#pragma once
#include "Processor.h"
#include <iostream>
#include <vector>
#include <list>
#include <tuple>

class ProcessorManager
{
	// singleton part
private:
	static ProcessorManager* instance_;
	ProcessorManager() : p_core_count(2), e_core_count(2) {}
	ProcessorManager& operator=(ProcessorManager&& other) {}
	ProcessorManager& operator=(const ProcessorManager& other) {}
	ProcessorManager(ProcessorManager&& other) {}
	ProcessorManager(const ProcessorManager& other) {}
	~ProcessorManager() {}
public:
	static ProcessorManager* getInstance() {
		if (instance_ == nullptr) {
			instance_ = new ProcessorManager();
		}
		return instance_;
	}
private:
	int p_core_count;
	int e_core_count;
	std::vector<Processor> processor_vec_;
public:
	void init() {
		processor_vec_ = std::vector<Processor>();
		for (int i = 0; i < p_core_count; i++)
		{
			processor_vec_.push_back(Processor(processor_vec_.size(), ProcessorType::PERFOR));
		}
		for (int i = 0; i < e_core_count; i++)
		{
			processor_vec_.push_back(Processor(processor_vec_.size(), ProcessorType::EFFIC));
		}
	}

	void tick() {
		for (Processor& processor : processor_vec_) {
			processor.tick();
		}
	}

	bool isDone(){
		for (Processor& psr : processor_vec_) {
			if (psr.isRun()) return false;
		}
		return true;
	}

	int countProcessor() {
		if (processor_vec_.empty()) return 0;
		else return processor_vec_.size();
	}

	int countAvailable() {
		int count = 0;
		for (Processor& processor : processor_vec_) {
			if (!processor.isRun())
				count++;
		}
		return count;
	}

	int countQuantumAvailable() {
		int count = 0;
		for (Processor& processor : processor_vec_) {
			if (!processor.isRunQuantum()) {
				count++;
			}
		}
		return count;
	}

	/// <returns>core idx, max time</returns>
	std::pair<int, int> maxCurBurstTime() {
		int max_idx = -1;
		int max_value = -1;

		for (int i = 0; i < processor_vec_.size(); i++)
		{
			int burst_time = 987654321;

			if (processor_vec_[i].isRun()) {
				burst_time = processor_vec_[i].getCurProcess()->getCurBurstTime();
			}

			if (burst_time > max_value) {
				max_idx = i;
				max_value = burst_time;
			}
		}

		return { max_idx, max_value };
	}

	Processor& getProcessor(int idx) {
		if (processor_vec_.size() <= idx) {
			throw std::exception("processor_vec overflow");
		}
		return processor_vec_[idx];
	}

	Processor& getAvailableProcessor() {
		for (Processor& processor : processor_vec_) {
			if (!processor.isRun())
				return processor;
		}
		return processor_vec_[0];
	}

	Processor& getQuantumAvailableProcessor() {
		for (Processor& processor : processor_vec_) {
			if (!processor.isRunQuantum()) {
				return processor;
			}
		}
		return processor_vec_[0];
	}

	bool addProcess(std::shared_ptr<Process> _process) {
		int psr_size = processor_vec_.size();

		for (int i = 0; i < psr_size; i++)
		{
			if (!processor_vec_[i].isRun()) {
				processor_vec_[i].addProcess(_process);
				return true;
			}
		}
		return false;
	}

	/// <returns>queue empty : True / queue non-empty : False</returns>
	bool appendProcess(std::queue<Process>& _process_queue) {
		int psr_size = processor_vec_.size();

		for (int i = 0; i < psr_size; i++)
		{
			if (!processor_vec_[i].isRun()) {
				processor_vec_[i].addProcess(std::shared_ptr<Process>(&_process_queue.front()));
				_process_queue.pop();
			}
		}
		return _process_queue.empty();
	}

	void printStat(int total_time) {
		std::cout << "\n\ntotal : " << total_time << '\n';
		
		for (Processor& psr : processor_vec_)
		{
			psr.printStat();
		}
	}

	void printHistory(int total_time) {
		for (Processor& psr : processor_vec_) {
			psr.printHistory(total_time);
		}
	}
};

ProcessorManager* ProcessorManager::instance_ = nullptr;

