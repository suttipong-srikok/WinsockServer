#include "SocketServer.h"

int __cdecl main(void)
{
	const char *config_file = "severconfig.ini";

	printf("Winsock Server START\n\n");

	SocketServer *psv = new SocketServer("severconfig.ini");
	psv->RunServer();
	delete psv;

	return 0;
}