#include "MSCheatEngine.h"

MSCheatEngine::MSCheatEngine() {
	serialVersion = false;
	enabled = false;

	serialDevice = NULL; //We dont have a serial device yet

	//Setting up serial connection parameters
	serialSettings.DCBlength = sizeof(serialSettings);
	serialSettings.BaudRate = CBR_115200;
	serialSettings.fParity = false; //Disable parity check
	serialSettings.ByteSize = 8;
	serialSettings.Parity = NOPARITY;
	serialSettings.StopBits = ONESTOPBIT;
	
	//Disable any flow control
	serialSettings.fOutxCtsFlow = false;
	serialSettings.fOutxDsrFlow = false;
	serialSettings.fDtrControl = DTR_CONTROL_DISABLE;
	serialSettings.fDsrSensitivity = false;
	serialSettings.fOutX = false;
	serialSettings.fInX = false;
	serialSettings.fRtsControl = RTS_CONTROL_DISABLE;
}

MSCheatEngine::~MSCheatEngine() {
	if (serialVersion) {
		CloseHandle(serialDevice);
	}
}

void MSCheatEngine::enableStandardMode() {
	enabled = true;
}

void MSCheatEngine::enableFrameworkMode() {
	if (enabled) { // only once at startup
		return;
	}
	enabled = true;
	
	serialDevice = CreateFile(L"\\\\.\\COM3",GENERIC_WRITE,0,NULL,OPEN_EXISTING,/*FILE_FLAG_OVERLAPPED*/FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (serialDevice == INVALID_HANDLE_VALUE) {
		std::cout << "Unable to use led matrix, falling back to normal mode" << std::endl;
		return;
	}

	if (!SetCommState(serialDevice, &serialSettings)) {
		std::cout << "Unable to use led matrix, falling back to normal mode" << std::endl;
		CloseHandle(serialDevice);
		return;
	}

	serialVersion = true;
}

