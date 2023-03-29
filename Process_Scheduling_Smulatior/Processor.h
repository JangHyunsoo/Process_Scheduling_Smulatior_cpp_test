#pragma once
#include "Process.h"
#include <memory>
#include <vector>
#include <iostream>

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
		if (cur_process_ == nullptr) return false;
		else return is_run_;
	}

	void addProcess(std::shared_ptr<Process> _process) {
		cur_process_ = _process;
		is_run_ = true;
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
			history_.push_back(0);
		}
	}

	void printHistory(int total_time) {
		std::cout << "P" << processor_no_ << " :\t";
		for (int i = 0; i <= total_time; i++)
		{
			if (history_.size() - 1 <= i) {
				std::cout << "0\t";
			}
			else {
				std::cout << history_[i] << "\t";
			}
		}
		std::cout << '\n';
	}
};