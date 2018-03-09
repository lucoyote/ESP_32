/*
 * WiFi.h
 *
 *  Created on: Feb 25, 2017
 *      Author: kolban
 */

#ifndef MAIN_WIFI_H_
#define MAIN_WIFI_H_
#include "sdkconfig.h"

#include <string>
#include <vector>
#include <mdns.h>
#include <esp_err.h>
#include "FreeRTOS.h"
#include "WiFiEventHandler.h"
#include "WiFiAPRecord.h"

/**
 * @brief %WiFi driver.
 *
 * Encapsulate control of %WiFi functions.
 *
 * Here is an example fragment that illustrates connecting to an access point.
 * @code{.cpp}
 * #include <WiFi.h>
 * #include <WiFiEventHandler.h>
 *
 * class TargetWiFiEventHandler: public WiFiEventHandler {
 *    esp_err_t staGotIp(system_event_sta_got_ip_t event_sta_got_ip) {
 *       ESP_LOGD(tag, "MyWiFiEventHandler(Class): staGotIp");
 *       // Do something ...
 *       return ESP_OK;
 *    }
 * };
 *
 * WiFi wifi;
 *
 * TargetWiFiEventHandler *eventHandler = new TargetWiFiEventHandler();
 * wifi.setWifiEventHandler(eventHandler);
 * wifi.connectAP("myssid", "mypassword");
 * @endcode
 */
class WiFi
{
private:
		static esp_err_t    eventHandler(void* ctx, system_event_t* event);
		void                init();
    uint32_t            ip;
    uint32_t            gw;
    uint32_t            netmask;
    WiFiEventHandler*   m_pWifiEventHandler;
    uint8_t             m_dnsCount=0;
    bool                m_eventLoopStarted;
    bool                m_initCalled;
    bool                m_apConnected;   // Are we connected to an access point?
  	FreeRTOS::Semaphore m_connectFinished = FreeRTOS::Semaphore("ConnectFinished");

public:
    WiFi();
    ~WiFi();
    void                      addDNSServer(const std::string& ip);
    void                      addDNSServer(const char* ip);
    void                      addDNSServer(ip_addr_t ip);
    void                      setDNSServer(int numdns, const std::string& ip);
    void                      setDNSServer(int numdns, const char* ip);
    void                      setDNSServer(int numdns, ip_addr_t ip);
    struct in_addr            getHostByName(const std::string& hostName);
    struct in_addr            getHostByName(const char* hostName);
    bool                      connectAP(const std::string& ssid, const std::string& password, bool waitForConnection=true);
    void                      dump();
    bool                      isConnectedToAP();
    static std::string        getApMac();
    static tcpip_adapter_ip_info_t getApIpInfo();
    static std::string        getApSSID();
	static std::string        getApIp();
	static std::string        getApNetmask();
	static std::string        getApGateway();
    static std::string        getMode();
    static tcpip_adapter_ip_info_t getStaIpInfo();
    static std::string        getStaMac();
    static std::string        getStaSSID();
	static std::string        getStaIp();
	static std::string        getStaNetmask();
	static std::string        getStaGateway();
    std::vector<WiFiAPRecord> scan();
    void                      startAP(const std::string& ssid, const std::string& passwd, wifi_auth_mode_t auth = WIFI_AUTH_OPEN);
    void                      startAP(const std::string& ssid, const std::string& passwd, wifi_auth_mode_t auth, uint8_t channel, bool ssid_hidden, uint8_t max_connection);
    void                      setIPInfo(const std::string& ip, const std::string& gw, const std::string& netmask);
    void                      setIPInfo(const char* ip, const char* gw, const char* netmask);
    void                      setIPInfo(uint32_t ip, uint32_t gw, uint32_t netmask);
    void                      setWifiEventHandler(WiFiEventHandler *wifiEventHandler);
};

#endif /* MAIN_WIFI_H_ */
