#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
// #define DEFAULT_PORT "27015"

class SocketServer
{
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;
	int iResult, iSendResult;
	char recvbuf[DEFAULT_BUFLEN],
		_port[10], _totalthreads[10], _sleepthreads[20], _logfile[100];
	int recvbuflen = DEFAULT_BUFLEN;
	struct addrinfo *result = NULL,
		hints;
	void InitializeWinsock();
	void AddrInfoMalloc();
	void ResolveAddrInfo();
	void CreateListenSocket();
	void SetupListenSocket();
	void ListenForRequest();
	void SetConfig(const char*);
public:
	SocketServer(const char *config_file);
	~SocketServer();
	void RunServer();
};

class Utilities
{
public:
	void CharArrayMAlloc(char *arr[], int size, int max_length);
	void SplitString(char *str, char dem, char *arr[], int size, int max_length);
	void Trim(char*);
	void LowerString(char*);
	void ReadConfig(const char *file_name, char *config_name, char *config_value);
};

