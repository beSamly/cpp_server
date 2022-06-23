#pragma once
#include <memory>

#ifdef _DEBUG
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#pragma comment(lib, "ServerCoreLibrary\\Debug\\ServerCoreLibrary.lib")
#pragma comment(lib, "SharedProtobuf\\Debug\\SharedProtobuf.lib")
#else
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#pragma comment(lib, "ServerCoreLibrary\\Release\\ServerCoreLibrary.lib")
#pragma comment(lib, "ServerCoreLibrary\\Release\\SharedProtobuf.lib")
#endif

#include "GlobalVar.h"
#include "GlobalPch.h"
#include "ClientSession.h"
#include "SocketServer.h"
#include "Logger.h"

using SocketServerRef = std::shared_ptr<class SocketServer>;
using ClientSessionRef = std::shared_ptr<class ClientSession>;
