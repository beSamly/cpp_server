#include "pch.h"
#include "SocketClient.h"
#include "InputHandler.h"

int main() {
	SocketClientRef socketClient = MakeShared<SocketClient>(NetAddress(L"127.0.0.1", 7777), 1);
	ASSERT_CRASH(socketClient->Start());

	Vector<thread>	_threads;
	for (int32 i = 0; i < 5; i++)
	{
		_threads.push_back(thread([=]()
		{
			while (true)
			{
				socketClient->GetIocpCore()->HandleIocpEvent();
			}
		}));
	}

	_threads.push_back(thread([=]()
	{
		while (true)
		{
			int keyPressed;
			cout << "Pleas choose option" << endl;
			cout << "[1] Login" << endl;
			cout << "[2] Buy EquipItem" << endl;
			cout << "[3] Break EquipItem" << endl;
			cout << "[4] Upgrade EquipItem" << endl;
			std::cin >> keyPressed;
			GInputHandler->HandleInput(socketClient, keyPressed);
			cout << "Key pressed is " << keyPressed << endl;;
		}
	}));

	for (thread& t : _threads)
	{
		if (t.joinable())
			t.join();
	}

	return 0;
}