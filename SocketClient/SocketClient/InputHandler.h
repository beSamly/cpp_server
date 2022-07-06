#pragma once
#include "SocketClient.h";

class InputHandler
{
public:
	std::vector<std::function<void(SocketClientRef)>> _inputHandlers = std::vector<std::function<void(SocketClientRef)>>(UINT16_MAX, nullptr);;
	void Init();
	void HandleInput(SocketClientRef session, int32 key);
};

