#include "pch.h"
#include "ClientSession.h"
#include "PacketManager.h"
#include "PacketHeader.h"
#include "PacketId.h"
#include "LoginResponse.pb.h"

ClientSession::ClientSession()
{
}

ClientSession::~ClientSession()
{
}

ClientSessionRef ClientSession::GetClientSessionRef()
{
	return static_pointer_cast<ClientSession>(shared_from_this());
}

int32 ClientSession::OnRecv(BYTE* buffer, int32 len)
{
	int32 processLen = 0;

	while (true)
	{
		int32 dataSize = len - processLen;
		// ������ ����� ��� ������ ���� ���� �� ����
		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
		// ����� ��ϵ� ��Ŷ ũ�⸦ �Ľ��� �� �־�� �Ѵ�
		if (dataSize < header.size)
			break;

		// ��Ŷ ���� ����
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
	// TODO
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

PlayerRef ClientSession::GetPlayer()
{
	return _player;
}

void ClientSession::SetPlayer(PlayerRef player)
{
	_player = player;
}

void ClientSession::SendLoginResponse(Protocol::LoginResponse pkt)
{
	SendBufferRef buffer = PacketManager::PacketToSendBuffer(pkt, PacketId::LOGIN_RES);
	this->Send(buffer);
}
