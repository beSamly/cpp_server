#pragma once
#include "IPacketHandler.h"
#include "PacketId.h"
#include "LoginResponse.h"
#include "PacketHeader.h"
#include "SendBuffer.h"

class PacketManager
{
private:
	Vector<IPacketHandler*> _handlers = Vector<IPacketHandler*>(UINT16_MAX, nullptr);

public:
	PacketManager();
	~PacketManager();
	void Init();

	void HandlePacket(ServerSessionRef& session, int16 packetId, BYTE* buffer, int32 len);

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

