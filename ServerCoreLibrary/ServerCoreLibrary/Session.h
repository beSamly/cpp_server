#pragma once
#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"
#include "NetAddress.h"
#include "RecvBuffer.h"

class Service;

/*--------------
	Session
---------------*/

class Session : public IocpObject
{
	friend class BaseSocketServer;
	friend class IocpCore;
	friend class Service;

	enum
	{
		BUFFER_SIZE = 0x10000, // 64KB
	};
/*---------------------
	Member Variables
----------------------*/
private:
	weak_ptr<Service>		_service;
	SOCKET					_socket = INVALID_SOCKET;
	NetAddress				_netAddress = {};
	Atomic<bool>			_connected = false;

private:
	USE_LOCK;

	/* ���� ���� */
	RecvBuffer				_recvBuffer;

	/* �۽� ���� */
	Queue<SendBufferRef>	_sendQueue;
	Atomic<bool>			_sendRegistered = false;

	BaseSocketServerRef		_server;

private:
	/* IocpEvent ���� */
	ConnectEvent			_connectEvent;
	DisconnectEvent			_disconnectEvent;
	RecvEvent				_recvEvent;
	SendEvent				_sendEvent;

/*------------------
		Method
-------------------*/
public:
	Session();
	virtual ~Session();

public:
						/* �ܺο��� ��� */
	void				Send(SendBufferRef sendBuffer);
	bool				Connect();
	void				Disconnect(const WCHAR* cause);
	void				SetOwner(BaseSocketServerRef server) { _server = server; }

						/* ���� ���� */
	void				SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress			GetAddress() { return _netAddress; }
	SOCKET				GetSocket() { return _socket; }
	bool				IsConnected() { return _connected; }
	SessionRef			GetSessionRef() { return static_pointer_cast<Session>(shared_from_this()); }

private:
						/* �������̽� ���� */
	HANDLE				GetHandle() override;
	void				HandleIocpEvent(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
						/* ���� ���� */
	bool				RegisterConnect();
	bool				RegisterDisconnect();
	void				RegisterRecv();
	void				RegisterSend();

	void				ProcessConnect();
	void				ProcessDisconnect();
	void				ProcessRecv(int32 numOfBytes);
	void				ProcessSend(int32 numOfBytes);

	void				HandleError(int32 errorCode);

protected:
						/* �������̽� */
	virtual void		OnConnected() abstract;
	virtual int32		OnRecv(BYTE* buffer, int32 len) abstract;
	virtual void		OnSend(int32 len) abstract;
	virtual void		OnDisconnected() abstract;
};
