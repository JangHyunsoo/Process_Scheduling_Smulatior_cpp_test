#include <iostream>
#include <sstream>
#include "SchedulerManager.h"
#include "JobSimulator.h"
#include "ProcessorManager.h"

using namespace std;

void printJob(Job& job) {
	cout << "No: " << job.job_no << " | A.T: " << job.arrival_time << " | B.T: " << job.brust_time << '\n'; 
}

int main()
{
	SchedulerManager::getInstance()->init();
	SchedulerManager::getInstance()->run();

}