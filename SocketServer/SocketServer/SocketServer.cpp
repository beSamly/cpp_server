#include "SocketServer.h"
#include "pch.h"
#include <functional>
#include "ClientSession.h"

bool SocketServer::Start()
{
	if (StartAccept() == false)
		return false;
	Log->Info("Server started");
	return true;
}

void SocketServer::Close()
{
	// TODO
	CloseSocket();
}

void SocketServer::AddSession(SessionRef session)
{
	WRITE_LOCK;
	_sessionCount++;
	_sessions.insert(session);
}

void SocketServer::ReleaseSession(SessionRef session)
{
	WRITE_LOCK;
	ASSERT_CRASH(_sessions.erase(session) != 0);
	_sessionCount--;
}

/*---------------------
	 �������̽� ����
----------------------*/
SessionRef SocketServer::CreateSession()
{
	auto session = MakeShared<ClientSession>();
	
	session->SetOwner(std::static_pointer_cast<BaseSocketServer>(shared_from_this()));

	if (_iocpCore->Register(session) == false)
		return nullptr;

	return std::static_pointer_cast<Session>(session);
}

// BaseSocketServer���� ProcessAccept() ȣ�� �ÿ� �̺�Ʈ �߻�
void SocketServer::OnConnected(SessionRef session)
{
	Log->Info("Session connected");
	AddSession(session);
}

// Session ���� ProcessDisconnect() ȣ�� �ÿ� �̺�Ʈ �߻�
void SocketServer::OnDisconnected(SessionRef session)
{
	Log->Info("Session disconnected");
	ReleaseSession(session);
}