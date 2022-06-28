#include "pch.h"
#include "RunInterval.h"
#include "JobTimer.h"

RunInterval::RunInterval()
{
}

void RunInterval::SetInterval(JobRef job)
{
	GJobTimer->SetInterval(10000,job);
}
