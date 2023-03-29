#include <iostream>
#include <sstream>
#include "JobSimulator.h"

using namespace std;

void printJob(Job& job) {
	cout << "No: " << job.job_no << " | A.T: " << job.arrival_time << " | B.T: " << job.brust_time << '\n'; 
}

int main()
{
	JobSimulator::getInstance()->init();
	auto job_inst = JobSimulator::getInstance();
	while (!job_inst->isEmpty())
	{
		auto job = job_inst->getJob();
		printJob(job);
	}
}