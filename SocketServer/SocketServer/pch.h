#pragma once
#include <memory>
#include <string>
#include <format>
#include <functional>
#include <concepts>
#include <regex>
#include <iostream>

#ifdef _DEBUG
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#pragma comment(lib, "ServerCoreLibrary\\Debug\\ServerCoreLibrary.lib")
#pragma comment(lib, "SharedProtobuf\\Debug\\SharedProtobuf.lib")
#else
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#pragma comment(lib, "ServerCoreLibrary\\Release\\ServerCoreLibrary.lib")
#pragma comment(lib, "ServerCoreLibrary\\Release\\SharedProtobuf.lib")
#endif

#include "TLS.h"
#include "GlobalVar.h"
#include "GlobalPch.h"
#include "ClientSession.h"
#include "SocketServer.h"
#include "Logger.h"
#include "ColumnInfo.h"
#include "Collection.h"

using std::shared_ptr;
using std::function;
using std::vector;
using SocketServerRef = std::shared_ptr<class SocketServer>;
using ClientSessionRef = std::shared_ptr<class ClientSession>;
using ColumnInfoRef = std::shared_ptr<class ColumnInfo>;
using JobQueueRef = std::shared_ptr<class JobQueue>;
using JobRef = std::shared_ptr<class Job>;
using JobDataRef = std::shared_ptr<class JobData>;
using CallbackType = std::function<void()>;

template<typename T>
using CollectionRef = std::shared_ptr<class Collection<T>>;
using EquipItemRef = std::shared_ptr<class EquipItem>;

using PlayerRef = std::shared_ptr<class Player>;
using AccountRef = std::shared_ptr<class Account>;
using DBConnectionGaurdRef = std::shared_ptr<class DBConnectionGaurd>;

