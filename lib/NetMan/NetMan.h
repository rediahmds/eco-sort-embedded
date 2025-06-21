#ifndef NETMAN_H
#define NETMAN_H

#include <NetWizard.h>
#include <WebServer.h>
#include <Lcd.h>

#define DEFAULT_AP_NAME "EcoSort AP"
#define DEFAULT_AP_PASSWORD ""

enum class WiFiMode
{
    MANUAL,
    AUTO
};

class NetMan : public NetWizard
{
public:
    NetMan(String ssid, String password, LCD &lcd);
    NetMan(WebServer *server, String APname, String APpassword, LCD &lcd);

    void begin();

private:
    const WiFiMode _mode;
    String _ssid;
    String _password;
    WebServer *_server;
    LCD &_lcd;

    void _connectionStatusCallback(NetWizardConnectionStatus status);
};

#endif