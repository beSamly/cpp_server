#pragma once

struct TimerItem
{

	TimerItem(uint64 executeTick, JobRef job, uint64 tickAfter ,bool isInterval = false) : executeTick(executeTick), job(job), tickAfter(tickAfter), isInterval(isInterval) {

	}

	bool operator<(const TimerItem& other) const
	{
		return executeTick > other.executeTick;
	}

	uint64 executeTick = 0;
	uint64 tickAfter = 0;
	bool isInterval;
	JobRef job = nullptr;
};

/*--------------
	JobTimer
---------------*/

class JobTimer
{
public:
	void			Reserve(uint64 tickAfter, JobRef job, bool isInterval = false);
	void			SetInterval(uint64 tickAfter, JobRef job);
	void			Execute(uint64 now);
	void			Clear();

private:
	USE_LOCK;
	PriorityQueue<TimerItem>	_items;
	Atomic<bool>				_isExecuting = false;
};

