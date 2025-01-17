#pragma once

#ifndef VC_EXTRALEAN

class CNetDatagramSender
{
	public:
		CNetDatagramSender();
		virtual ~CNetDatagramSender();

		BOOL isSocket();

		BOOL SetSocket(const char * c_szIP, WORD wPortIndex);
		BOOL SetSocket(DWORD dwAddress, WORD wPortIndex);
		BOOL Send(const void * pBuffer, int iSize);

	protected:
		BOOL m_isSocket;

		WORD m_dwAddress;
		WORD m_wPortIndex;

		SOCKET m_Socket;
		SOCKADDR_IN m_SockAddr;
};

#endif
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
