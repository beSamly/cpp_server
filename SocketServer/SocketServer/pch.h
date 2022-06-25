#pragma once
#include <memory>
#include <string>

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
#include "ColumnInfo.h"
#include "Collection.h"

using std::shared_ptr;
using SocketServerRef = std::shared_ptr<class SocketServer>;
using ClientSessionRef = std::shared_ptr<class ClientSession>;
using ColumnInfoRef = std::shared_ptr<class ColumnInfo>;

template<typename T>
using CollectionRef = std::shared_ptr<class Collection<T>>;
