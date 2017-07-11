
#include <U8g2lib.h>
#include "main.h"

U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 13, 11, 10, 9, 8);  // D0=13, D1=11, CS=10, DC=9, Reset=8

// Global variables
int g_nPacketLength = 0;
char g_szDataPacket[PACKET_MAX_SIZE];
String g_strCPUTemp = "0.00";
String g_strGPUTemp = "0.00";
String g_strFPS = "0.00";
boolean g_bPacketReceived = false;

void setup(void) {
	u8g2.begin();

	// Start the serial port
	Serial.begin(115200);

	int start = millis();
	while (!Serial){
		// Timeout if no COM is detected for 5 seconds
		if (millis() - start >= 5000) {
			break;
		}
	};

	// Reserve some memory
	g_strCPUTemp.reserve(6);
	g_strGPUTemp.reserve(6);
	g_strFPS.reserve(6);
}


void loop(void) {
	// Type of the current packet part
	int nType = 0;

	// If the packet is received, do some stuff 
	if (g_bPacketReceived) {
		//Serial.println(dataPacket);
		g_bPacketReceived = false;

		// Parse the packet
		char* szPart = strtok(g_szDataPacket, ";");
		while (szPart != 0)
		{
			switch (nType) {
			case PACK_CPU:
				g_strCPUTemp = szPart;
				break;
			case PACK_GPU:
				g_strGPUTemp = szPart;
				break;
			case PACK_FPS:
				g_strFPS = szPart;
				break;
			}

			nType++;
			// Find the next part
			szPart = strtok(0, ";");
		}

		// Reset
		memset(g_szDataPacket, 0, sizeof(g_szDataPacket));
	}

	// Display the data
	u8g2.firstPage();
	do {
		u8g2.setFont(u8g2_font_courR10_tf);
		u8g2.drawStr(0, 10, "CPU: ");
		u8g2.drawStr(38, 10, g_strCPUTemp.c_str());

		u8g2.drawStr(0, 25, "GPU: ");
		u8g2.drawStr(38, 25, g_strGPUTemp.c_str());

		u8g2.drawStr(0, 40, "FPS: ");
		u8g2.drawStr(30, 40, "              ");
		u8g2.drawStr(38, 40, g_strFPS.c_str());

		// Test for gloriousness
		if (g_strFPS.length() > 0 && atoi(g_strFPS.c_str()) >= GLORIOUS_FPS) {
			u8g2.drawXBMP(76, 0, 50, 29, kuiSuperSecretBitmap);
		}
	} while (u8g2.nextPage());
}

/**
 * Only read from the serial port when there's something to read
 */
void serialEvent() {
	g_nPacketLength = 0;
	while (Serial.available()) {
		// Read a byte
		char cCurrentByte = (char)Serial.read();

		// The packet ends with "$" => no more reading
		if (cCurrentByte == '$') {
			g_bPacketReceived = true;
			break;
		}

		// Save the current byte in the packet buffer
		if (g_nPacketLength < PACKET_MAX_SIZE) {
			g_szDataPacket[g_nPacketLength++] = cCurrentByte;
		}
	}
}