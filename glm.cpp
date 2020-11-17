#include <Windows.h>

#include "Glm.h"
#include <stdio.h>


Glm::Glm()
{
	hComm = CreateFile("\\\\.\\COM34", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hComm == INVALID_HANDLE_VALUE)
		printf("Error in opening serial port\n");
	else
		printf("opening serial port successful\n");
}

Glm::~Glm()
{
	CloseHandle(hComm);
}


float Glm::readDistance()
{
	if (hComm == INVALID_HANDLE_VALUE)
		return -1;
	
	char lpBuffer[4];

	lpBuffer[0] = 0xc0;
	lpBuffer[1] = 0x40;
	lpBuffer[2] = 0x00;
	lpBuffer[3] = 0xee;

	DWORD written;
	bool Status = WriteFile(hComm, lpBuffer, 4, &written, FALSE);
	if (Status == false)
		return -1;
	if (written != 4)
		return -1;

	DWORD read;
	unsigned char TempChar[7];
	int c = 0;
	bool recv = ReadFile(hComm, &TempChar, 7, &read, NULL);

	if (recv && read == 7)
	{
		int a = TempChar[2];
		int b = TempChar[3];
		int c = TempChar[4];
		int d = TempChar[5];
		distance = a + (b << 8)  + (c << 16) + (d <<24);
		distance = distance * 0.05;

		return distance;
	}
	return -1;
}

