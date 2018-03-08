/*
 * UDPListenTask2.cpp
 *
 *  Created on: 13 feb 2018
 *      Author: luca
 */

#include "UDPListenTask.h"

UDPListenTask::UDPListenTask () : Task ("UDPListenTask",2048,15)
{
	UDPListenTask::_port = 2390;

	UDPListenTask::setCore(1);

	UDPListenTask::Avalaible = false;
	UDPListenTask::ReadedBytes = 0;

	UDPListenTask::_ReadCallback = 0;
	UDPListenTask::bReadTask = true;
	UDPListenTask::TotalBytes = 0;
	UDPListenTask::TotalPackets = 0;
	UDPListenTask::lostPackets = 0;
	UDPListenTask::lPacketCounter = 0;
}

UDPListenTask::~UDPListenTask()
{
	// TODO Auto-generated destructor stub
}

void UDPListenTask::run(void *data)
{
	UDPListenTask::_socket.createSocket(true);

	UDPListenTask::_socket.listen(2390, true, true);

	while(UDPListenTask::bReadTask)
	{
		int received = UDPListenTask::_socket.receive(UDPListenTask::_buffer, 902, false);
		if (received>0)
		{
			char message[80];
			sprintf (message, "Received packet: %d bytes: %d - %d", received, UDPListenTask::_buffer[0], UDPListenTask::_buffer[1]);

			CLogger::getInstance()->Log(ESP_LOG_INFO,"UDPListenTask",message);

			UDPListenTask::ReadedBytes = received;
			UDPListenTask::Avalaible = true;
			UDPListenTask::TotalBytes += received;
			UDPListenTask::TotalPackets ++;

			if (received==2)
			{
				if (UDPListenTask::lPacketCounter< 16)
					UDPListenTask::lostPackets ++;

				UDPListenTask::lPacketCounter = 0;
			}
			else
			{
				UDPListenTask::lPacketCounter++;
			}

			if (UDPListenTask::_ReadCallback)
			{
				UDPListenTask::_ReadCallback(received, UDPListenTask::_buffer);
			}

		}
		//UDPListenTask::delay(1);
	}
}

void UDPListenTask::SetCallback(void* Callback(int,void*))
{
	//UDPListenTask::_ReadCallback = Callback;
}
