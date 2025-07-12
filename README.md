# WinsockServer

A Windows Winsock-based TCP server implementation in C++.

## Overview

This project implements a basic TCP server using the Windows Winsock API. The server is designed to listen for client connections on a configurable port and handle incoming requests.

## Project Structure

```
WinsockServer/
├── WinsockServer.sln          # Visual Studio solution file
└── WinsockServer/
    ├── SocketServer.h         # Main server class header
    ├── SocketServer.cpp       # Server implementation
    ├── Utilities.cpp          # Utility functions
    ├── winsock_server.cpp     # Main entry point
    ├── severconfig.ini        # Server configuration
    └── *.vcxproj             # Visual Studio project files
```

## Features

- **TCP Server**: Implements a Winsock-based TCP server
- **Configuration File**: Server settings loaded from `severconfig.ini`
- **Error Handling**: Robust error handling with retry mechanisms
- **Utilities**: Helper functions for string manipulation and configuration parsing

## Configuration

The server uses `severconfig.ini` for configuration:

```ini
port=27015
```

## Building

This project requires:
- Windows operating system
- Visual Studio with C++ support
- Winsock2 library (included with Windows)

Open `WinsockServer.sln` in Visual Studio and build the solution.

## Usage

1. Configure the server port in `severconfig.ini`
2. Build and run the executable
3. The server will start listening on the configured port

## Dependencies

- Windows Winsock2 API
- Standard C++ libraries
- Ws2_32.lib (automatically linked)

## Classes

### SocketServer
Main server class that handles:
- Winsock initialization
- Socket creation and binding
- Listening for connections
- Client request handling

### Utilities
Helper class providing:
- String manipulation functions
- Configuration file parsing
- Memory management utilities

## License

This project appears to be based on Microsoft's Winsock server examples and is intended for educational purposes.
