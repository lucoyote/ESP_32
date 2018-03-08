/*
 * TCPListenTask.h
 *
 *  Created on: 13 feb 2018
 *      Author: luca
 */

#ifndef MAIN_TCPLISTENTASK_H_
#define MAIN_TCPLISTENTASK_H_

#include <Task.h>
#include <Socket.h>
#include <esp_log.h>

class TCPListenTask: public Task
{
public:
	TCPListenTask (int Port);

	virtual ~TCPListenTask();
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
	unsigned char _buffer[4192];
	Socket _socket;


	using f_void_t = void(*)(int, void *);

	f_void_t _ReadCallback;
};

#endif /* MAIN_UDPLISTENTASK_H_ */
