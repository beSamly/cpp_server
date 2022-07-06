#include "pch.h"
#include <iostream>
#include "SocketServer.h"
#include "SendBuffer.h"
#include "ThreadManager.h"

// TODO 설정 값들 하드코딩 말고 Config 파일에서 읽어오도록 수정
int32 WORKER_TICK = 64;
int32 NETWORK_TIME_OUT_MS = 1000;
int32 MAX_WORKER_THREAD = 10;
int32 PORT = 7777;
int32 MAX_SESSION_COUNT = 100;

int main() {
	SocketServerRef socketServer = MakeShared<SocketServer>(NetAddress(L"127.0.0.1", PORT), MAX_SESSION_COUNT);
	socketServer->Start();

	for (int32 i = 0; i < MAX_WORKER_THREAD; i++)
	{
		GThreadManager->Launch([&socketServer]()
		{
			while (true)
			{
				LEndTickCount = ::GetTickCount64() + WORKER_TICK;

				// 네트워크 입출력 및 패킷 핸들러 실행
				socketServer->GetIocpCore()->HandleIocpEvent(NETWORK_TIME_OUT_MS);

				// Global Queue 의 일감 실행
				//ThreadManager::DoGlobalQueueWork();

				// JobTimer Queue 의 일감 실행 : 시간 예약 혹은 인터벌 일감
				ThreadManager::DistributeReservedJobs();
			}
		});
	}

	GThreadManager->Join();

	return 0;
}