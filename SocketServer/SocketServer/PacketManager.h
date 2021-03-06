#pragma once
#include "IPacketHandler.h"
#include "ClientSession.h"
#include "PacketHeader.h"
#include "SendBuffer.h"

class PacketManager
{
private:
	std::vector<IPacketHandler*> _handlers;

public:
	PacketManager();
	~PacketManager();
	void Init();
	
	void HandlePacket(ClientSessionRef& session, int16 packetId, BYTE* buffer, int32 len);

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

