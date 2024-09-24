/*
* @author: blackdragonx61 / Mali
* @date: 08.09.2022
* @github: https://github.com/blackdragonx61
* @dev: https://metin2.dev/profile/14335-mali
* @youtube: https://www.youtube.com/blackdragonx61
*/

#include "StdAfx.h"
#include "InstanceBase.h"
#include "PythonCharacterManager.h"
#include "PythonNonPlayer.h"
#include "../GameLib/RaceManager.h"

PyObject* ingameEventSystemSetValentineEventMetinstone(PyObject* poSelf, PyObject* poArgs)
{
	bool bEnable;
	if (!PyTuple_GetBoolean(poArgs, 0, &bEnable))
		return Py_BadArgument();

	CRaceManager::Instance().SetValentineStoneShapeState(bEnable);

	CPythonCharacterManager& rkChrMgr = CPythonCharacterManager::Instance();
	for (CPythonCharacterManager::CharacterIterator i = rkChrMgr.CharacterInstanceBegin(); i != rkChrMgr.CharacterInstanceEnd(); ++i)
	{
		CInstanceBase* pkInstEach = *i;
		if (!pkInstEach)
			continue;

		if (!pkInstEach->IsStone())
			continue;

		const DWORD dwRace = pkInstEach->GetRealRace();
		DWORD dwEventRace = 0;

		if (dwRace >= 0x1F41 && dwRace <= 0x1F68)
			dwEventRace = 0x2008;
		else if (dwRace >= 0x1F73 && dwRace <= 0x1FB3)
			dwEventRace = 0x2009;

		if (dwEventRace)
		{
			if (bEnable)
			{
				pkInstEach->SetRaceDataStoneShapeEvent(dwRace);
				pkInstEach->ChangeStoneShape(dwEventRace, 0);
				pkInstEach->RestoreRenderMode();
				pkInstEach->SetAddColor(D3DXCOLOR(0.0, 0.0, 0.0, 1.0f));
			}
			else
			{
				const DWORD c_rColor = CPythonNonPlayer::Instance().GetMonsterColor(dwRace);
				if (c_rColor)
					pkInstEach->SetColorOperation(dwRace, c_rColor);

				pkInstEach->ChangeStoneShape(dwRace, 0);
				pkInstEach->ResetRaceDataStoneShapeEvent();
			}
		}
	}

	return Py_BuildNone();
}

PyObject* ingameEventSystemSetIceCreamEventMetinstone(PyObject* poSelf, PyObject* poArgs)
{
	bool bEnable;
	if (!PyTuple_GetBoolean(poArgs, 0, &bEnable))
		return Py_BadArgument();

	CRaceManager::Instance().SetIceCreamStoneShapeState(bEnable);

	CPythonCharacterManager& rkChrMgr = CPythonCharacterManager::Instance();
	for (CPythonCharacterManager::CharacterIterator i = rkChrMgr.CharacterInstanceBegin(); i != rkChrMgr.CharacterInstanceEnd(); ++i)
	{
		CInstanceBase* pkInstEach = *i;
		if (!pkInstEach)
			continue;

		if (!pkInstEach->IsStone())
			continue;

		const DWORD dwRace = pkInstEach->GetRealRace();
		if ((dwRace >= 0x1F41 && dwRace <= 0x1F68) || (dwRace >= 0x1F73 && dwRace <= 0x1FB3))
			pkInstEach->ChangeStoneShape(bEnable ? 0x200Au : dwRace, 0);
	}

	return Py_BuildNone();
}

PyObject* ingameEventSystemSetRamadanEventMetinstone(PyObject* poSelf, PyObject* poArgs)
{
	bool bEnable;
	if (!PyTuple_GetBoolean(poArgs, 0, &bEnable))
		return Py_BadArgument();

	CRaceManager::Instance().SetRamadanStoneShapeState(bEnable);

	CPythonCharacterManager& rkChrMgr = CPythonCharacterManager::Instance();
	for (CPythonCharacterManager::CharacterIterator i = rkChrMgr.CharacterInstanceBegin(); i != rkChrMgr.CharacterInstanceEnd(); ++i)
	{
		CInstanceBase* pkInstEach = *i;
		if (!pkInstEach)
			continue;

		if (!pkInstEach->IsStone())
			continue;

		const DWORD dwRace = pkInstEach->GetRealRace();
		if ((dwRace >= 0x1F41 && dwRace <= 0x1F68) || (dwRace >= 0x1F73 && dwRace <= 0x1FB3))
			pkInstEach->ChangeStoneShape(bEnable ? 0x200Bu : dwRace, 0);
	}

	return Py_BuildNone();
}

PyObject* ingameEventSystemSetYutnoriEventMetinstone(PyObject* poSelf, PyObject* poArgs)
{
	bool bEnable;
	if (!PyTuple_GetBoolean(poArgs, 0, &bEnable))
		return Py_BadArgument();

	CRaceManager::Instance().SetYutnoriStoneShapeState(bEnable);

	CPythonCharacterManager& rkChrMgr = CPythonCharacterManager::Instance();
	for (CPythonCharacterManager::CharacterIterator i = rkChrMgr.CharacterInstanceBegin(); i != rkChrMgr.CharacterInstanceEnd(); ++i)
	{
		CInstanceBase* pkInstEach = *i;
		if (!pkInstEach)
			continue;

		if (!pkInstEach->IsStone())
			continue;

		const DWORD dwRace = pkInstEach->GetRealRace();
		if ((dwRace >= 0x1F41 && dwRace <= 0x1F68) || (dwRace >= 0x1F73 && dwRace <= 0x1FB3))
		{
			if (bEnable)
			{
				pkInstEach->ChangeStoneShape(0x1F7C, 0);
				pkInstEach->RestoreRenderMode();
				pkInstEach->SetAddColor(D3DXCOLOR(0.0, 0.0, 0.0, 1.0f));
			}
			else
			{
				const DWORD c_rColor = CPythonNonPlayer::Instance().GetMonsterColor(dwRace);
				if (c_rColor)
					pkInstEach->SetColorOperation(dwRace, c_rColor);

				pkInstEach->ChangeStoneShape(dwRace, 0);
			}
		}
	}

	return Py_BuildNone();
}

PyObject* ingameEventSystemSetFootballEventMetinstone(PyObject* poSelf, PyObject* poArgs)
{
	bool bEnable;
	if (!PyTuple_GetBoolean(poArgs, 0, &bEnable))
		return Py_BadArgument();

	CRaceManager::Instance().SetFootballStoneShapeState(bEnable);

	CPythonCharacterManager& rkChrMgr = CPythonCharacterManager::Instance();
	for (CPythonCharacterManager::CharacterIterator i = rkChrMgr.CharacterInstanceBegin(); i != rkChrMgr.CharacterInstanceEnd(); ++i)
	{
		CInstanceBase* pkInstEach = *i;
		if (!pkInstEach)
			continue;

		if (!pkInstEach->IsStone())
			continue;

		const DWORD dwRace = pkInstEach->GetRealRace();
		if ((dwRace >= 0x1F41 && dwRace <= 0x1F68) || (dwRace >= 0x1F73 && dwRace <= 0x1FB3))
			pkInstEach->ChangeStoneShape(bEnable ? 0x200F : dwRace, 0);
	}

	return Py_BuildNone();
}

void initInGameEventSystem()
{
	static PyMethodDef s_methods[] =
	{
		{ "SetValentineEventMetinstone",	ingameEventSystemSetValentineEventMetinstone,	METH_VARARGS },
		{ "SetIceCreamEventMetinstone",		ingameEventSystemSetIceCreamEventMetinstone,	METH_VARARGS },
		{ "SetRamadanEventMetinstone",		ingameEventSystemSetRamadanEventMetinstone,		METH_VARARGS },
		{ "SetYutnoriEventMetinstone",		ingameEventSystemSetYutnoriEventMetinstone,		METH_VARARGS },
		{ "SetFootballEventMetinstone",		ingameEventSystemSetFootballEventMetinstone,	METH_VARARGS },

		{ NULL,								NULL,											NULL		 },
	};

	Py_InitModule("ingameEventSystem", s_methods);
}