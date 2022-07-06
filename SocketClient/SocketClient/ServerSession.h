#pragma once
#include "Session.h"

class ServerSession : public Session
{
public:
	ServerSession();
	virtual ~ServerSession();
	std::shared_ptr<ServerSession> GetSessionRef();

private:
	/* 인터페이스 구현 */
	virtual void	OnConnected() override;
	virtual void	OnDisconnected() override;
	virtual void	OnSend(int32 len) override;
	virtual int32	OnRecv(BYTE* buffer, int32 len) override;

private:
	void				OnRecvPacket(BYTE* buffer, int32 len);
};

