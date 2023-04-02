#pragma once
#include "Job.h"
#include <exception>
class Process
{
private:
	int process_no_;
	int arrival_time_;
	int burst_time_;
	int cur_burst_time_;

public:
	Process(Job _job) : process_no_(_job.job_no), arrival_time_(_job.arrival_time), burst_time_(_job.burst_time), cur_burst_time_(_job.burst_time){}
	~Process() {}

public:
	int getNo() {
		return process_no_;
	}
	int getArrival() {
		return arrival_time_;
	}
	int getBurstTime() {
		return burst_time_;
	}
	int getCurBurstTime() {
		return cur_burst_time_;
	}
	void tick(int work) {
		cur_burst_time_ -= work;
		if (cur_burst_time_ < 0) {
			cur_burst_time_ = 0;
		}
	}

	bool isDead() {
		return cur_burst_time_ <= 0;
	}
};

