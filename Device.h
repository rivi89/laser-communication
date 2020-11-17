#ifndef DEVICE_H
#define DEVICE_H

#include  <time.h>


class Device
{

public:
	enum Mode
	{
		MASTER = 0,
		SLAVE
	};
	Device() : _mode(SLAVE)
	{
		
	}
	virtual ~Device()
	{
	}
	virtual void setMode(Mode mode)
	{
		_mode = mode;
	}
	virtual float readDistance() = 0;
protected:
	Mode _mode;
	float distance;
};


class Test : public Device
{
public:
	Test() : Device()
	{
	}
	virtual ~Test()
	{
	}

	float readDistance()
	{

	//	int intDist = rand() % 100;
	//	float distance = (float)intDist / 10 + 1000;

		int intDist = rand() % 50;
		float distance = (float)intDist / 10 + 700;
		return distance;
	}

protected:
};





#endif