#pragma once
#include <windows.h>
#include <iostream>
#include <memory>
#include <conio.h>
#include <functional>
#include "MinesweeperBoard.h"

class MSCheatEngine
{
	public:
		MSCheatEngine(MinesweeperBoard& _board);
		~MSCheatEngine();
		void enableStandardMode();
		void enableFrameworkMode();
		void spyOnTile(int _row, int _col);
		void addHintFunctions(std::function<void()> _hintMine, std::function<void()> _hintNoMine);
	private:
		HANDLE serialDevice;
		DCB serialSettings;
		bool serialVersion;
		bool enabled;
		MinesweeperBoard& board;
		
		//Framework mode
		void sendCommandToFramework(byte _commandId, byte* _payload, size_t _payloadLength);
		void showMine();
		void clearScreen();

		//Normal mode
		std::function<void()> hintMine = []() {};
		std::function<void()> hintNoMine = []() {};
};

