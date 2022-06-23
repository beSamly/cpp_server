#pragma once
#include "IPacketHandler.h"
#include "PacketId.h"
#include "LoginResponseHandler.h"
#include "PacketHeader.h"
#include "SendBuffer.h"

class PacketManager
{
public:
	static Vector<IPacketHandler*> handlers;

public:
	static void Init()
	{
		handlers = Vector<IPacketHandler*>(UINT16_MAX, nullptr);
		Vector<IPacketHandler*> handlers(UINT16_MAX, nullptr);
		handlers[PacketId::LOGIN_RES] = (IPacketHandler*)(new LoginResponseHandler());
	}

	static void HandlePacket(ServerSessionRef session, int16 packetId, BYTE* buffer, int32 len) {

		if (handlers[packetId] == nullptr) {
			// TODO logging
			cout << "Invalid packet id received" << packetId << endl;
			return;
		}

		handlers[packetId]->HandlePacket(session, buffer, len);
	}
	
	template<typename T>
	static SendBufferRef PacketToSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = MakeShared<SendBuffer>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());

		header->size = packetSize;
		header->id = pktId;

		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};

