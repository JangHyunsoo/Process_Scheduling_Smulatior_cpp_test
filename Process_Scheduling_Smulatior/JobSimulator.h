#pragma once
#include "Job.h"
#include <random>
#include <algorithm>
#include <queue>
#include <list>
#include <memory>

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
	std::vector<Job> job_vec_;
	std::queue<Job> job_queue_;

	//random
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> arrival_time_dis_;
	std::uniform_int_distribution<int> burst_time_dis_;
public:
	void init() {
		job_vec_ = std::vector<Job>();
		job_queue_ = std::queue<Job>();
		initRandom();
		for (int i = 0; i < 30; i++)
		{
			addJobByRandom();
		}

		for (auto job : job_vec_)
		{
			printJob(job);
		}
		carryQueue();
	}
	bool isEmpty() {
		return job_queue_.empty();
	}

	bool isDone() {
		return isEmpty();
	}

	Job& getJob() {
		Job& job = job_queue_.front();
		job_queue_.pop();
		return job;
	}
	std::unique_ptr<std::list<Job>> getJobs(int total_tick) {
		std::unique_ptr<std::list<Job>> ret = std::make_unique<std::list<Job>>();
		
		if (job_queue_.empty()) return std::move(ret);
	
		while (!job_queue_.empty())
		{
			if (job_queue_.front().arrival_time == total_tick) {
				ret->push_back(job_queue_.front());
				job_queue_.pop();
			}
			else break;
		}
		return std::move(ret);
	}
private:
	void initRandom() {
		gen = std::mt19937(rd());
		arrival_time_dis_ = std::uniform_int_distribution<int>(0, 20);
		burst_time_dis_ = std::uniform_int_distribution<int>(1, 10);
	}
	void addJob(int _arrival_time, int _burst_time) {
		
		job_vec_.push_back(Job{++job_count, _arrival_time, _burst_time });
	}
	void addJobByRandom() {
		int at = arrival_time_dis_(gen);
		int bt = burst_time_dis_(gen);
		addJob(at, bt);
	}
	void carryQueue() {
		std::sort(job_vec_.begin(), job_vec_.end(), [](Job one, Job other){
			if (one.arrival_time == other.arrival_time) return one.job_no < other.job_no;
			else return one.arrival_time < other.arrival_time;
		});
		for (auto item : job_vec_) {
			job_queue_.push(item);
		}
	}

	void printJob(Job& job) {
		std::cout << "No: " << job.job_no << "\t\tA.T: " << job.arrival_time << "\t\tB.T: " << job.burst_time << '\n';
	}

};

JobSimulator* JobSimulator::instance_ = nullptr;