#pragma once
#include <format>;
#include <functional>;
#include <vector>;

#ifdef _DEBUG
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#pragma comment(lib, "ServerCoreLibrary\\Debug\\ServerCoreLibrary.lib")
#pragma comment(lib, "SharedProtobuf\\Debug\\SharedProtobuf.lib")
#else
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#pragma comment(lib, "ServerCoreLibrary\\Release\\ServerCoreLibrary.lib")
#pragma comment(lib, "SharedProtobuf\\Release\\SharedProtobuf.lib")
#endif

#include "GlobalVar.h"
#include "GlobalPch.h"
#include "SocketClient.h"
#include "ServerSession.h"

using std::format;
using SocketClientRef = std::shared_ptr<class SocketClient>;
using ServerSessionRef = std::shared_ptr<class ServerSession>;