#pragma once
#include <memory>

#ifdef _DEBUG
#pragma comment(lib, "ServerCoreLibrary\\Debug\\ServerCoreLibrary.lib")
#else
#pragma comment(lib, "ServerCoreLibrary\\Release\\ServerCoreLibrary.lib")
#endif

#include "GlobalPch.h"
#include "ClientSession.h"
#include "SocketServer.h"

using SocketServerRef = std::shared_ptr<class SocketServer>;
using ClientSessionRef = std::shared_ptr<class ClientSession>;