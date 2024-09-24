#pragma once

class CPythonExceptionSender : public IPythonExceptionSender
{
	public:
		CPythonExceptionSender();
		virtual ~CPythonExceptionSender();

		void Send();

	protected:
		std::set<DWORD> m_kSet_dwSendedExceptionCRC;
};
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
