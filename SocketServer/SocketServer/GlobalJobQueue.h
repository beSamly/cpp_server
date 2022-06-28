#pragma once
#include "LockQueue.h"

/*--------------------
	GlobalJobQueue
---------------------*/

class GlobalJobQueue
{
public:
	GlobalJobQueue();
	~GlobalJobQueue();

	void					Push(JobRef jobQueue);
	JobRef				Pop();

private:
	LockQueue<JobRef> _jobQueues;
};

