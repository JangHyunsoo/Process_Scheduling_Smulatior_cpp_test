#pragma once
#include "Job.h"
#include <random>
#include <algorithm>
#include <queue>
#include <list>


class JobSimulator
{
// singleton part
private:
	static JobSimulator* instance_;
	JobSimulator() {}
	~JobSimulator() {}
public:
	static JobSimulator* getInstance() {
		if (instance_ == nullptr) {
			instance_ = new JobSimulator();
		}
		return instance_;
	}

// logic part
private:
	int job_count = 0;
	// heap으로 수정할 수도 있음.
	std::list<Job> job_list_;
	std::queue<Job> job_queue_;

	//random
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> arrival_time_dis_;
	std::uniform_int_distribution<int> brust_time_dis_;
public:
	void init() {
		job_list_ = std::list<Job>();
		job_queue_ = std::queue<Job>();
		initRandom();
		for (int i = 0; i < 10; i++)
		{
			addJobByRandom();
		}
		carryQueue();
	}
	bool isEmpty() {
		return job_queue_.empty();
	}
	Job& getJob() {
		Job& job = job_queue_.front();
		job_queue_.pop();
		return job;
	}
private:
	void initRandom() {
		gen = std::mt19937(rd());
		arrival_time_dis_ = std::uniform_int_distribution<int>(0, 20);
		brust_time_dis_ = std::uniform_int_distribution<int>(1, 5);
	}
	void addJob(int _arrival_time, int _brust_time) {
		
		job_list_.push_back(Job{ ++job_count, _arrival_time, _brust_time });
	}
	void addJobByRandom() {
		addJob(arrival_time_dis_(gen), brust_time_dis_(gen));
	}
	void carryQueue() {
		//std::sort(job_list_.begin(), job_list_.end(), [](Job one, Job other){
		//	if (one.arrival_time == other.arrival_time) return one.job_no < other.job_no;
		//	else return one.arrival_time < other.arrival_time;
		//});
		for (auto item : job_list_) {
			job_queue_.push(item);
		}
	}
};

JobSimulator* JobSimulator::instance_ = nullptr;