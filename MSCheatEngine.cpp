#include "MSCheatEngine.h"

MSCheatEngine::MSCheatEngine(MinesweeperBoard& _board) : board(_board) {
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
		std::cout << "Unable to use led matrix, falling back to normal mode, press any key to continue" << std::endl;
		_getch();
		return;
	}

	if (!SetCommState(serialDevice, &serialSettings)) {
		std::cout << "Unable to use led matrix, falling back to normal mode, press any key to continue" << std::endl;
		CloseHandle(serialDevice);
		_getch();
		return;
	}

	serialVersion = true;
}

void MSCheatEngine::sendCommandToFramework(byte _commandId, byte* _payload, size_t _payloadLength) {
	size_t size = _payloadLength + 3; //Two header bytes + command code
	byte* payload = new byte[size];
	payload[0] = 0x32;
	payload[1] = 0xAC;
	payload[2] = _commandId;
	memcpy(payload + 3, _payload, _payloadLength);
	WriteFile(serialDevice, payload, size, NULL, NULL);
	delete[] payload;
}

void MSCheatEngine::clearScreen() {
	byte blankScreen [39];
	memset(blankScreen, 0x00, sizeof(blankScreen));
	sendCommandToFramework(0x06, blankScreen, sizeof(blankScreen));
}

void MSCheatEngine::showMine() {
	byte blankScreen[39];
	memset(blankScreen, 0xF0, sizeof(blankScreen));
	sendCommandToFramework(0x06, blankScreen, sizeof(blankScreen));
}

void MSCheatEngine::spyOnTile(int _row, int _col) {
	if (enabled) {
		bool hasMine = board.board[_row][_col].hasMine;
		if (serialVersion) {
			if (hasMine) {
				showMine();
			}
			else {
				clearScreen();
			}
		}
		else {
			if (hasMine) {
				std::cout << "\x1b[0 q";
			}
			else {
				std::cout << "\x1b[1 q";
			}
		}
	}
}