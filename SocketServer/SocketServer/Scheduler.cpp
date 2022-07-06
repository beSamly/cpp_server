#include "pch.h"
#include "Scheduler.h"
#include "JobTimer.h"

Scheduler::Scheduler()
{
}

void Scheduler::SetInterval(JobRef job)
{
	GJobTimer->SetInterval(10000,job);
}
