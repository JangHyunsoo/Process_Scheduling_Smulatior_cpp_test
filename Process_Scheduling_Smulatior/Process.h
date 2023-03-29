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

public:
	int getNo() {
		return process_no_;
	}

	void tick(int work) {
		brust_time_ -= work;
		if (brust_time_ < 0) {
			brust_time_ = 0;
		}
	}

	bool isDead() {
		return cur_brust_time_ <= 0;
	}
};

