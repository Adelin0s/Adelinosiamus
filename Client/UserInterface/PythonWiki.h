#pragma once

#ifdef ENABLE_WIKI
#include "../gamelib/ItemManager.h"
#include "../gamelib/ItemData.h"
#include "../gamelib/RaceData.h"
#include "PythonNonPlayer.h"

enum {
	MAX_REFINE_ITEM = 5,
};

typedef struct r_table {
	DWORD id;
	DWORD item_vnums[MAX_REFINE_ITEM];
	DWORD item_count[MAX_REFINE_ITEM];
	long long cost;
	//DWORD src_num;
	//DWORD result_vnum;
	DWORD prob;
	DWORD refine_count;
} refineTable;

typedef struct refine_map {
	DWORD	itemVnum;
	DWORD	level;
	refine_map(DWORD _vnum, DWORD _level) :itemVnum(_vnum), level(_level) {}
} character_data;

typedef struct special_map {
	DWORD	itemVnum;
	DWORD	count;
	special_map(DWORD _vnum, DWORD _count):itemVnum(_vnum),count(_count){}
} special_data;

constexpr DWORD bossChests[][2] = {
	{50118,0},
	{50254,0},
	{50073,2091},
	{50078,1304},
	{50079,2206},
	{50077,1901},
	{50076,2191},
	{50070,691},
	{38052,0},
	{54100,0},
	{54101,0},
	{54120,0},
	{350001,2092},
	{350002,1093},
	{350003,693},
	{50186,2598},
	{54700,2493},
	{50270,6193},
	{54702,6091},
	{54703,6191},
	{54704,6192},
	{54705,3965},
	{70445,6500},
	{70444,6501},
	{50081, 1091},
	{33033,2782},
};

constexpr DWORD eventChests[][2] = {
	{50011,0},
	//{50267,0},
	//{50268,0},
	//{50269,0},
};

constexpr DWORD ishopChests[][2] = {
	{83011,0},
	{83012,0},
	{83015,0},
	{83008,0},
	{83014,0},
	{83009,0},
};

constexpr DWORD alternativeChests[][2] = {
	{951042,0},
	{951043,0},
	{951044,0},
	{951045,0},
	{951040,0},
	{50033,0},
	{50259,0},
	{55009,0},
	{951078,0},
	{951072,0},
	{951071,0},
	{951070,0},
	{33028,0},
};

constexpr DWORD eventBoss[] = {
	1093,
	2493
};

const std::map<BYTE, std::vector<DWORD>> m_CostumeData = {

	{0, //Weapon
		{
			40129, 40132, 40130, 40131, 40134, 40133, 40101, 40104, 40102, 40103, 40105, 40106, 505004, 505003, 505006, 505005, 505007, 505008, 506010, 506011, 506012, 506013, 506014, 506015, 506016, 506017, 506018, 506019, 506020, 506021
		}
	},

	{1, //Armor
		{
			41775, 41777, 41311, 41312, 505001, 504003, 504009, 504005, 504001, 504007, 41798, 41800, 41670, 41672
		}
	},
	{2, //Hair
		{
			45511, 45513, 45147, 45148, 505002, 504004, 504010, 504006, 504002, 504008, 45534, 45536, 45336, 45338
		}
	},

	{3, //Sash
		{
			85001, 85002, 85003, 85004, 85005, 85006, 85007, 85008, 85011, 85012, 85013, 85014, 85015, 85016, 85017, 85018
		}
	},
	{4, //Costume sash
		{
			505011, 505012, 505013, 505014, 506026, 506027, 506028, 506029, 506030, 506031, 506032, 506033,
			86001, 86002, 86003, 86004,
			86005, 86006, 86007, 86008,	
			86011, 86012, 86013, 86014,
			86015, 86016, 86017, 86018,
			86021, 86022, 86023, 86024,
			86025, 86026, 86027, 86028,
			86031, 86032, 86033, 86034,
			86035, 86036, 86037, 86038,
			86041, 86042, 86043, 86044,
			86045, 86046, 86047, 86048,
			86051, 86052, 86053, 86054,
			86055, 86056, 86057, 86058
		}
	},
	{5, //Pet
		{
			53005, 53006, 53017, 506039, 506038, 506037, 506036, 506035, 506034, 53001
		}
	},
	{6, //Pet Skin
		{
			505010, 53271
		}
	},
	{7, //Mount
		{
			52001, 52002, 52039, 52042, 506040, 506041, 506042, 506043, 506044, 506045
		}
	},
	{8, //Mount Skin
		{
			505009, 506023, 506022, 506055
		}
	},
	{9, //Pet Level
		{
			55701, 55702, 55703, 55704, 55705, 55706, 55707, 55708, 55709, 55710, 55711
		}
	},
};

struct TSimpleItem
{
	DWORD vnum;
	WORD count;
};

struct cube_data
{
	TSimpleItem reward;
	TSimpleItem material[10];
	DWORD gold;
	DWORD gem;
	BYTE percent;
	DWORD mobIdx;
};

class CPythonWiki : public CSingleton <CPythonWiki>
{
public:
	CPythonWiki();
	virtual ~CPythonWiki();

	void	ReadData(const char* localeFile);
	bool	LoadItemTable(const char* c_szFileName);
	bool	LoadRefineTable(const char* c_szFileName);
	void	LoadItem(CItemData::TItemTable* item);
	void	LoadMonster(CPythonNonPlayer::TMobTable* monster);
	void	ListReverse();

	bool	ReadSpecialDropItemFile(const char* c_pszFileName);
	bool	ReadMobDropItemFile(const char* c_pszFileName);

	const refineTable* GetRefineItem(DWORD index);

	BYTE	GetRefineLevel(DWORD itemVnum, DWORD itemType, DWORD itemSubType);
	bool	ItemBlackList(DWORD itemVnum, DWORD itemType, DWORD itemSubType);

	bool	BlackListMonster(DWORD mobVnum);

	bool	LowLevelBoss(DWORD mobVnum);
	bool	HighLevelBoss(DWORD mobVnum);
	bool	PreBoss(DWORD mobVnum);
	bool	DungeonBoss(DWORD mobVnum);
	bool	WorldBoss(DWORD mobVnum);
	bool	Stones(DWORD mobVnum);
	bool	DungeonStones(DWORD mobVnum);

	bool	ReadCubeFile(const char* c_pszFileName);

	const std::unordered_map<DWORD, std::vector<special_data>> GetSpecialDrop() {return m_vecSpecialDrop;}
	const std::unordered_map<DWORD, std::vector<special_data>> GetMobDrop() {return m_vecMobDrop;}

	std::vector<character_data> m_vecBossCategory[5];
	std::vector<character_data> m_vecMonsterCategory[3];
	std::vector<character_data> m_vecStoneCategory[4];

	std::vector<cube_data> m_vecCubeCategory[11];


	std::vector<character_data> m_vecWeapon[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecArmor[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecHelmets[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecShields[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecEarrings[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecBracelet[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecNecklace[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecShoes[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecBelt[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecTalisman[CRaceData::JOB_MAX_NUM];
	std::vector<character_data> m_vecCrystal[CRaceData::JOB_MAX_NUM];

	std::unordered_map<DWORD, std::vector<special_data>> m_vecSpecialDrop;
	std::unordered_map<DWORD, std::vector<special_data>> m_vecMobDrop;

	bool	m_bLoaded;
	std::unordered_map<DWORD, refineTable> m_vecRefineTable;	
};
#endif
