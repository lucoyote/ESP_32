/*
 * CLogger.cpp
 *
 *  Created on: 04 mar 2018
 *      Author: luca
 */

#include "CLogger.h"

CLogger * CLogger::m_Instance = NULL;
bool CLogger::m_isvalidInstance = false;

/**
 * @brief Create an instance of the CLogger class.
 * Constructor is private, so this class cannot be instantiated, because this is a Singleton class
 *
 * @return N/A.
 */
CLogger::CLogger() : Task ("LoggerTask",2048,1)
{
	m_mux.owner = portMUX_FREE_VAL;
	m_mux.count = 0;

}

CLogger::~CLogger() {
	CLogger::m_isvalidInstance = false;
}

/**
 * @brief Get the instance of the CLogger class, create the instance if is necessary
 *
 * @return Instance of CLogger class
 */
CLogger * CLogger::getInstance()
{
	if (! CLogger::m_isvalidInstance)
	{
		CLogger::m_isvalidInstance = true;
		m_Instance = new CLogger();
	}
	return m_Instance;

}

void CLogger::SetLogLevel(esp_log_level_t iDefaultLogLevel)
{
	ConfiguredLogLevel = iDefaultLogLevel;
}

void CLogger::run(void * data)
{
	while(1)
	{
		while (m_iPopPosition != m_iPushPosition)
		{
			vTaskEnterCritical(&m_mux);
				LogVoice_t voice = m_Messages[m_iPopPosition];
				m_iPopPosition = (m_iPopPosition +1) %  LOG_BUFFER_SIZE;
			vTaskExitCritical(&m_mux);

			const char * tag = voice.Tag.c_str();
			const char * message = voice.Message.c_str();
			char message2[80];
			sprintf (message2,"%d - %s\n", esp_log_timestamp(), message);

			esp_log_write(voice.Loglevel, tag, message2);

		}
		delay(100);
	}
}

void CLogger::Log (esp_log_level_t iLogLevel, std::string sTag, std::string sMessage)
{
	LogVoice_t _logvoice;

	if (iLogLevel >= ConfiguredLogLevel)
	{
		_logvoice.Loglevel = iLogLevel;
		_logvoice.Tag = sTag;
		_logvoice.Message = sMessage;
		vTaskEnterCritical(&m_mux);
			m_Messages[m_iPushPosition] = _logvoice;
			m_iPushPosition = (m_iPushPosition + 1) % LOG_BUFFER_SIZE;
		vTaskExitCritical(&m_mux);
	}

}

