#pragma once
#include <functional>
#include "BaseSocketServer.h"

using SessionFactory = std::function<SessionRef(void)>;

class SocketServer : public BaseSocketServer
{
public:
	Set<SessionRef>		_sessions;

private:
	USE_LOCK
	SessionFactory		_sessionFactory;
	int32				_sessionCount = 0;

public:
	SocketServer(NetAddress netAddress, int32 maxSessionCount) : BaseSocketServer(maxSessionCount, netAddress) {
	};

public:
	bool	Start();
	void	Close();
	void	AddSession(SessionRef session);
	void	ReleaseSession(SessionRef session);
protected:
	// �������̽� ����
	SessionRef CreateSession() override;
	void OnConnected(SessionRef session) override;
	void OnDisconnected(SessionRef session) override;
};


 