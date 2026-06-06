#pragma once
#include <windows.h>
#include <iostream>

class MSCheatEngine
{
	public:
		MSCheatEngine();
		~MSCheatEngine();
		void enableStandardMode();
		void enableFrameworkMode();
	private:
		HANDLE serialDevice;
		DCB serialSettings;
		bool serialVersion;
		bool enabled;
};

