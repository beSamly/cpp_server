#pragma once

#ifdef _DEBUG
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#pragma comment(lib, "ServerCoreLibrary\\Debug\\ServerCoreLibrary.lib")
#else
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#pragma comment(lib, "ServerCoreLibrary\\Release\\ServerCoreLibrary.lib")
#endif

#include "GlobalVar.h"
#include "GlobalPch.h"
#include "SocketClient.h"
#include "ServerSession.h"

using SocketClientRef = std::shared_ptr<class SocketClient>;
using ServerSessionRef = std::shared_ptr<class ServerSession>;