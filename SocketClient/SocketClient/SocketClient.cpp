#include "pch.h"
#include "SocketClient.h"
#include "Session.h"
#include "ServerSession.h"
#include "SocketUtils.h"

SessionRef SocketClient::CreateSession()
{
	auto session = MakeShared<ServerSession>();

	session->SetOwner(std::static_pointer_cast<BaseSocketServer>(shared_from_this()));

	if (_iocpCore->Register(session) == false)
		return nullptr;

	return std::static_pointer_cast<Session>(session);
}

bool SocketClient::Start()
{
	SocketUtils::Init();
	for (int32 i = 0; i < _maxSessionCount; i++)
	{
		SessionRef session = CreateSession();
		session->SetNetAddress(_netAddress);
		if (session->Connect() == false)
			return false;

		if (i == 0) {
			_serverSession = session;
		}
	}

	return true;
}

void SocketClient::OnConnected(SessionRef session)
{
}

void SocketClient::OnDisconnected(SessionRef session)
{
}
