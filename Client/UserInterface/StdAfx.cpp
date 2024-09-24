// stdafx.cpp : source file that includes just the standard includes
//	UserInterface.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef ENABLE_DUNGEON_BOSS_ICON_IN_MAP
#include "PythonNonPlayer.h"
bool IsBoss(DWORD race)
{
	const CPythonNonPlayer::TMobTable* pMobTable = CPythonNonPlayer::Instance().GetTable(race);
	if (pMobTable && pMobTable->bType == 0 && pMobTable->bRank >= 4)
		return true;
	return false;
}
bool GetDungeonNPC(DWORD mobIndex)
{
	if (mobIndex >= 9860 && mobIndex <= 9871)// Zodiac
		return true;
	switch (mobIndex)
	{
	case 20371:// barones
	case 20367: // cata
	case 9023: // crystal
	case 20348:// deviltower
	case 20353: // ork
	case 30121:// beran
	case 9043:// eregon
	case 20394:// razador
	case 9045:// green lion
	case 20412: //jotun
	case 9042:// mushroom
	case 20419:// meley
	case 20173://orc maze
	case 9032:// sahmeran
	case 20395:// nemere
	case 9044:// trex
	case 9025:// vespik
	case 20423:// viserion
	case 9038: // caribbean
	case 9046:// fenrir
	case 90009:// hydra
		return true;
	}
	return false;
}
#endif

//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
