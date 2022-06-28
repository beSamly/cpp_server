#pragma once
#include <functional>

/*---------
	Job
----------*/

class Job
{
public:
	Job(CallbackType&& callback, bool isInterval = false) : _callback(std::move(callback)), _isInterval(isInterval)
	{
	}

	template<typename T, typename Ret, typename... Args>
	Job(std::shared_ptr<T> owner, Ret(T::* memFunc)(Args...), Args&&... args)
	{
		_callback = [owner, memFunc, args...]()
		{
			(owner.get()->*memFunc)(args...);
		};
	}

	void Execute()
	{
		_callback();
	}

private:
	CallbackType _callback;
	bool _isInterval;
};

