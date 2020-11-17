#ifndef MCOLLECTOR_H
#define MCOLLECTOR_H

#include <thread>

#include "WheelMeasure.h"
#include "Observer.h"
#include "Device.h"


class MeasureCollector
{
public:
	MeasureCollector(Device& dev, Observer& obs) : _obs(obs), _device(dev)
	{
		th = std::thread(&MeasureCollector::th_fct, this);
	}

	~MeasureCollector()
	{
		running = false;
		if (th.joinable())
		{
			th.join();
		}
	}

	enum MeasureMode
	{
		//invio e ricezione della misura dal laser (laser in modalitá slave)
		LIVE_MEASURE,
		//lettura sequenziale della misura dal laser (laser in modalitá master)
		SEQ_MEASURE
	};
	void SetMode(MeasureMode& mode)
	{
		_mode = mode;
	};

protected:
	MeasureMode _mode = SEQ_MEASURE;
	Device& _device;
	std::thread th;
	bool running;
	Observer& _obs;
	void th_fct()
	{
		WheelMeasure m;

		while (running)
		{
			switch (_mode)
			{
			case LIVE_MEASURE:
				{
					//devo spedire il comando e ricevere il comando aggiornare la struttura wheelmeasure
					//e notificare alla websocket
					m.set("Distance", _device.readDistance());
					_obs.notify(m);
					//era piú giusto una classe di settings...
					std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				}
				break;
			case SEQ_MEASURE:

			{ 

				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				m.set("FrontLeft", _device.readDistance());
				_obs.notify(m);

				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				m.set("RearLeft", _device.readDistance());
				_obs.notify(m);

				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				m.set("RearRight", _device.readDistance());
				_obs.notify(m);

				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				m.set("FrontRight", _device.readDistance());
				_obs.notify(m);
			}


				break;
			default:
				break;
			}
		}
	}

};



#endif