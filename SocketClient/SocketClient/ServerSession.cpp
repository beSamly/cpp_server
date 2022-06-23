#include "pch.h"
#include "ServerSession.h"
#include "Logger.h"

ServerSession::ServerSession()
{

}

ServerSession::~ServerSession()
{

}

void ServerSession::OnConnected()
{

}

void ServerSession::OnDisconnected()
{

}

void ServerSession::OnSend(int32 len)
{

}

int32 ServerSession::OnRecv(BYTE* buffer, int32 len)
{
	Log->Info("Recv packet");
	return 10;
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{

}
