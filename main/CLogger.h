/*
 * CLogger.h
 *
 *  Created on: 04 mar 2018
 *      Author: luca
 */

#ifndef MAIN_CLOGGER_H_
#define MAIN_CLOGGER_H_

#include <vector>
#include <string>
#include "Task.h"
#include <esp_log.h>

#define LOG_BUFFER_SIZE 100

typedef struct {
	esp_log_level_t Loglevel;
    std::string Tag;
    std::string Message;
}LogVoice_t;



class CLogger : public Task
{
public:
	static CLogger * getInstance();

	void SetLogLevel (esp_log_level_t iDefaultLogLevel);
	void Log (esp_log_level_t iLogLevel, std::string sTag, std::string sMessage);

private:
	static CLogger * m_Instance;
	static bool m_isvalidInstance;

	CLogger();
	virtual ~CLogger();
	void run(void *data);

	LogVoice_t m_Messages [LOG_BUFFER_SIZE];
	int m_iPushPosition = 0;
	int m_iPopPosition = 0;

	esp_log_level_t ConfiguredLogLevel = ESP_LOG_INFO;

	portMUX_TYPE m_mux;

};

#endif /* MAIN_CLOGGER_H_ */
