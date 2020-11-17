#ifndef WHEEL_MEASURE_H
#define WHEEL_MEASURE_H


class WheelMeasure
{
public:
	WheelMeasure()
	{
		measures["FrontLeft"] = 0;
		measures["FrontRight"] = 0;
		measures["RearLeft"] = 0;
		measures["RearRight"] = 0;

		measures["Distance"] = 0;
	}

	bool set(std::string target, float value)
	{
		if (measures.find(target) == measures.end())
		{
			return false;
		}
		measures[target] = value;
		return true;
	}

	float get(std::string target)
	{
		if (measures.find(target) == measures.end())
		{
			return -1;
		}
		return measures[target];
	}

	/*
	void set_width_exeption(std::string target, float value)
	{
	if (measures.find(target) == measures.end())
	{
	throw std::exception("Wrong target");
	}
	measures[target] = value;
	}
	*/

protected:
	std::map<std::string, float> measures;

	/*
	int frontLeft;
	int rearLeft;
	int rearRight;
	int frontRight;
	*/
};


#endif
