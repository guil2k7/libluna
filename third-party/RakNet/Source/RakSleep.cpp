#include <unistd.h> // usleep
#include "RakSleep.h"

using namespace RakNet;

void RakNet::RakSleep(unsigned int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}
