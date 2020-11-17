#include "websocket.h"

#include "DeviceFactory.h"
#include <fstream>

#include "MeasureCollector.h"
#include <thread>
#include <Windows.h>

webSocket webs;

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		printf("Ctrl-C event\n\n");
		webs.stopServer();
		return TRUE;

		// CTRL-CLOSE: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		printf("Ctrl-Close event\n\n");
		return TRUE;

		// Pass other signals to the next handler. 
	case CTRL_BREAK_EVENT:
		printf("Ctrl-Break event\n\n");
		return FALSE;

	case CTRL_LOGOFF_EVENT:
		printf("Ctrl-Logoff event\n\n");
		return FALSE;

	case CTRL_SHUTDOWN_EVENT:
		printf("Ctrl-Shutdown event\n\n");
		return FALSE;

	default:
		return FALSE;
	}
}

int main ()
{
	SetConsoleCtrlHandler(CtrlHandler, TRUE);
	DeviceFactory laser_factory;
	//Device* d = nullptr;
	std::shared_ptr<Device> d;
	std::ifstream ifs("data\\config.cfg");
	if (ifs.is_open())
	{
		std::string laser_name;
		ifs >> laser_name;

		d = laser_factory.create(laser_name);
	}

	MeasureCollector collector(*d, webs);

	webs.startServer();

	return 0;
}

