#pragma once
#include "Process.h"
#include <memory>
#include <vector>

enum class ProcessorType
{
	EFFIC,
	PERFOR
};

class Processor
{
private:
	int processor_no_;
	ProcessorType processor_type_;
	std::shared_ptr<Process> cur_process_;
	bool is_run_;

	std::vector<int> history_;
public:
	Processor(int _core_no, ProcessorType _core_type = ProcessorType::EFFIC) : processor_no_(_core_no), processor_type_(_core_type), cur_process_{ nullptr }, is_run_(false), history_(std::vector<int>()){}
	~Processor() {}

	int getNo() {
		return processor_no_;
	}
	ProcessorType getType() {
		return processor_type_;
	}
	Process& getCurProcess() {
		return *cur_process_;
	}
	bool isRun() {
		return !is_run_;
	}

	void addProcess(std::shared_ptr<Process> _process) {
		if (!_process->isDead()) {
			cur_process_ = _process;
			is_run_ = true;
		}

	}
	void tick() {
		if (is_run_) {
			cur_process_->tick(processor_type_ == ProcessorType::EFFIC ? 1 : 2);
			history_.push_back(cur_process_->getNo());
			if (cur_process_->isDead())
			{
				cur_process_ = nullptr;
				is_run_ = false;
			}
		}
		else {
			history_.push_back(-1);
		}
	}
};