#pragma once

class Thread
{
public:
	Thread() = default;
	virtual ~Thread() = default;

	virtual void run() const = 0;
};