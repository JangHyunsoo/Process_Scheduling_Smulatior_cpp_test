#pragma once
#include "Job.h"
#include <exception>
class Process
{
private:
	int process_no_;
	int arrival_time_;
	int brust_time_;
	int cur_brust_time_;

public:
	Process(Job _job) : process_no_(_job.job_no), arrival_time_(_job.arrival_time), brust_time_(_job.brust_time), cur_brust_time_(_job.brust_time){}
	~Process() {}
	void tick() {
		if (brust_time_ <= 0) {
			throw std::exception("process tick but already dead..");
		}
		brust_time_--;
	}
	bool isDead() {
		return cur_brust_time_ == 0;
	}
};

