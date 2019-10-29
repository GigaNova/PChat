#pragma once
#include <thread>

class Thread
{
public:
	Thread() = default;
	virtual ~Thread() = default;

	void start()
	{
		std::thread thread(std::bind(&Thread::run, this));
		thread.detach();
	}
	
	virtual void run() const = 0;
};
