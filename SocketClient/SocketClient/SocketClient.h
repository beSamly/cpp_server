#pragma once
#include "BaseSocketServer.h"

class SocketClient : public BaseSocketServer
{
public:
	SocketClient(NetAddress netAddress, int32 maxSessionCount) : BaseSocketServer(maxSessionCount, netAddress) {
	};
	virtual ~SocketClient() {}

	SessionRef CreateSession() override;

	bool Start();

	void OnConnected(SessionRef session) override;

	void OnDisconnected(SessionRef session) override;
};
