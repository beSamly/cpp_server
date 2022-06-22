#include "ClientSession.h"
#include "pch.h"

ClientSession::ClientSession()
{
	//TODO
}

ClientSession::~ClientSession()
{
	//TODO
}
//
//ClientSessionRef ClientSession::GetClientSessionRef()
//{
//	return std::static_pointer_cast<ClientSession>(shared_from_this());
//}

// [size(2)][id(2)][data....][size(2)][id(2)][data....]
int32 ClientSession::OnRecv(BYTE* buffer, int32 len)
{
	int32 processLen = 0;

	while (true)
	{
		int32 dataSize = len - processLen;
		// �ּ��� ����� �Ľ��� �� �־�� �Ѵ�
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
	//PacketSessionRef session = GetPacketSessionRef();
	//PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	//// TODO : packetId �뿪 üũ
	//ClientPacketHandler::HandlePacket(session, buffer, len);
}

void ClientSession::OnSend(int32 len)
{
}