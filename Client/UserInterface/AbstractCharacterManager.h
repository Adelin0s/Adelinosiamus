#pragma once

#include "AbstractSingleton.h"

class CInstanceBase;

class IAbstractCharacterManager : public TAbstractSingleton<IAbstractCharacterManager>
{
	public:
		IAbstractCharacterManager() {}
		virtual ~IAbstractCharacterManager() {}

		virtual void Destroy() = 0;
		virtual CInstanceBase *						GetInstancePtr(DWORD dwVID) = 0;
};
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
