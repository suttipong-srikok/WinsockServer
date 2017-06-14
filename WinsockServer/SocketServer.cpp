//+------------------------------------------------------------------+
//| Definition of SocketServer Class's Methods                       |
//+------------------------------------------------------------------+
#include "SocketServer.h"

// PRIVATE
void SocketServer::InitializeWinsock()
{
	int i = 0;
	while (1)
	{
		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0)
		{
			i++;
			// printf("WSAStartup failed with error: %d\n", iResult);
			printf("Initialize Winsock failed with error: %d\n", iResult);

			if (i == 1000)
			{
				i = 0;
				Sleep(3000);
			}
		}
		else
			break;
	}
}

void SocketServer::AddrInfoMalloc()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
}

void SocketServer::ResolveAddrInfo()
{
	int i = 0;
	while (1)
	{
		// Resolve the server address and port
		iResult = getaddrinfo(NULL, _port, &hints, &result);
		if (iResult != 0)
		{
			i++;
			printf("getaddrinfo failed with error: %d\n", iResult);

			if (i == 1000)
			{
				WSACleanup();
				freeaddrinfo(result);

				i = 0;
				Sleep(3000);
				InitializeWinsock();
			}
		}
		else
			break;
	}
}

void SocketServer::CreateListenSocket()
{
	int i = 0;
	while (1)
	{
		// Create a SOCKET for connecting to server
		ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ListenSocket == INVALID_SOCKET)
		{
			i++;
			printf("socket failed with error: %ld\n", WSAGetLastError());

			if (i == 1000)
			{
				freeaddrinfo(result);
				WSACleanup();

				i = 0;
				Sleep(3000);
				InitializeWinsock();
				ResolveAddrInfo();
			}
		}
		else
			break;
	}
}

void SocketServer::SetupListenSocket()
{
	int i = 0;
	while (1)
	{
		// Setup the TCP listening socket
		iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			i++;
			printf("bind failed with error: %d\n", WSAGetLastError());

			if (i == 1000)
			{
				freeaddrinfo(result);
				closesocket(ListenSocket);
				WSACleanup();

				i = 0;
				Sleep(3000);
				InitializeWinsock();
				ResolveAddrInfo();
				CreateListenSocket();
			}
		}
		else
			break;
	}
	freeaddrinfo(result);
}

void SocketServer::ListenForRequest()
{
	int i = 0;
	while (1)
	{
		iResult = listen(ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR)
		{
			i++;
			printf("listen failed with error: %d\n", WSAGetLastError());

			if (i == 1000)
			{
				closesocket(ListenSocket);
				WSACleanup();

				i = 0;
				Sleep(3000);
				InitializeWinsock();
				ResolveAddrInfo();
				CreateListenSocket();
				SetupListenSocket();
			}
		}
		else
			break;
	}
}

void SocketServer::SetConfig(const char *config_file)
{
	Utilities *util = new Utilities();
	util->ReadConfig(config_file, "port", _port);
	delete util;
}

// PUBLIC
SocketServer::SocketServer(const char *config_file)
{
	SetConfig(config_file);

	InitializeWinsock();
	AddrInfoMalloc();
	ResolveAddrInfo();
	CreateListenSocket();
	SetupListenSocket();
	ListenForRequest();
}

SocketServer::~SocketServer()
{
	closesocket(ListenSocket);
	closesocket(ClientSocket);
	WSACleanup();
}

void SocketServer::RunServer()
{
	while (1)
	{
		printf("Listening...\n");

		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("accept failed with error: %d\n", WSAGetLastError());
			continue;
		}

		printf("Accept connection from client.\n");

		// Receive until the peer shuts down the connection
		do
		{
			iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0)
			{
				printf("Bytes received: %d\n", iResult);

				recvbuf[iResult] = '\0';
				printf("Request message from client: %s\n", recvbuf);

				char respMsg[] = "Server got your message";

				// Echo the buffer back to the sender
				iSendResult = send(ClientSocket, respMsg, strlen(respMsg), 0);
				if (iSendResult == SOCKET_ERROR)
				{
					printf("send failed with error: %d\n", WSAGetLastError());
					continue;
				}

				printf("Bytes sent: %d\n", iSendResult);
			}
			else
				printf("Client close connection.");

		} while (iResult > 0);

		printf("\n\n");
	}
}
