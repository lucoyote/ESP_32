/*
 * UDPListenTask2.h
 *
 *  Created on: 13 feb 2018
 *      Author: luca
 */

#ifndef MAIN_UDPLISTENTASK_H_
#define MAIN_UDPLISTENTASK_H_

#include <Task.h>
#include <Socket.h>
#include <esp_log.h>
#include "CLogger.h"

class UDPListenTask: public Task
{
public:
	UDPListenTask ();

	virtual ~UDPListenTask();
	void run(void *data);

	bool Avalaible;
	bool bReadTask;
	int ReadedBytes;

	long TotalBytes;
	long TotalPackets;
	long lostPackets;
	long lPacketCounter;

	void SetCallback(void* Callback(int, void*));

private:
	int _port;
	unsigned char _buffer[902];
	Socket _socket;


	using f_void_t = void(*)(int, void *);

	f_void_t _ReadCallback;
};

#endif /* MAIN_UDPLISTENTASK_H_ */
