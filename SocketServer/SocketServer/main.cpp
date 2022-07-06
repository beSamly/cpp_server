#include "pch.h"
#include <iostream>
#include "SocketServer.h"
#include "SendBuffer.h"
#include "ThreadManager.h"

// TODO ���� ���� �ϵ��ڵ� ���� Config ���Ͽ��� �о������ ����
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

				// ��Ʈ��ũ ����� �� ��Ŷ �ڵ鷯 ����
				socketServer->GetIocpCore()->HandleIocpEvent(NETWORK_TIME_OUT_MS);

				// Global Queue �� �ϰ� ����
				//ThreadManager::DoGlobalQueueWork();

				// JobTimer Queue �� �ϰ� ���� : �ð� ���� Ȥ�� ���͹� �ϰ�
				ThreadManager::DistributeReservedJobs();
			}
		});
	}

	GThreadManager->Join();

	return 0;
}