#pragma once

#include <Windows.h>
#include "Device.h"

class Glm : public Device
{
public:
	Glm();
	virtual ~Glm();
	float readDistance();
protected:
	HANDLE hComm;
};
