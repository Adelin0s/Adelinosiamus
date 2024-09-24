#pragma once

#include "AbstractSingleton.h"

class IAbstractChat : public TAbstractSingleton<IAbstractChat>
{
	public:
		IAbstractChat() {}
		virtual ~IAbstractChat() {}

		virtual void AppendChat(int iType, const char * c_szChat) = 0;
};
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
