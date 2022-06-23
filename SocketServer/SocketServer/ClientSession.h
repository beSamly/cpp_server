#pragma once

#include "Session.h"
/*-----------------
	ClientSession
------------------*/

class ClientSession : public Session
{
public:
	ClientSession();
	virtual ~ClientSession();
	std::shared_ptr<ClientSession> GetClientSessionRef() { return static_pointer_cast<ClientSession>(shared_from_this()); }

private:
	/* 인터페이스 구현 */
	virtual void	OnConnected() override;
	virtual void	OnDisconnected() override;
	virtual void	OnSend(int32 len) override;
	virtual int32	OnRecv(BYTE* buffer, int32 len) override;

private:
	void			OnRecvPacket(BYTE* buffer, int32 len);
};
