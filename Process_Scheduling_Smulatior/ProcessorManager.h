#pragma once
#include "Processor.h"
#include <vector>
#include <list>

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

	int countAvailable() {
		int count = 0;
		for (Processor& processor : processor_vec_) {
			if (!processor.isRun())
				count++;
		}
		return count;
	}

	bool addProcess(Process* _process) {
		int psr_size = processor_vec_.size();

		for (int i = 0; i < psr_size; i++)
		{
			if (!processor_vec_[i].isRun()) {
				processor_vec_[i].addProcess(std::shared_ptr<Process>(_process));
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

	void printHistory(int total_time) {
		for (Processor& psr : processor_vec_) {
			psr.printHistory(total_time);
		}
	}
};

ProcessorManager* ProcessorManager::instance_ = nullptr;

