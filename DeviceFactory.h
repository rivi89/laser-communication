#pragma once

#include <string>
#include "glm.h"


class DeviceFactory
{
public:
	//Device* create(std::string device_name)
	std::shared_ptr<Device> create(std::string device_name)
	{
		if (device_name == "TEST")
		{
			//t = new Test();
			t = std::make_shared<Test>();
		}
		if (device_name == "GLM50C")
		{
			//t = new Glm();
			t = std::make_shared<Glm>();
		}
		return t;
	}

	DeviceFactory() : t(nullptr)
	{

	}

	~DeviceFactory()
	{
		/*
		if (t != nullptr)
			delete t;
			*/
	}
	//Device* t;
	std::shared_ptr<Device> t;
};