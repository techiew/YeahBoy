#pragma once
#include <string>

#define PrintDebugMsg(msg, type)

class DebugConsole
{
private:

public:
	DebugConsole();
	void PrintToConsole(std::string msg, int type);
	~DebugConsole();
};