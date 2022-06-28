#include "pch.h"
#include "JobTimer.h"
#include "JobQueue.h"
#include "Job.h"

/*--------------
	JobTimer
---------------*/
void JobTimer::Reserve(uint64 tickAfter, JobRef job, bool isInterval)
{
	const uint64 executeTick = ::GetTickCount64() + tickAfter;
	auto timerItem = TimerItem(executeTick, job, tickAfter, isInterval);

	WRITE_LOCK;
	_items.push(timerItem);
}

void JobTimer::SetInterval(uint64 tickAfter, JobRef job)
{
	Reserve(tickAfter, job, true);
}

void JobTimer::Execute(uint64 now)
{
	// 한 번에 1 쓰레드만 통과
	if (_isExecuting.exchange(true) == true)
		return;

	Vector<TimerItem> items;

	{
		WRITE_LOCK;

		while (_items.empty() == false)
		{
			const TimerItem& timerItem = _items.top();
			if (now < timerItem.executeTick)
				break;

			items.push_back(timerItem);
			_items.pop();
		}
	}

	for (TimerItem& item : items)
	{
		JobRef job = item.job;
		job->Execute();

		// Interval 계열이면 다시 등록
		if (item.isInterval) {
			Reserve(item.tickAfter, job, true);
		}
	}

	// 끝났으면 풀어준다
	_isExecuting.store(false);
}

void JobTimer::Clear()
{
	WRITE_LOCK;

	while (_items.empty() == false)
	{
		const TimerItem& timerItem = _items.top();
		_items.pop();
	}
}
