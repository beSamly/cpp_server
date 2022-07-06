#include "pch.h"
#include "ServerSession.h"
#include "Logger.h"
#include "PacketHeader.h"
#include "PacketManager.h"

ServerSession::ServerSession()
{

}

ServerSession::~ServerSession()
{

}

std::shared_ptr<ServerSession> ServerSession::GetSessionRef()
{
	return static_pointer_cast<ServerSession>(shared_from_this());
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

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	auto packetId = header->id;
	auto session = this->GetSessionRef();
	GPacketManager->HandlePacket(session, packetId, buffer, len);
}
