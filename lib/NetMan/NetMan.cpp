#include "NetMan.h"

void NetMan::handleConnectionChanges(NetWizardConnectionStatus status, LCD &lcd, int delayms)
{
	switch (status)
	{
	case NetWizardConnectionStatus::DISCONNECTED:
		lcd.clearRow(0);
		lcd.clearRow(1);

		lcd.printCentered(0, "Koneksi WiFi");
		lcd.printCentered(1, "terputus.");
		break;

	case NetWizardConnectionStatus::CONNECTING:
		lcd.clearRow(0);
		lcd.clearRow(1);

		lcd.printCentered(0, "WiFi sedang");
		lcd.printCentered(1, "menghubungkan.");
		break;

	case NetWizardConnectionStatus::CONNECTED:
		lcd.clearRow(0);
		lcd.clearRow(1);

		lcd.printCentered(0, "WiFi berhasil");
		lcd.printCentered(1, "terhubung.");
		break;

	case NetWizardConnectionStatus::CONNECTION_FAILED:
		lcd.clearRow(0);
		lcd.clearRow(1);

		lcd.printCentered(0, "Koneksi WiFi gagal.");
		break;

	case NetWizardConnectionStatus::CONNECTION_LOST:
		lcd.clearRow(0);
		lcd.clearRow(1);

		lcd.printCentered(0, "Koneksi WiFi hilang.");
		break;

	case NetWizardConnectionStatus::NOT_FOUND:
	default:
		lcd.clearRow(0);
		lcd.clearRow(1);

		lcd.printCentered(0, "Koneksi WiFi");
		lcd.printCentered(1, "tak ditemukan.");
		break;
	}

	delay(delayms);
}

void NetMan::handlePortalChanges(NetWizardPortalState state, LCD &lcd, int delayms)
{
	switch (state)
	{
	case NetWizardPortalState::IDLE:
		lcd.clearRow(2);
		lcd.clearRow(3);

		lcd.printCentered(2, "Web Portal siap");
		lcd.printCentered(3, "untuk dimulai.");
		break;

	case NetWizardPortalState::CONNECTING_WIFI:
		lcd.clearRow(2);
		lcd.clearRow(3);

		lcd.printCentered(2, "Web Portal mencoba");
		lcd.printCentered(3, "terhubung ke WiFi.");
		break;

	case NetWizardPortalState::WAITING_FOR_CONNECTION:
		lcd.clearRow(2);
		lcd.clearRow(3);

		lcd.printCentered(2, "Web Portal menunggu");
		lcd.printCentered(3, "koneksi client.");
		break;

	case NetWizardPortalState::SUCCESS:
		lcd.clearRow(2);
		lcd.clearRow(3);

		lcd.printCentered(2, "Web Portal-client");
		lcd.printCentered(3, "berhasil terhubung.");
		break;

	case NetWizardPortalState::FAILED:
		lcd.clearRow(2);
		lcd.clearRow(3);

		lcd.printCentered(2, "Web Portal-client");
		lcd.printCentered(3, "gagal terhubung.");
		break;

	case NetWizardPortalState::TIMEOUT:
	default:
		lcd.clearRow(2);
		lcd.clearRow(3);

		lcd.printCentered(2, "Web Portal mencapai");
		lcd.printCentered(3, "batas waktu.");
		break;
	}

	delay(delayms);
}
