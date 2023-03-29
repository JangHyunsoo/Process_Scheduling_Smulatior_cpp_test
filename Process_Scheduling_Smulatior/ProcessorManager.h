#pragma once
#include "Processor.h"
#include <vector>

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
	std::vector<Processor> core_vec_;
public:
	void init() {
		core_vec_ = std::vector<Processor>();
		for (int i = 0; i < p_core_count; i++)
		{
			core_vec_.push_back(Processor(core_vec_.size() - 1, CoreType::PERFOR));
		}
		for (int i = 0; i < e_core_count; i++)
		{
			core_vec_.push_back(Processor(core_vec_.size() - 1, CoreType::EFFIC));
		}

	}
};

