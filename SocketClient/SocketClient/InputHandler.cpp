#include "pch.h"
#include "InputHandler.h"
#include "Logger.h"

using std::cin;

void ProcessLogin();

void InputHandler::HandleInput(int32 key)
{
	switch (key) {
	case 1:
		ProcessLogin();
		break;
	case 2:
		break;
	default:
		break;
	}
}

void ProcessLogin() {
	string id;
	string email;

	cout << "email : " << endl;
	cin >> id;

	cout << "password : " << endl;
	cin >> email;

	Log->Info("Sending packet to " + id + " " + email);
}
