#include <esp_log.h>
#include <string>
#include "WiFi.h"
#include <WiFiEventHandler.h>

#include "sdkconfig.h"
#include <socket.h>
#include <Task.h>
#include "UDPListenTask.h"
#include "CLogger.h"


#define SSID "Luca_Dlink"
#define PASSWORD "AlessandroMontiEmanuele"
#define IPADDRESS "192.168.1.221"
#define GATEWAY "192.168.1.1"
#define SUBNETMASK "255.255.255.0"

static char tag[] = "my tag";

extern "C"
{
	void app_main(void);
}




class MyWiFiEventHandler: public WiFiEventHandler
{

	public:
		UDPListenTask * _readTask= new UDPListenTask();


	private:

	esp_err_t staGotIp(system_event_sta_got_ip_t event_sta_got_ip)
	{

		CLogger::getInstance()->Log(ESP_LOG_INFO,tag,"MyWiFiEventHandler(Class): staGotIp");

		return ESP_OK;
	}

	esp_err_t staConnected(system_event_sta_connected_t info)
	{
		CLogger::getInstance()->Log(ESP_LOG_INFO,tag,"MyWiFiEventHandler(Class): staConnected");
		MyWiFiEventHandler::_readTask->start();
		return ESP_OK;
	}
	esp_err_t staDisconnected(system_event_sta_disconnected_t info)
	{
		CLogger::getInstance()->Log(ESP_LOG_INFO,tag,"MyWiFiEventHandler(Class): staDisconnected");
		MyWiFiEventHandler::_readTask->stop();
		return ESP_OK;
	}
};

void app_main(void)
{
	WiFi wifi;

	// Define Logger
	CLogger::getInstance()->SetLogLevel(ESP_LOG_INFO);
	CLogger::getInstance()->start(); // Start logger handler task


	MyWiFiEventHandler *eventHandler = new MyWiFiEventHandler();

	wifi.setWifiEventHandler(eventHandler);
	//wifi.setIPInfo(IPADDRESS, GATEWAY, SUBNETMASK);
	wifi.connectAP(SSID, PASSWORD);


	while(1)
	{
		vTaskDelay(60000/portTICK_PERIOD_MS);
	}
	CLogger::getInstance()->stop();
}



