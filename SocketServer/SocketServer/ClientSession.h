#pragma once
#include "Session.h"

/*-----------------
	ClientSession
------------------*/
class Player;
using PlayerRef = std::shared_ptr<Player>;

class ClientSession : public Session
{
public:
	ClientSession();
	virtual ~ClientSession();
	std::shared_ptr<ClientSession> GetClientSessionRef();

public:
	PlayerRef _player = nullptr;
public:
	PlayerRef		GetPlayer();
	void			SetPlayer(PlayerRef player);
private:
	/* 인터페이스 구현 */
	virtual void	OnConnected() override;
	virtual void	OnDisconnected() override;
	virtual void	OnSend(int32 len) override;
	virtual int32	OnRecv(BYTE* buffer, int32 len) override;

private:
	void			OnRecvPacket(BYTE* buffer, int32 len);

};
