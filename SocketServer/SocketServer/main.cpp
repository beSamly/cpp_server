#include "pch.h"
#include <iostream>
#include "SocketServer.h"
#include "SendBuffer.h"
#include "ThreadManager.h"

int32 WORKER_TICK = 64;

int main() {
	SocketServerRef socketServer = MakeShared<SocketServer>(NetAddress(L"127.0.0.1", 7777), 100);
	//SocketServer* socketServer = new SocketServer(NetAddress(L"127.0.0.1", 7777), 100);
	socketServer->Start();

	for (int32 i = 0; i < 10; i++)
	{
		GThreadManager->Launch([&socketServer]()
		{
			while (true)
			{
				LEndTickCount = ::GetTickCount64() + WORKER_TICK;

				// 네트워크 입출력 처리 -> 인게임 로직까지 (패킷 핸들러에 의해)
				socketServer->GetIocpCore()->HandleIocpEvent(2);

				// 글로벌 큐
				ThreadManager::DoGlobalQueueWork();

				//Timer
				ThreadManager::DistributeReservedJobs();
			}
		});
	}

	GThreadManager->Join();

	//// Main Thread
	//DoWorkerJob(service);

	return 0;
}