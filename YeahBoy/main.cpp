#include "YeahBoy.h"

int main(int argc, char* argv[])
{
	YeahBoy yeahBoy = YeahBoy();
	yeahBoy.InsertCartridge("example");
	yeahBoy.Start();
	return 0;
}