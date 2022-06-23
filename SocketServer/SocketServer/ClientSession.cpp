#include "ClientSession.h"
#include "pch.h"
#include "PacketManager.h"
#include "PacketHeader.h"

ClientSession::ClientSession()
{
	//TODO
}

ClientSession::~ClientSession()
{
	//TODO
}

// [size(2)][id(2)][data....][size(2)][id(2)][data....]
int32 ClientSession::OnRecv(BYTE* buffer, int32 len)
{
	int32 processLen = 0;

	while (true)
	{
		int32 dataSize = len - processLen;
		// 최소한 헤더는 파싱할 수 있어야 한다
		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
		// 헤더에 기록된 패킷 크기를 파싱할 수 있어야 한다
		if (dataSize < header.size)
			break;

		// 패킷 조립 성공
		OnRecvPacket(&buffer[processLen], header.size);

		processLen += header.size;
	}

	return processLen;
}


void ClientSession::OnConnected()
{

}

void ClientSession::OnDisconnected()
{
	/*GSessionManager.Remove(static_pointer_cast<ClientSession>(shared_from_this()));

	if (_currentPlayer)
	{
		if (auto room = _room.lock())
			room->DoAsync(&Room::Leave, _currentPlayer);
	}

	_currentPlayer = nullptr;
	_players.clear();*/
}


void ClientSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	auto packetId = header->id;
	auto session = this->GetClientSessionRef();
	GPacketManager->HandlePacket(session, packetId, buffer, len);
}

void ClientSession::OnSend(int32 len)
{
}