#pragma once
#include <chrono>

class TimeHelper
{
public:
	static TIMESTAMP_STRUCT GetNow() {
		// TODO
		TIMESTAMP_STRUCT currentTimestamp;
		currentTimestamp.fraction = 0;
		currentTimestamp.hour = 0;
		currentTimestamp.minute = 0;
		currentTimestamp.second = 0;
		currentTimestamp.year = 2022;
		currentTimestamp.month = 11;
		currentTimestamp.day = 13;
		return currentTimestamp;
	}
};

