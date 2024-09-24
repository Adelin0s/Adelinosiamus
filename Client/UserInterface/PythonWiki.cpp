#include "StdAfx.h"

#ifdef ENABLE_WIKI
#include "PythonWiki.h"
#include "PythonNetworkStream.h"
#include "PythonPlayer.h"
#include "../GameLib/ItemManager.h"
#include "../eterPack/EterPackManager.h"

bool printLocalDatainSysser = false;

//STATIC-FUNCTIONS
bool CompareLevel(const character_data i, const character_data j) { return (i.level > j.level); }
bool CompareLevelLow(const character_data i, const character_data j) { return (i.level < j.level); }
bool isFirstItem(DWORD itemVnum, const char* szname)
{
	const std::string str(szname);
	if (str.find("+0") != std::string::npos)
		return true;
	return false;
}
bool isLastItem(DWORD itemVnum, const char* szname, BYTE itemType)
{
	const std::string str(szname);
	std::string strrefine = "+";
	strrefine += std::to_string(CPythonWiki::Instance().GetRefineLevel(itemVnum, itemType, 0));
	if (str.find(strrefine.c_str()) != std::string::npos)
		return true;
	return false;
}

CPythonWiki::~CPythonWiki() {}
CPythonWiki::CPythonWiki() : m_bLoaded(false) {}

void CPythonWiki::ReadData(const char* localeFile)
{
	if (m_bLoaded)
		return;
	m_bLoaded = true;

	if (!LoadRefineTable("locale/refine_table.txt"))
		TraceError("CPythonApplication - CPythonWiki::LoadRefineTable(locale/refine_table.txt)");
	char szItemProto[256];
	snprintf(szItemProto, sizeof(szItemProto), "%s/item_proto", localeFile);
	if (!LoadItemTable(szItemProto))
		TraceError("CPythonWiki - LoadItemTable(%s) Error", szItemProto);
	ReadSpecialDropItemFile("locale/special_item_group.txt");
	ReadMobDropItemFile("locale/mob_drop_item.txt");
	ReadCubeFile("locale/cube.txt");
}

bool CPythonWiki::ReadSpecialDropItemFile(const char* c_pszFileName)
{
	CTextFileLoader loader;
	if (!loader.Load(c_pszFileName))
		return false;

	int iVnum;
	std::vector<special_data> vecSpecialData;
	std::string stName("");
	TTokenVector* pTok;

	for (DWORD i = 0; i < loader.GetChildNodeCount(); ++i)
	{
		loader.SetChildNode(i);
		loader.GetCurrentNodeName(&stName);
		if (!loader.GetTokenInteger("vnum", &iVnum))
		{
			TraceError("ReadSpecialDropItemFile:Syntax error %s : no vnum, node %s", c_pszFileName, stName.c_str());
			loader.SetParentNode();
			continue;
		}
		vecSpecialData.clear();

		for (int k = 1; k < 256; ++k)
		{
			char buf[4];
			snprintf(buf, sizeof(buf), "%d", k);
			if (loader.GetTokenVector(buf, &pTok))
			{
				vecSpecialData.emplace_back(special_data(std::stoi(pTok->at(0)), std::stoi(pTok->at(1))));
				continue;
			}
			break;
		}
		loader.SetParentNode();

		if (vecSpecialData.size())
		{
			if (printLocalDatainSysser)
			{
				TraceError("                ");
				TraceError("ChestIndex: %d", iVnum);
				for (DWORD j = 0; j < vecSpecialData.size(); ++j)
					TraceError("Chest Data - Index: %d  ItemVnum: %d ItemCount: %d", j, vecSpecialData[j].itemVnum, vecSpecialData[j].count);
			}
			m_vecSpecialDrop.emplace(iVnum, vecSpecialData);
		}
	}
	return true;
}

bool CPythonWiki::ReadMobDropItemFile(const char* c_pszFileName)
{
	CTextFileLoader loader;
	if (!loader.Load(c_pszFileName))
		return false;

	int iVnum;
	std::vector<special_data> vecSpecialData;
	std::string stName("");
	TTokenVector* pTok;

	for (DWORD i = 0; i < loader.GetChildNodeCount(); ++i)
	{
		loader.SetChildNode(i);
		loader.GetCurrentNodeName(&stName);
		if (!loader.GetTokenInteger("mob", &iVnum))
		{
			TraceError("ReadMobDropItemFile:Syntax error %s : no vnum, node %s", c_pszFileName, stName.c_str());
			loader.SetParentNode();
			continue;
		}
		vecSpecialData.clear();
		for (int k = 1; k < 256; ++k)
		{
			char buf[4];
			snprintf(buf, sizeof(buf), "%d", k);
			if (loader.GetTokenVector(buf, &pTok))
			{
				vecSpecialData.emplace_back(special_data(std::stoi(pTok->at(0)), std::stoi(pTok->at(1))));
				continue;
			}
			break;
		}
		loader.SetParentNode();
		if (vecSpecialData.size())
		{
			if (printLocalDatainSysser)
			{
				TraceError("                ");
				TraceError("MobIndex: %d", iVnum);
				for (DWORD j = 0; j < vecSpecialData.size(); ++j)
					TraceError("Mob Data - Index: %d  ItemVnum: %d ItemCount: %d", j, vecSpecialData[j].itemVnum, vecSpecialData[j].count);
			}
			m_vecMobDrop.emplace(iVnum, vecSpecialData);
		}
	}
	return true;
}

bool CPythonWiki::LoadItemTable(const char* c_szFileName)
{
	CMappedFile file;
	LPCVOID pvData;
	if (!CEterPackManager::Instance().Get(file, c_szFileName, &pvData))
		return false;
	DWORD dwFourCC, dwElements, dwDataSize, dwVersion = 0, dwStride = 0;
	file.Read(&dwFourCC, sizeof(DWORD));
	if (dwFourCC == MAKEFOURCC('M', 'I', 'P', 'X'))
	{
		file.Read(&dwVersion, sizeof(DWORD));
		file.Read(&dwStride, sizeof(DWORD));
		if (dwVersion != 1)
		{
			TraceError("CPythonItem::LoadItemTable: invalid item_proto[%s] VERSION[%d]", c_szFileName, dwVersion);
			return false;
		}
		if (dwStride != sizeof(CItemData::TItemTable))
		{
			TraceError("CPythonItem::LoadItemTable: invalid item_proto[%s] STRIDE[%d] != sizeof(SItemTable)", c_szFileName, dwStride, sizeof(CItemData::TItemTable));
			return false;
		}
	}
	else if (dwFourCC != MAKEFOURCC('M', 'I', 'P', 'T'))
	{
		TraceError("CPythonItem::LoadItemTable: invalid item proto type %s", c_szFileName);
		return false;
	}
	file.Read(&dwElements, sizeof(DWORD));
	file.Read(&dwDataSize, sizeof(DWORD));

#ifdef ENABLE_NEW_OPTIMIZATION
	std::unique_ptr<BYTE[]> pbData(new BYTE[dwDataSize]());
	file.Read(pbData.get(), dwDataSize);
	CLZObject zObj;
	if (!CLZO::Instance().Decompress(zObj, pbData.get(), COMPRESS_ITEM))
	{
#else
	BYTE* pbData = new BYTE[dwDataSize];
	file.Read(pbData, dwDataSize);
	CLZObject zObj;
	if (!CLZO::Instance().Decompress(zObj, pbData, COMPRESS_ITEM))
	{
		delete[] pbData;
#endif
		return false;
	}
	CItemData::TItemTable* table = (CItemData::TItemTable*)zObj.GetBuffer();
	for (DWORD i = 0; i < dwElements; ++i, ++table)
		CPythonWiki::Instance().LoadItem(table);
#ifndef ENABLE_NEW_OPTIMIZATION
	delete[] pbData;
#endif

	for (DWORD j = 0; j < CRaceData::JOB_MAX_NUM; j++)
	{
		std::stable_sort(m_vecWeapon[j].begin(), m_vecWeapon[j].end(), CompareLevel);
		std::stable_sort(m_vecArmor[j].begin(), m_vecArmor[j].end(), CompareLevel);
		std::stable_sort(m_vecHelmets[j].begin(), m_vecHelmets[j].end(), CompareLevel);
		std::stable_sort(m_vecShields[j].begin(), m_vecShields[j].end(), CompareLevel);
		std::stable_sort(m_vecEarrings[j].begin(), m_vecEarrings[j].end(), CompareLevel);
		std::stable_sort(m_vecBracelet[j].begin(), m_vecBracelet[j].end(), CompareLevel);
		std::stable_sort(m_vecNecklace[j].begin(), m_vecNecklace[j].end(), CompareLevel);
		std::stable_sort(m_vecShoes[j].begin(), m_vecShoes[j].end(), CompareLevel);
		std::stable_sort(m_vecBelt[j].begin(), m_vecBelt[j].end(), CompareLevel);
		std::stable_sort(m_vecTalisman[j].begin(), m_vecTalisman[j].end(), CompareLevel);
		std::stable_sort(m_vecCrystal[j].begin(), m_vecCrystal[j].end(), CompareLevel);
	}
	return true;
}


bool CPythonWiki::LoadRefineTable(const char* c_szFileName)
{
	CMappedFile File;
	LPCVOID pData;
	if (!CEterPackManager::Instance().Get(File, c_szFileName, &pData))
		return false;

	CMemoryTextFileLoader textFileLoader;
	textFileLoader.Bind(File.Size(), pData);

	CTokenVector TokenVector;
	for (DWORD i = 0; i < textFileLoader.GetLineCount(); ++i)
	{
		if (textFileLoader.GetLineString(i)[0] == '#')
			continue;
		if (!textFileLoader.SplitLine(i, &TokenVector, "\t"))
			continue;
		if (TokenVector.size() != 15)
		{
			TraceError("CPythonWiki::LoadRefineTable(%s) - StrangeLine in %d\n", c_szFileName, i);
			continue;
		}
		int row = 0;
		refineTable p;
		memset(&p, 0, sizeof(refineTable));

		p.id = (DWORD)atoi(TokenVector[row++].c_str());
		p.refine_count = 0;
		for (DWORD j = 0; j < MAX_REFINE_ITEM; ++j)
		{
			p.item_vnums[j] = (DWORD)atoi(TokenVector[row++].c_str());
			if (p.item_vnums[j] != 0)
				p.refine_count = j + 1;
			p.item_count[j] = (DWORD)atoi(TokenVector[row++].c_str());
		}
		p.cost = (long long)atoll(TokenVector[row++].c_str());
		row++;//src_num
		row++;//result_vnum
		p.prob = (DWORD)atoi(TokenVector[row++].c_str());
		m_vecRefineTable.emplace(p.id, p);
	}
	return true;
}

bool CPythonWiki::ItemBlackList(DWORD itemVnum, DWORD itemType, DWORD itemSubType)
{

	constexpr DWORD m_BlockedItemVnumRangeList[][2] = {
		// block {start, end},
		{360, 395},
		{1210, 1226},
		{2230, 2246},
		{3250, 3266},
		{300, 309},	
		{320, 335},
		{340, 355},
		{5200, 5216},
		{7330, 7346},
		{200, 209},
		{21310, 21406},
		{20810, 20859},
		{20910, 20959},
		{12780, 12789},
		{13210, 13219},
		{13200, 13209},
		{13190, 13199},
		{17570, 17609},
		{16580, 16619},
		{14580, 14619},
		{15240, 15249},
		{18100, 18109},
		{18040, 18049},
		{18070, 18079},
		{9626, 9800},
		{9856, 10030},
		{10086, 10260},
		{10316, 10490},
		{10546, 10720},
		{1190,1199},
		{2210,2219},
		{3230,3239},
		{5170,5179},
		{7310,7319},
		{21210,21279},
		{12800,12809},
		{12840,12849},
		{12820,12829},
	};
	for (DWORD j = 0; j < _countof(m_BlockedItemVnumRangeList); ++j)
		if (itemVnum >= m_BlockedItemVnumRangeList[j][0] && itemVnum <= m_BlockedItemVnumRangeList[j][1])
			return false;

	const std::vector<DWORD> m_BlockedItemVnumList = {
		// warrior & weapon blacklist
		9510, 9520, 219, 229, 239, 269, 3179, 3189, 7209,
		21970, 21960, 21950, 21940, 21930, 21920, 21910, 21900,

		// ninja & weapon blacklist
		1149, 1159, 1169, 8000,

		// shaman & weapon blacklist
		5139, 5149, 5159, 7179, 7189,

		// armor blacklist
		11000, 11010, 11020, 11030,

		// shield blacklist
		13189,
	};
	return std::find(m_BlockedItemVnumList.begin(), m_BlockedItemVnumList.end(), itemVnum) != m_BlockedItemVnumList.end() ? false : true;
}

BYTE CPythonWiki::GetRefineLevel(DWORD itemVnum, DWORD itemType, DWORD itemSubType)
{
	if (itemVnum >= 9600 && itemVnum <= 10775)
		return 25;

	if (itemVnum >= 51010 && itemVnum <= 51030)
		return 20;

	// ymir +15 items
	//constexpr DWORD darkVnums[] = { 320,340,1190,2210,3230,5170,7310,12780,12800,12820,12840,12860,21210,21230,21250,21270,};
	//for (UINT i = 0; i < _countof(darkVnums); i++)
	//{
	//	if (itemVnum >= darkVnums[i] && itemVnum <= darkVnums[i] + 15)
	//		return 15;
	//}
	return 9;
}

const refineTable* CPythonWiki::GetRefineItem(DWORD index)
{
	const auto it = m_vecRefineTable.find(index);
	return it != m_vecRefineTable.end() ? &it->second : NULL;
}

void CPythonWiki::ListReverse()
{
	for (DWORD j = 0; j < 3; j++)
	{
		std::stable_sort(m_vecStoneCategory[j].begin(), m_vecStoneCategory[j].end(), CompareLevelLow);
		std::stable_sort(m_vecBossCategory[j].begin(), m_vecBossCategory[j].end(), CompareLevelLow);
		std::stable_sort(m_vecMonsterCategory[j].begin(), m_vecMonsterCategory[j].end(), CompareLevelLow);
	}
}

bool CPythonWiki::BlackListMonster(DWORD mobVnum)
{
	const std::vector<DWORD> m_BlockedMonsterVnumList = {
		//monsters
		194, 193, 192, 191, 491, 492, 493, 494, 591, 2091, 1304, 2206, 1901, 791, 2191, 691,
		3890, 3596, 3590, 3390, 3290, 3090, 3790, 3190, 3690, 3490, 3891, 3591, 3595, 3091, 3291, 3391, 3191, 3791, 3491, 3691,
		2092, 693, 1093, 2598, 2493, 6191, 6091, 6192, 3965, 20420, 6500, 6501, 2752, 2762, 2772, 2782, 2792, 2802, 2812, 2822, 2832, 2842, 2852, 2862,
		1192,
		1091, 2094, 2597, 6051, 6151, 6408, 2750, 2760, 2770, 2780, 2790, 2800, 2810, 2820, 2830, 2840, 2850, 2860, 2751, 2761, 2771, 2781, 2791, 2801, 2811, 2821, 2831, 2841, 2851, 2861, 4479, 4439, 4469, 3956,
		8001, 8002, 8003, 8004, 8005, 8006, 8007, 8008, 8009, 8010, 8011, 8012, 8013, 8014,
		8024, 8025, 8026, 8027,
		8051, 8052, 8053, 8054, 8055, 8056, 8061, 8063,
		8015, 8017, 8018, 8032, 2095, 8016, 8019, 8031, 20399, 20422, 20500, 2902, 2908, 2903, 2904, 2907, 2900, 2901, 2905, 2906,
	};

	if (std::find(m_BlockedMonsterVnumList.begin(), m_BlockedMonsterVnumList.end(), mobVnum) != m_BlockedMonsterVnumList.end())
		return false;

	constexpr DWORD m_BlockedMonsterVnumRangeList[][2] = {
		// block {start, end},
		{0, 0},
	};
	for (DWORD j = 0; j < _countof(m_BlockedMonsterVnumRangeList); ++j)
		if (mobVnum >= m_BlockedMonsterVnumRangeList[j][0] && mobVnum <= m_BlockedMonsterVnumRangeList[j][1])
			return false;

	return true;
}

bool CPythonWiki::LowLevelBoss(DWORD mobVnum)
{
	const std::vector<DWORD> m_LowLevelVnumList = {
		//monsters
		194, 193, 192, 191, 491, 492, 493, 494, 591, 2091, 1304, 2206, 1901, 791, 2191, 691,
	};

	if (std::find(m_LowLevelVnumList.begin(), m_LowLevelVnumList.end(), mobVnum) != m_LowLevelVnumList.end())
		return true;

	return false;;
}

bool CPythonWiki::HighLevelBoss(DWORD mobVnum)
{
	const std::vector<DWORD> m_LowLevelVnumList = {
		//monsters
		3890, 3596, 3590, 3390, 3290, 3090, 3790, 3190, 3690, 3490, 3891, 3591, 3595, 3091, 3291, 3391, 3191, 3791, 3491, 3691,

	};

	if (std::find(m_LowLevelVnumList.begin(), m_LowLevelVnumList.end(), mobVnum) != m_LowLevelVnumList.end())
		return true;

	return false;
}

bool CPythonWiki::PreBoss(DWORD mobVnum)
{
	const std::vector<DWORD> m_LowLevelVnumList = {
		//monsters
		1091, 2094, 2597, 6051, 6151, 6408, 2750, 2760, 2770, 2780, 2790, 2800, 2810, 2820, 2830, 2840, 2850, 2860, 2751, 2761, 2771, 2781, 2791, 2801, 2811, 2821, 2831, 2841, 2851, 2861, 4479, 4439, 4469, 3956,
	};

	if (std::find(m_LowLevelVnumList.begin(), m_LowLevelVnumList.end(), mobVnum) != m_LowLevelVnumList.end())
		return true;

	return false;
}

bool CPythonWiki::DungeonBoss(DWORD mobVnum)
{
	const std::vector<DWORD> m_LowLevelVnumList = {
		//monsters
		2092, 693, 1093, 2598, 2493, 6191, 6091, 6192, 3965, 20420, 6500, 6501, 2752, 2762, 2772, 2782, 2792, 2802, 2812, 2822, 2832, 2842, 2852, 2862,
	};

	if (std::find(m_LowLevelVnumList.begin(), m_LowLevelVnumList.end(), mobVnum) != m_LowLevelVnumList.end())
		return true;

	return false;
}

bool CPythonWiki::WorldBoss(DWORD mobVnum)
{
	const std::vector<DWORD> m_LowLevelVnumList = {
		//monsters
		1192,
	};

	if (std::find(m_LowLevelVnumList.begin(), m_LowLevelVnumList.end(), mobVnum) != m_LowLevelVnumList.end())
		return true;

	return false;
}

bool CPythonWiki::Stones(DWORD mobVnum)
{
	const std::vector<DWORD> m_LowLevelVnumList = {
		//monsters
		8001, 8002, 8003, 8004, 8005, 8006, 8007, 8008, 8009, 8010, 8011, 8012, 8013, 8014,
		8024, 8025, 8026, 8027,
		8051, 8052, 8053, 8054, 8055, 8056, 8061, 8063,
	};

	if (std::find(m_LowLevelVnumList.begin(), m_LowLevelVnumList.end(), mobVnum) != m_LowLevelVnumList.end())
		return true;

	return false;
}

bool CPythonWiki::DungeonStones(DWORD mobVnum)
{
	const std::vector<DWORD> m_LowLevelVnumList = {
		//monsters
		8015, 8017, 8018, 8032, 2095, 8016, 8019, 8031, 20399, 20422, 20500, 2902, 2908, 2903, 2904, 2907, 2900, 2901, 2905, 2906,
	};

	if (std::find(m_LowLevelVnumList.begin(), m_LowLevelVnumList.end(), mobVnum) != m_LowLevelVnumList.end())
		return true;

	return false;
}


void CPythonWiki::LoadMonster(CPythonNonPlayer::TMobTable* monster)
{
	if (BlackListMonster(monster->dwVnum))
		return;

	if (LowLevelBoss(monster->dwVnum))
	{
		m_vecBossCategory[0].emplace_back(character_data(monster->dwVnum, monster->bLevel));
	}
	else if (HighLevelBoss(monster->dwVnum))
	{
		m_vecBossCategory[1].emplace_back(character_data(monster->dwVnum, monster->bLevel));
	}
	else if (PreBoss(monster->dwVnum))
	{
		m_vecBossCategory[2].emplace_back(character_data(monster->dwVnum, monster->bLevel));
	}
	else if (DungeonBoss(monster->dwVnum))
	{
		m_vecBossCategory[3].emplace_back(character_data(monster->dwVnum, monster->bLevel));
	}
	else if (WorldBoss(monster->dwVnum))
	{
		m_vecBossCategory[4].emplace_back(character_data(monster->dwVnum, monster->bLevel));
	}
	else if (Stones(monster->dwVnum))
	{
		if (monster->bLevel >= 1 && monster->bLevel <= 70)
		{
			m_vecStoneCategory[0].emplace_back(character_data(monster->dwVnum, monster->bLevel));
		}
		else if (monster->bLevel >= 71 && monster->bLevel <= 105)
		{
			m_vecStoneCategory[1].emplace_back(character_data(monster->dwVnum, monster->bLevel));
		}
		else if (monster->bLevel >= 106)
		{
			m_vecStoneCategory[2].emplace_back(character_data(monster->dwVnum, monster->bLevel));
		}
	}
	else if (DungeonStones(monster->dwVnum))
	{
		m_vecStoneCategory[3].emplace_back(character_data(monster->dwVnum, monster->bLevel));
	}
}

void CPythonWiki::LoadItem(CItemData::TItemTable* item)
{
	constexpr BYTE flagList[CRaceData::JOB_MAX_NUM] = { CItemData::ITEM_ANTIFLAG_WARRIOR , CItemData::ITEM_ANTIFLAG_ASSASSIN ,CItemData::ITEM_ANTIFLAG_SHAMAN ,CItemData::ITEM_ANTIFLAG_SURA };

	if (isLastItem(item->dwVnum, item->szLocaleName, item->bType))
	{
		if (!ItemBlackList(item->dwVnum, item->bType, item->bSubType))
			return;
		DWORD itemLevel = 0;
		for (DWORD j = 0; j < CItemData::ITEM_LIMIT_MAX_NUM; j++)
		{
			if (item->aLimits[j].bType == CItemData::LIMIT_LEVEL)
			{
				itemLevel = item->aLimits[j].lValue;
				break;
			}
		}

		if (item->bType == CItemData::ITEM_TYPE_WEAPON)
		{
			for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
			{
				if (!(item->dwAntiFlags & flagList[j]))
					m_vecWeapon[j].emplace_back(character_data(item->dwVnum, itemLevel));
			}
		}
		else if (item->bType == CItemData::ITEM_TYPE_ARMOR)
		{
			if (item->bSubType == CItemData::ARMOR_BODY)
			{
				for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
				{
					if (!(item->dwAntiFlags & flagList[j]))
						m_vecArmor[j].emplace_back(character_data(item->dwVnum, itemLevel));
				}
			}
			else if (item->bSubType == CItemData::ARMOR_HEAD)
			{
				for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
				{
					if (!(item->dwAntiFlags & flagList[j]))
						m_vecHelmets[j].emplace_back(character_data(item->dwVnum, itemLevel));
				}
			}
			else if (item->bSubType == CItemData::ARMOR_SHIELD)
			{
				for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
				{
					if (!(item->dwAntiFlags & flagList[j]))
						m_vecShields[j].emplace_back(character_data(item->dwVnum, itemLevel));
				}
			}
			else if (item->bSubType == CItemData::ARMOR_WRIST)
			{
				for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
				{
					if (!(item->dwAntiFlags & flagList[j]))
						m_vecBracelet[j].emplace_back(character_data(item->dwVnum, itemLevel));
				}
			}
			else if (item->bSubType == CItemData::ARMOR_FOOTS)
			{
				for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
				{
					if (!(item->dwAntiFlags & flagList[j]))
						m_vecShoes[j].emplace_back(character_data(item->dwVnum, itemLevel));
				}
			}
			else if (item->bSubType == CItemData::ARMOR_NECK)
			{
				for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
				{
					if (!(item->dwAntiFlags & flagList[j]))
						m_vecNecklace[j].emplace_back(character_data(item->dwVnum, itemLevel));
				}
			}
			else if (item->bSubType == CItemData::ARMOR_EAR)
			{
				for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
				{
					if (!(item->dwAntiFlags & flagList[j]))
						m_vecEarrings[j].emplace_back(character_data(item->dwVnum, itemLevel));
				}
			}
			else if (item->bSubType == CItemData::ARMOR_PENDANT_FIRE ||
				item->bSubType == CItemData::ARMOR_PENDANT_ICE ||
				item->bSubType == CItemData::ARMOR_PENDANT_EARTH ||
				item->bSubType == CItemData::ARMOR_PENDANT_THUNDER ||
				item->bSubType == CItemData::ARMOR_PENDANT_DARK ||
				item->bSubType == CItemData::ARMOR_PENDANT_WIND)
			{
				for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
				{
					if (!(item->dwAntiFlags & flagList[j]))
						m_vecTalisman[j].emplace_back(character_data(item->dwVnum, itemLevel));
				}
			}
		}
		else if (item->bType == CItemData::ITEM_TYPE_BELT)
		{
			for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
			{
				if (!(item->dwAntiFlags & flagList[j]))
					m_vecBelt[j].emplace_back(character_data(item->dwVnum, itemLevel));
			}
		}
		else if (item->dwVnum >= 51010 && item->dwVnum <= 51030)
		{
			for (BYTE j = 0; j < CRaceData::JOB_MAX_NUM; ++j)
			{
				if (!(item->dwAntiFlags & flagList[j]))
					m_vecCrystal[j].emplace_back(character_data(item->dwVnum, itemLevel));
			}
		}
	}
}

PyObject* wikiGetRefineItems(PyObject* poSelf, PyObject* poArgs)
{
	int iRefineIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iRefineIndex))
		return Py_BadArgument();
	auto item = CPythonWiki::Instance().GetRefineItem(iRefineIndex);
	if (!item)
		return Py_BuildValue("i", 0);
	return Py_BuildValue("iiiiiiiiiiiOii", item->id,item->item_vnums[0], item->item_count[0],item->item_vnums[1], item->item_count[1],item->item_vnums[2], item->item_count[2],item->item_vnums[3], item->item_count[3],item->item_vnums[4], item->item_count[4], PyLong_FromLongLong(item->cost), item->prob, item->refine_count);
}

PyObject* wikiIsBlackList(PyObject* poSelf, PyObject* poArgs)
{
	int iItemVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemVnum))
		return Py_BadArgument();
	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BadArgument();
	int iSubtype;
	if (!PyTuple_GetInteger(poArgs, 2, &iSubtype))
		return Py_BadArgument();
	if (iItemVnum < 0 || iType < 0 || iSubtype < 0)
		return Py_BadArgument();
	return Py_BuildValue("i", CPythonWiki::Instance().ItemBlackList((DWORD)iItemVnum, (DWORD)iType, (DWORD)iSubtype));
}

PyObject* wikiGetCategorySize(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	int iCategoryType;
	if (!PyTuple_GetInteger(poArgs, 1, &iCategoryType))
		return Py_BadArgument();
	if (iType >= 0 && iType <= 3)
	{
		if (iCategoryType == 0)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecWeapon[iType].size());
		else if (iCategoryType == 1)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecArmor[iType].size());
		else if (iCategoryType == 2)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecHelmets[iType].size());
		else if (iCategoryType == 3)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecShields[iType].size());
		else if (iCategoryType == 4)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecEarrings[iType].size());
		else if (iCategoryType == 5)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecBracelet[iType].size());
		else if (iCategoryType == 6)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecNecklace[iType].size());
		else if (iCategoryType == 7)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecShoes[iType].size());
		else if (iCategoryType == 8)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecBelt[iType].size());
		else if (iCategoryType == 9)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecTalisman[iType].size());
		else if (iCategoryType == 10)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecCrystal[iType].size());
	}
	return Py_BuildValue("i", 0);
}

PyObject* wikiGetCategoryData(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	int iCategoryType;
	if (!PyTuple_GetInteger(poArgs, 1, &iCategoryType))
		return Py_BadArgument();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 2, &iIndex))
		return Py_BadArgument();
	if (iType >= 0 && iType <= 3)
	{
		if (iCategoryType == 0)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecWeapon[iType][iIndex].itemVnum);
		else if (iCategoryType == 1)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecArmor[iType][iIndex].itemVnum);
		else if (iCategoryType == 2)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecHelmets[iType][iIndex].itemVnum);
		else if (iCategoryType == 3)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecShields[iType][iIndex].itemVnum);
		else if (iCategoryType == 4)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecEarrings[iType][iIndex].itemVnum);
		else if (iCategoryType == 5)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecBracelet[iType][iIndex].itemVnum);
		else if (iCategoryType == 6)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecNecklace[iType][iIndex].itemVnum);
		else if (iCategoryType == 7)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecShoes[iType][iIndex].itemVnum);
		else if (iCategoryType == 8)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecBelt[iType][iIndex].itemVnum);
		else if (iCategoryType == 9)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecTalisman[iType][iIndex].itemVnum);
		else if (iCategoryType == 10)
			return Py_BuildValue("i", CPythonWiki::Instance().m_vecCrystal[iType][iIndex].itemVnum);
	}
	return Py_BuildValue("i", 0);
}

PyObject* wikiReadData(PyObject* poSelf, PyObject* poArgs)
{
	char* locale;
	if (!PyTuple_GetString(poArgs, 0, &locale))
		return Py_BuildException();
	CPythonWiki::Instance().ReadData(locale);
	return Py_BuildNone();
}

PyObject* wikiGetRefineMaxLevel(PyObject* poSelf, PyObject* poArgs)
{
	int iItemVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemVnum))
		return Py_BuildException();
	CItemManager::Instance().SelectItemData(iItemVnum);
	CItemData* pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildValue("i", CPythonWiki::Instance().GetRefineLevel(iItemVnum, 0, 0));
	return Py_BuildValue("i", CPythonWiki::Instance().GetRefineLevel(iItemVnum, pItemData->GetType(), pItemData->GetSubType()));
}

PyObject* wikiGetChestSize(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BuildException();
	if (iType == 0)
		return Py_BuildValue("i", _countof(bossChests));
	else if (iType == 1)
		return Py_BuildValue("i", _countof(eventChests));
	else if (iType == 2)
		return Py_BuildValue("i", _countof(alternativeChests));
	else if (iType == 3)
		return Py_BuildValue("i", _countof(ishopChests));
	return Py_BuildValue("i", 0);
}

PyObject* wikiGetChestData(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BuildException();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BuildException();
	if (iType == 0)
		return Py_BuildValue("ii", bossChests[iIndex][0], bossChests[iIndex][1]);
	else if (iType == 1)
		return Py_BuildValue("ii", eventChests[iIndex][0], eventChests[iIndex][1]);
	else if (iType == 2)
		return Py_BuildValue("ii", alternativeChests[iIndex][0], alternativeChests[iIndex][1]);
	else if (iType == 3)
		return Py_BuildValue("ii", ishopChests[iIndex][0], ishopChests[iIndex][1]);
	return Py_BuildValue("ii", 0,0);
}

PyObject* wikiGetSpecialInfoSize(PyObject* poSelf, PyObject* poArgs)
{
	int iItemVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemVnum))
		return Py_BuildException();
	const auto it = CPythonWiki::Instance().m_vecSpecialDrop.find(iItemVnum);
	if (it != CPythonWiki::Instance().m_vecSpecialDrop.end())
		return Py_BuildValue("i", it->second.size());
	return Py_BuildValue("i", 0);
}

PyObject* wikiGetSpecialInfoData(PyObject* poSelf, PyObject* poArgs)
{
	int iItemVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemVnum))
		return Py_BuildException();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BuildException();
	const auto it = CPythonWiki::Instance().m_vecSpecialDrop.find(iItemVnum);
	if (it != CPythonWiki::Instance().m_vecSpecialDrop.end())
		return Py_BuildValue("ii", it->second[iIndex].itemVnum, it->second[iIndex].count);
	return Py_BuildValue("ii", 0, 0);
}

PyObject* wikiGetMobInfoSize(PyObject* poSelf, PyObject* poArgs)
{
	int iItemVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemVnum))
		return Py_BuildException();
	const auto it = CPythonWiki::Instance().m_vecMobDrop.find(iItemVnum);
	if (it != CPythonWiki::Instance().m_vecMobDrop.end())
		return Py_BuildValue("i", it->second.size());
	return Py_BuildValue("i", 0);
}

PyObject* wikiGetMobInfoData(PyObject* poSelf, PyObject* poArgs)
{
	int iItemVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemVnum))
		return Py_BuildException();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BuildException();
	const auto it = CPythonWiki::Instance().m_vecMobDrop.find(iItemVnum);
	if (it == CPythonWiki::Instance().m_vecMobDrop.end())
		return Py_BuildValue("ii",0,0);
	return Py_BuildValue("ii", it->second[iIndex].itemVnum, it->second[iIndex].count);
}

PyObject* wikiGetBossSize(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	return Py_BuildValue("i", CPythonWiki::Instance().m_vecBossCategory[iType].size());
}

PyObject* wikiGetBossData(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BadArgument();
	return Py_BuildValue("i", CPythonWiki::Instance().m_vecBossCategory[iType][iIndex]);
}

PyObject* wikiCostumeSize(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	const auto it = m_CostumeData.find(iType);
	if (it != m_CostumeData.end())
		return Py_BuildValue("i", it->second.size());
	return Py_BuildValue("i", 0);
}
PyObject* wikiCostumeData(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BadArgument();
	const auto it = m_CostumeData.find(iType);
	if (it != m_CostumeData.end())
		return Py_BuildValue("i", it->second[iIndex]);
	return Py_BuildValue("i", 0);
}

PyObject* wikiGetMonsterSize(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	return Py_BuildValue("i", CPythonWiki::Instance().m_vecMonsterCategory[iType].size());
}

PyObject* wikiGetMonsterData(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BadArgument();
	return Py_BuildValue("i", CPythonWiki::Instance().m_vecMonsterCategory[iType][iIndex]);
}

PyObject* wikiGetStoneSize(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	return Py_BuildValue("i", CPythonWiki::Instance().m_vecStoneCategory[iType].size());
}

PyObject* wikiGetStoneData(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BadArgument();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BadArgument();
	return Py_BuildValue("i", CPythonWiki::Instance().m_vecStoneCategory[iType][iIndex]);
}

PyObject* wikiGetItemDropFromChest(PyObject* poSelf, PyObject* poArgs)
{
	int szItemVnum = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &szItemVnum))
		return Py_BadArgument();
	bool szIsRefineItem = false;
	if (!PyTuple_GetBoolean(poArgs, 1, &szIsRefineItem))
		return Py_BadArgument();

	PyObject* poList = PyList_New(0);

	const BYTE refineLevel = szIsRefineItem ? CPythonWiki::Instance().GetRefineLevel(szItemVnum, 0, 0) : 0;
	const auto m_vec_ItemRange = CPythonWiki::Instance().GetSpecialDrop();

	for (const auto& [chestVnum, chestData] : m_vec_ItemRange)
	{
		if (chestData.size() > 0)
		{
			if (szIsRefineItem)
			{
				for (const auto& dataItem : chestData)
				{
					if (szItemVnum >= dataItem.itemVnum && szItemVnum <= dataItem.itemVnum + refineLevel)
					{
						const auto obj = Py_BuildValue("i", chestVnum);
						PyList_Append(poList, obj);
						break;
					}
				}
			}
			else
			{
				for (const auto& dataItem : chestData)
				{
					if (szItemVnum == dataItem.itemVnum)
					{
						const auto obj = Py_BuildValue("i", chestVnum);
						PyList_Append(poList, obj);
						break;
					}

				}
			}

		}
	}
	return Py_BuildValue("O", poList);
}

PyObject* wikiGetItemDropFromMonster(PyObject* poSelf, PyObject* poArgs)
{
	int szItemVnum = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &szItemVnum))
		return Py_BadArgument();
	bool szIsRefineItem = false;
	if (!PyTuple_GetBoolean(poArgs, 1, &szIsRefineItem))
		return Py_BadArgument();

	PyObject* poList = PyList_New(0);
	const BYTE refineLevel = szIsRefineItem ? CPythonWiki::Instance().GetRefineLevel(szItemVnum, 0, 0) : 0;
	const auto m_vec_ItemRange = CPythonWiki::Instance().GetMobDrop();
	for (const auto& [mobVnum, mobData] : m_vec_ItemRange)
	{
		if (mobData.size() > 0)
		{
			if (szIsRefineItem)
			{
				for (const auto& dataItem : mobData)
				{
					if (szItemVnum >= dataItem.itemVnum && szItemVnum <= dataItem.itemVnum + refineLevel)
					{
						const auto obj = Py_BuildValue("i", mobVnum);
						PyList_Append(poList, obj);
						break;
					}
				}
			}
			else
			{
				for (const auto& dataItem : mobData)
				{
					if (szItemVnum == dataItem.itemVnum)
					{
						const auto obj = Py_BuildValue("i", mobVnum);
						PyList_Append(poList, obj);
						break;
					}

				}
			}
		}
	}
	return Py_BuildValue("O", poList);
}

#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp>
void split_argument_ex(const char* argument, std::vector<std::string>& vecArgs, const char* arg)
{
	boost::split(vecArgs, argument, boost::is_any_of(arg), boost::token_compress_on);
}

bool CPythonWiki::ReadCubeFile(const char* c_pszFileName)
{
	CMappedFile File;
	LPCVOID pData;
	if (!CEterPackManager::Instance().Get(File, c_pszFileName, &pData))
		return false;

	CMemoryTextFileLoader textFileLoader;
	textFileLoader.Bind(File.Size(), pData);

	cube_data cube;

	for (BYTE j = 0; j < _countof(m_vecCubeCategory); ++j)
		m_vecCubeCategory[j].clear();

	CTokenVector TokenVector;
	for (DWORD i = 0; i < textFileLoader.GetLineCount(); ++i)
	{
		if (textFileLoader.GetLineString(i)[0] == '#')
			continue;
		std::vector<std::string> m_LineSplit;
		split_argument_ex(textFileLoader.GetLineString(i).c_str(), m_LineSplit, "\t");

		if (!m_LineSplit.size())
			continue;

		if (m_LineSplit[0] == "section")
			memset(&cube, 0, sizeof(cube));
		else if (m_LineSplit[0] == "npc" && m_LineSplit.size() == 2)
			cube.mobIdx = (DWORD)atoi(m_LineSplit[1].c_str());
		else if (m_LineSplit[0] == "item" && m_LineSplit.size() == 3)
		{
			for (BYTE j = 0; j < 10; ++j)
			{
				if (cube.material[j].vnum == 0)
				{
					cube.material[j].vnum = (DWORD)atoi(m_LineSplit[1].c_str());
					cube.material[j].count = (WORD)atoi(m_LineSplit[2].c_str());
					break;
				}
			}
		}
		else if (m_LineSplit[0] == "reward" && m_LineSplit.size() == 3)
		{
			cube.reward.vnum = (DWORD)atoi(m_LineSplit[1].c_str());
			cube.reward.count = (WORD)atoi(m_LineSplit[2].c_str());
		}
		else if (m_LineSplit[0] == "percent" && m_LineSplit.size() == 2)
			cube.percent = (BYTE)atoi(m_LineSplit[1].c_str());
		else if (m_LineSplit[0] == "gold" && m_LineSplit.size() == 2)
			cube.gold = (DWORD)atoi(m_LineSplit[1].c_str());
		else if (m_LineSplit[0] == "gem" && m_LineSplit.size() == 2)
			cube.gem = (DWORD)atoi(m_LineSplit[1].c_str());
		else if (m_LineSplit[0] == "end")
		{
			if (cube.reward.vnum != 0)
			{
				CItemData* pItemData;
				if (CItemManager::Instance().GetItemDataPointer(cube.reward.vnum, &pItemData))
				{
					const CItemData::TItemTable* pTable = pItemData->GetTable();
					if (pTable)
					{
						BYTE categoryIdx = 0;

						const BYTE itemType = pTable->bType, itemSubType = pTable->bSubType, itemVnum = pTable->dwVnum;
						if (itemType)
						{
							if (itemType == CItemData::ITEM_TYPE_WEAPON)
								m_vecCubeCategory[0].emplace_back(cube);
							else if (itemType == CItemData::ITEM_TYPE_ARMOR)
							{
								if (itemSubType == CItemData::ARMOR_BODY)
									m_vecCubeCategory[1].emplace_back(cube);
								else if (itemSubType == CItemData::ARMOR_HEAD)
									m_vecCubeCategory[2].emplace_back(cube);
								else if (itemSubType == CItemData::ARMOR_SHIELD)
									m_vecCubeCategory[3].emplace_back(cube);
								else if (itemSubType == CItemData::ARMOR_EAR)
									m_vecCubeCategory[4].emplace_back(cube);
								else if (itemSubType == CItemData::ARMOR_WRIST)
									m_vecCubeCategory[5].emplace_back(cube);
								else if (itemSubType == CItemData::ARMOR_NECK)
									m_vecCubeCategory[6].emplace_back(cube);
								else if (itemSubType == CItemData::ARMOR_FOOTS)
									m_vecCubeCategory[7].emplace_back(cube);
							}
							else if (itemType == CItemData::ITEM_TYPE_BELT)
								m_vecCubeCategory[8].emplace_back(cube);
							else if (itemVnum >= 67001 && itemVnum <= 67011)
								m_vecCubeCategory[9].emplace_back(cube);
						}
					}
				}
			}
		}
	}
	return true;
}

PyObject* wikiGetCubeSize(PyObject* poSelf, PyObject* poArgs)
{
	int iCategoryType;
	if (!PyTuple_GetInteger(poArgs, 0, &iCategoryType))
		return Py_BadArgument();
	return Py_BuildValue("i", iCategoryType < _countof(CPythonWiki::Instance().m_vecCubeCategory) ? CPythonWiki::Instance().m_vecCubeCategory[iCategoryType].size() : 0);
}
PyObject* wikiGetCubeData(PyObject* poSelf, PyObject* poArgs)
{
	int iCategoryType;
	if (!PyTuple_GetInteger(poArgs, 0, &iCategoryType))
		return Py_BadArgument();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BadArgument();
	if (iCategoryType < _countof(CPythonWiki::Instance().m_vecCubeCategory))
	{
		const cube_data& cube = CPythonWiki::Instance().m_vecCubeCategory[iCategoryType][iIndex];
		return Py_BuildValue("iiiiiiiiiiiiiiiiiiiiiiii", cube.reward.vnum, cube.gold, cube.gem, cube.mobIdx,
			cube.material[0].vnum, cube.material[0].count,
			cube.material[1].vnum, cube.material[1].count,
			cube.material[2].vnum, cube.material[2].count,
			cube.material[3].vnum, cube.material[3].count,
			cube.material[4].vnum, cube.material[4].count,
			cube.material[5].vnum, cube.material[5].count,
			cube.material[6].vnum, cube.material[6].count,
			cube.material[7].vnum, cube.material[7].count,
			cube.material[8].vnum, cube.material[8].count,
			cube.material[9].vnum, cube.material[9].count);
	}
	return Py_BuildValue("i", 0);
}

void initWiki()
{
	static PyMethodDef s_methods[] =
	{
		{ "GetRefineItems",	wikiGetRefineItems,	METH_VARARGS },
		{ "IsBlackList",	wikiIsBlackList,	METH_VARARGS },

		{ "GetCategorySize",	wikiGetCategorySize,	METH_VARARGS },
		{ "GetCategoryData",	wikiGetCategoryData,	METH_VARARGS },

		{ "GetBossSize",	wikiGetBossSize,	METH_VARARGS },
		{ "GetBossData",	wikiGetBossData,	METH_VARARGS },

		{ "GetMonsterSize",	wikiGetMonsterSize,	METH_VARARGS },
		{ "GetMonsterData",	wikiGetMonsterData,	METH_VARARGS },

		{ "GetCostumeSize",	wikiCostumeSize,	METH_VARARGS },
		{ "GetCostumeData",	wikiCostumeData,	METH_VARARGS },

		{ "GetStoneSize",	wikiGetStoneSize,	METH_VARARGS },
		{ "GetStoneData",	wikiGetStoneData,	METH_VARARGS },

		{ "GetChestSize",	wikiGetChestSize,	METH_VARARGS },
		{ "GetChestData",	wikiGetChestData,	METH_VARARGS },

		{ "GetSpecialInfoSize",	wikiGetSpecialInfoSize,	METH_VARARGS },
		{ "GetSpecialInfoData",	wikiGetSpecialInfoData,	METH_VARARGS },

		{ "GetMobInfoSize",	wikiGetMobInfoSize,	METH_VARARGS },
		{ "GetMobInfoData",	wikiGetMobInfoData,	METH_VARARGS },

		{ "ReadData",	wikiReadData,	METH_VARARGS },

		{ "GetRefineMaxLevel",	wikiGetRefineMaxLevel,	METH_VARARGS },

		{ "GetItemDropFromChest",	wikiGetItemDropFromChest,	METH_VARARGS },
		{ "GetItemDropFromMonster",	wikiGetItemDropFromMonster,	METH_VARARGS },
		{ "GetCubeSize",	wikiGetCubeSize,	METH_VARARGS },
		{ "GetCubeData",	wikiGetCubeData,	METH_VARARGS },

		{ NULL, NULL, NULL },
	};
	PyObject* poModule = Py_InitModule("wiki", s_methods);
}
#endif

