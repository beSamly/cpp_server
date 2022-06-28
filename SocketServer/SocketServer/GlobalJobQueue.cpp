#include "pch.h"
#include "GlobalJobQueue.h"
#include "LockQueue.h"

/*-------------------
	GlobalJobQueue
--------------------*/

GlobalJobQueue::GlobalJobQueue()
{

}

GlobalJobQueue::~GlobalJobQueue()
{

}

void GlobalJobQueue::Push(JobRef job)
{
	_jobQueues.Push(job);
}

JobRef GlobalJobQueue::Pop()
{
	return _jobQueues.Pop();
}
