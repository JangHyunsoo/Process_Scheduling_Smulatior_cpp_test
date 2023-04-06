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
	int waiting_time_;
	int remain_quantum_time_;

public:
	Process(Job _job) : process_no_(_job.job_no), arrival_time_(_job.arrival_time), burst_time_(_job.burst_time), cur_burst_time_(_job.burst_time), waiting_time_(0), remain_quantum_time_(-1){}
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
	int getWaitingTime() {
		return waiting_time_;
	}
	int getQuantumTime() {
		return remain_quantum_time_;
	}
	void setQuantumtime(int _quantum_time) {
		remain_quantum_time_ = _quantum_time;
	}

	void setWaitingTime(int _total_tick) {
		waiting_time_ = _total_tick - arrival_time_ - burst_time_ + cur_burst_time_;
		if (waiting_time_ < 0) {
			waiting_time_ = 0;
		}
	}

	/// <summary>
	/// remaining_time -= work? or remaining_time -= 1? 
	/// </summary>
	void tick(int work) {
		cur_burst_time_ -= work;
		remain_quantum_time_ -= 1;
		if (cur_burst_time_ < 0) {
			cur_burst_time_ = 0;
		}
		if (remain_quantum_time_ < 0) {
			remain_quantum_time_ = 0;
		}
	}

	bool isDead() {
		return cur_burst_time_ <= 0;
	}
};