#pragma once
#include "Process.h"
#include <memory>

enum class CoreType
{
	EFFIC,
	PERFOR
};

class Processor
{
private:
	int core_no_;
	CoreType core_type_;
	std::shared_ptr<Process> cur_process_;

public:
	Processor(int _core_no, CoreType _core_type = CoreType::EFFIC) : core_no_(_core_no), core_type_(_core_type), cur_process_{nullptr} {}
	~Processor(){}
	
	int getCoreNo() {
		return core_no_;
	}
	CoreType getCoreType() {
		return core_type_;
	}
	void addProcess(std::shared_ptr<Process> _process) {
		cur_process_ = _process;
	}
	void tick() {
		cur_process_->tick();
	}
};

