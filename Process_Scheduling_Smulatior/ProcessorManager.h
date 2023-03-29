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
			processor_vec_.push_back(Processor(processor_vec_.size() - 1, ProcessorType::PERFOR));
		}
		for (int i = 0; i < e_core_count; i++)
		{
			processor_vec_.push_back(Processor(processor_vec_.size() - 1, ProcessorType::EFFIC));
		}
	}
	
	int countAvailable() {
		int count = 0;
		for (auto processor : processor_vec_) {
			if (!processor.isRun())
				count++;
		}

		return count;
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
};

ProcessorManager* ProcessorManager::instance_ = nullptr;

