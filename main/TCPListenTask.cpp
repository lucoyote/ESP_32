/*
 * TCPListenTask.cpp
 *
 *  Created on: 13 feb 2018
 *      Author: luca
 */

#include "TCPListenTask.h"

TCPListenTask::TCPListenTask (int Port) : Task ("TCPListenTask",10000,15)
{
	TCPListenTask::_port = Port;

	TCPListenTask::setCore(0);

	TCPListenTask::Avalaible = false;
	TCPListenTask::ReadedBytes = 0;

	TCPListenTask::_ReadCallback = 0;
	TCPListenTask::bReadTask = true;
	TCPListenTask::TotalBytes = 0;
	TCPListenTask::TotalPackets = 0;
	TCPListenTask::lostPackets = 0;
	TCPListenTask::lPacketCounter = 0;
}

TCPListenTask::~TCPListenTask()
{
	// TODO Auto-generated destructor stub
}

void TCPListenTask::run(void *data)
{
	TCPListenTask::_socket.createSocket(true);

	fcntl(_socket.getHandle(),F_SETFL,O_NONBLOCK);

	TCPListenTask::_socket.bind(TCPListenTask::_port, INADDR_ANY);
	TCPListenTask::_socket.listen(TCPListenTask::_port, false, true);

	int received = 0;
	bool bClientConnected;

	while(TCPListenTask::bReadTask)
	{
		TCPListenTask::delay(1000);
		Socket clientsocket = TCPListenTask::_socket.accept();




		bClientConnected = true;
		ESP_LOGI("TCPListenTask", "Client connected");

		if (bClientConnected)
		{
			ESP_LOGI("TCPListenTask", "bClientConnected");
		}
		else
		{
			ESP_LOGI("TCPListenTask", "NOT bClientConnected");
		}

		while (bClientConnected)
		{
			//ESP_LOGI("TCPListenTask", "Receive");

			received = clientsocket.receive(TCPListenTask::_buffer, 902, false);

			if (received>0)
			{
				ESP_LOGI("TCPListenTask", "Received packet: %d bytes: %d - %d", received, TCPListenTask::_buffer[0], TCPListenTask::_buffer[1]);

				TCPListenTask::ReadedBytes = received;
				TCPListenTask::Avalaible = true;
				TCPListenTask::TotalBytes += received;
				TCPListenTask::TotalPackets ++;

				if (received==2)
				{
					if (TCPListenTask::lPacketCounter< 16)
						TCPListenTask::lostPackets ++;

					TCPListenTask::lPacketCounter = 0;
				}
				else
				{
					TCPListenTask::lPacketCounter++;
				}

				if (TCPListenTask::_ReadCallback)
				{
					TCPListenTask::_ReadCallback(received, TCPListenTask::_buffer);
				}

			}
			else
			{
				if (received <=0)
				{
					ESP_LOGI("TCPListenTask", "Client disconnected");
					clientsocket.close();
					bClientConnected = false;
					TCPListenTask::delay(1000);
				}
			}
		}
		//TCPListenTask::delay(1);
	}
}

void TCPListenTask::SetCallback(void* Callback(int,void*))
{
	//TCPListenTask::_ReadCallback = Callback;
}
