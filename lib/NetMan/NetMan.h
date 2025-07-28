#ifndef NETMAN_H
#define NETMAN_H

#include <NetWizard.h>
#include <WebServer.h>
#include <Lcd.h>

#define DEFAULT_AP_NAME "EcoSort AP"
#define DEFAULT_AP_PASSWORD ""

class NetMan
{
public:
    static void handleConnectionChanges(NetWizardConnectionStatus status, LCD &lcd, int delayms = 500);
    static void handlePortalChanges(NetWizardPortalState state, LCD &lcd, int delayms = 500);

    NetMan();
};

#endif