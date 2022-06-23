#include "pch.h"
#include "InputHandler.h"
#include "Logger.h"
#include "LoginRequest.pb.h"
#include "PacketManager.h"
#include "PacketId.h"

using std::cin;

void SendLoginRequest(SocketClientRef socketClient);

void InputHandler::HandleInput(SocketClientRef socketClient, int32 key)
{
	switch (key) {
	case 1:
		SendLoginRequest(socketClient);
		break;
	case 2:
		break;
	default:
		break;
	}
}

void SendLoginRequest(SocketClientRef socketClient) {
	string email;
	string password;

	cout << "email : " << endl;
	cin >> email;

	cout << "password : " << endl;
	cin >> password;

	Protocol::LoginRequest pkt;
	pkt.set_email(email);
	pkt.set_password(password);

	SendBufferRef buffer = PacketManager::PacketToSendBuffer(pkt, PacketId::LOGIN_REQ);
	socketClient->_serverSession->Send(buffer);
}
