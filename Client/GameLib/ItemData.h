#pragma once

//        Icon, Model (droped on ground), Game Data

#include "../eterLib/GrpSubImage.h"
#include "../eterGrnLib/Thing.h"
#include "GameLibDefines.h"
#include "../UserInterface/Locale_inc.h"

class CItemData
{
	public:
		enum
		{
			ITEM_NAME_MAX_LEN = 65,
			ITEM_LIMIT_MAX_NUM = 2,
			ITEM_VALUES_MAX_NUM = 6,
			ITEM_SMALL_DESCR_MAX_LEN = 256,
#if defined(ENABLE_ITEM_APPLY4)
			ITEM_APPLY_MAX_NUM = 4,
#else
			ITEM_APPLY_MAX_NUM = 3,
#endif
			ITEM_SOCKET_MAX_NUM = 3,
#ifdef __UNIMPLEMENTED__
			ITEM_PICK_MAX_LEVEL = 9,
			ITEM_ROD_MAX_LEVEL = 20,
#endif
		};

#ifdef ENABLE_SOULBIND_SYSTEM
		enum ESealBind
		{
			SEAL_BIND_FLAG_DROP,
			SEAL_BIND_FLAG_UPGRADE,
			SEAL_BIND_FLAG_SELL,
			SEAL_BIND_FLAG_ENCHANT,
			SEAL_BIND_FLAG_TRADE,
			SEAL_BIND_FLAG_UNSEAL,
			SEAL_BIND_FLAG_MAX,
		};

		enum ESealDate
		{
			SEAL_DATE_DEFAULT_TIMESTAMP = 0, // 2015/11/12 it's -1
			SEAL_DATE_UNLIMITED_TIMESTAMP = -1, // 2015/11/12 it doesn't exist
		};

		enum ESealItem
		{
			SEAL_ITEM_BINDING_VNUM = 50263,
			SEAL_ITEM_UNBINDING_VNUM = 50264,
		};
#endif

#ifdef __UNIMPLEMENTED__
		enum EPetData
		{
			EGG_USE_SUCCESS = 0,
			EGG_USE_FAILED_TIMEOVER = 2,
			EGG_USE_FAILED_BECAUSE_NAME = 1,
			GROWTH_PET_ITEM_USE_COOL_TIME = 1,
			PET_EGG_USE_TRUE = 0,
			PET_EGG_USE_FAILED_BECAUSE_TRADING = 1,
			PET_EGG_USE_FAILED_BECAUSE_SHOP_OPEN = 2,
			PET_EGG_USE_FAILED_BECAUSE_MALL_OPEN = 3,
			PET_EGG_USE_FAILED_BECAUSE_SAFEBOX_OPEN = 4,
			PET_HATCHING_MONEY = 100000,
			PET_NAME_MAX_SIZE = 20,
			PET_NAME_MIN_SIZE = 4,
		};
#endif

		enum EItemType
		{
			ITEM_TYPE_NONE,					// 0 ~ 1 무기
			ITEM_TYPE_WEAPON,				// 1 ~ 2 갑옷
			ITEM_TYPE_ARMOR,				// 2 ~ 3 아이템 사용
			ITEM_TYPE_USE,					// 3 ~ 4
			ITEM_TYPE_AUTOUSE,				// 4 ~ 5
			ITEM_TYPE_MATERIAL,				// 5 ~ 6 스페셜 아이템
			ITEM_TYPE_SPECIAL,				// 6 ~ 7
			ITEM_TYPE_TOOL,					// 7 ~ 8 복권
			ITEM_TYPE_LOTTERY,				// 8 ~ 9 돈
			ITEM_TYPE_ELK,					// 9 ~ 10
			ITEM_TYPE_METIN,				// 10 ~ 11
			ITEM_TYPE_CONTAINER,			// 11 ~ 12 낚시
			ITEM_TYPE_FISH,					// 12 ~ 13
			ITEM_TYPE_ROD,					// 13 ~ 14
			ITEM_TYPE_RESOURCE,				// 14 ~ 15
			ITEM_TYPE_CAMPFIRE,				// 15 ~ 16
			ITEM_TYPE_UNIQUE,				// 16 ~ 17
			ITEM_TYPE_SKILLBOOK,			// 17 ~ 18
			ITEM_TYPE_QUEST,				// 18 ~ 19
			ITEM_TYPE_POLYMORPH,			// 19 ~ 20 보물상자
			ITEM_TYPE_TREASURE_BOX,			// 20 ~ 21 보물상자 열쇠
			ITEM_TYPE_TREASURE_KEY,			// 21 ~ 22
			ITEM_TYPE_SKILLFORGET,			// 22 ~ 23
			ITEM_TYPE_GIFTBOX,				// 23 ~ 24
			ITEM_TYPE_PICK,					// 24 ~ 25 머리
			ITEM_TYPE_HAIR,					// 25 ~ 26 토템
			ITEM_TYPE_TOTEM,				// 26 ~ 27 생성될때 랜덤하게 속성이 붙는 약물
			ITEM_TYPE_BLEND,				// 27 ~ 28 코스츔 아이템 (2011년 8월 추가된 코스츔 시스템용 아이템)
			ITEM_TYPE_COSTUME,				// 28 ~ 29 용혼석
			ITEM_TYPE_DS,					// 29 ~ 30 특수한 용혼석 (DS_SLOT에 착용하는 UNIQUE 아이템이라 생각하면 됨)
			ITEM_TYPE_SPECIAL_DS,			// 30 ~ 31 추출도구.
			ITEM_TYPE_EXTRACT,				// 31 ~ 32 ?? 명도전??
			ITEM_TYPE_SECONDARY_COIN,		// 32 ~ 33 반지
			ITEM_TYPE_RING,					// 33 ~ 34
			ITEM_TYPE_BELT,					// 34 ~ 35 벨트
			ITEM_TYPE_CHEQUE,				// 35 ~ 36 won

			ITEM_TYPE_GACHA,				// 36 ~ 37 gacha

			ITEM_TYPE_PET,					// 37 ~ 38 pet
			ITEM_TYPE_SOUL,					// 38 ~ 39 soul
			ITEM_TYPE_MEDIUM,				// 39 ~ 40 medium
			ITEM_TYPE_PASSIVE,				// 40 ~ 41 passive
			ITEM_TYPE_MERCENARY,			// 41 ~ 42 mercenary
			ITEM_TYPE_BUFFI,
			ITEM_TYPE_MAX_NUM,
		};

		enum EDSSDuration
		{
			MIN_INFINITE_DURATION = 100 * 24 * 60 * 60,
			MAX_INFINITE_DURATION = 60 * 365 * 24 * 60 * 60,
		};

		enum EPetSubTypes
		{
			PET_LEVELABLE,
			PET_EGG,
			PET_TRANSPORTBOX,
			PET_PROTEIN,
			PET_CHANGE_NAME_ITEM,
			PET_DEW,
			PET_SKILL,
			PET_PRIMIUM_FEEDSTUFF,
			PET_ATTR_CHANGE,
			PET_ATTR_DETERMINE,
			PET_EXPFOOD_PER,
			PET_SKILL_DEL_BOOK,
			PET_SKILL_ALL_DEL_BOOK,
			PET_EXPFOOD,
			PET_FEEDSTUFF,
		};

		enum EWeaponSubTypes
		{
			WEAPON_SWORD,		//0
			WEAPON_DAGGER,		//1
			WEAPON_BOW,			//2
			WEAPON_TWO_HANDED,	//3
			WEAPON_BELL,		//4
			WEAPON_FAN,			//5
			WEAPON_ARROW,		//6
			WEAPON_MOUNT_SPEAR,	//7
#ifdef ENABLE_WOLFMAN_CHARACTER
			WEAPON_CLAW = 8,	//8
#endif
#ifdef ENABLE_QUIVER_SYSTEM
			WEAPON_QUIVER = 9,	//9
#endif
#ifdef __UNIMPLEMENTED__
			WEAPON_BOUQUET = 10,//10
#endif
			WEAPON_NUM_TYPES,	//11

			WEAPON_NONE = WEAPON_NUM_TYPES+1,
		};

		enum EMaterialSubTypes
		{
			MATERIAL_LEATHER,
			MATERIAL_BLOOD,
			MATERIAL_ROOT,
			MATERIAL_NEEDLE,
			MATERIAL_JEWEL,
			MATERIAL_DS_REFINE_NORMAL,
			MATERIAL_DS_REFINE_BLESSED,
			MATERIAL_DS_REFINE_HOLLY,
#if defined(ENABLE_DS_CHANGE_ATTR)
			MATERIAL_DS_CHANGE_ATTR,
#endif
		};

#ifdef ENABLE_SPECIAL_COSTUME_ATTR
		enum ECostumeAttrLimit
		{
			SPECIAL_ATTR_COSTUME_BODY_LIMIT = 3,
			SPECIAL_ATTR_COSTUME_HAIR_LIMIT = 3,
			SPECIAL_ATTR_COSTUME_WEAPON_LIMIT = 3,
		};
#endif

		enum EArmorSubTypes
		{
			ARMOR_BODY,
			ARMOR_HEAD,
			ARMOR_SHIELD,
			ARMOR_WRIST,
			ARMOR_FOOTS,
		    ARMOR_NECK,
			ARMOR_EAR,
#ifdef ENABLE_PENDANT_SYSTEM
			ARMOR_PENDANT,	//7
#endif
#ifdef ENABLE_GLOVE_SYSTEM
			ARMOR_GLOVE,	//8
#endif
#ifdef __PENDANT__
			ARMOR_PENDANT_FIRE,
			ARMOR_PENDANT_ICE,
			ARMOR_PENDANT_THUNDER,
			ARMOR_PENDANT_WIND,
			ARMOR_PENDANT_EARTH,
			ARMOR_PENDANT_DARK,
			ARMOR_PENDANT_SOUL,
#endif
			ARMOR_NUM_TYPES
		};

		enum ECostumeSubTypes
		{
			COSTUME_BODY,
			COSTUME_HAIR,
#ifdef ENABLE_MOUNT_COSTUME_SYSTEM
			COSTUME_MOUNT	= 2,		//2
#endif
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
			COSTUME_ACCE	= 3,		//3
#endif
#ifdef ENABLE_WEAPON_COSTUME_SYSTEM
			COSTUME_WEAPON	= 4,		//4
#endif
			COSTUME_PET,
			COSTUME_ACCE_SKIN,
			COSTUME_MOUNT_SKIN,
			COSTUME_NORMAL_PET_SKIN,
			COSTUME_NUM_TYPES,
		};

		enum EBuffiSubTypes
		{
			BUFFI_SCROLL,
			BUFFI_NAME_SCROLL,
		};

		enum EUseSubTypes
		{
			USE_POTION,					// 0
			USE_TALISMAN,
			USE_TUNING,
			USE_MOVE,
			USE_TREASURE_BOX,
			USE_MONEYBAG,
			USE_BAIT,
			USE_ABILITY_UP,
			USE_AFFECT,
			USE_CREATE_STONE,
			USE_SPECIAL,				// 10
			USE_POTION_NODELAY,
			USE_CLEAR,
			USE_INVISIBILITY,
			USE_DETACHMENT,
			USE_BUCKET,
			USE_POTION_CONTINUE,
			USE_CLEAN_SOCKET,
			USE_CHANGE_ATTRIBUTE,
			USE_ADD_ATTRIBUTE,
			USE_ADD_ACCESSORY_SOCKET,	// 20
			USE_PUT_INTO_ACCESSORY_SOCKET,
			USE_ADD_ATTRIBUTE2,
			USE_RECIPE,
			USE_CHANGE_ATTRIBUTE2,
			USE_BIND,
			USE_UNBIND,
			USE_TIME_CHARGE_PER,
			USE_TIME_CHARGE_FIX,				// 28
			USE_PUT_INTO_BELT_SOCKET,
			USE_PUT_INTO_RING_SOCKET,
#ifdef ENABLE_USE_COSTUME_ATTR
			USE_CHANGE_COSTUME_ATTR,			// 31
			USE_RESET_COSTUME_ATTR,				// 32
#endif
		};

		enum EDragonSoulSubType
		{
			DS_SLOT1,
			DS_SLOT2,
			DS_SLOT3,
			DS_SLOT4,
			DS_SLOT5,
			DS_SLOT6,
			DS_SLOT_NUM_TYPES = 6,
		};

		enum EMetinSubTypes
		{
			METIN_NORMAL,
			METIN_GOLD,
		};

		enum ELimitTypes
		{
			LIMIT_NONE,
			LIMIT_LEVEL,
			LIMIT_STR,
			LIMIT_DEX,
			LIMIT_INT,
			LIMIT_CON,
			LIMIT_PCBANG,						//deprecated
			LIMIT_REAL_TIME,
			LIMIT_REAL_TIME_START_FIRST_USE,
			LIMIT_TIMER_BASED_ON_WEAR,
			LIMIT_NEWWORLD_LEVEL,				//10
			LIMIT_MAX_NUM
		};

		enum EItemAntiFlag
		{
			ITEM_ANTIFLAG_FEMALE        = (1 << 0),
			ITEM_ANTIFLAG_MALE          = (1 << 1),
			ITEM_ANTIFLAG_WARRIOR       = (1 << 2),
			ITEM_ANTIFLAG_ASSASSIN      = (1 << 3),
			ITEM_ANTIFLAG_SURA          = (1 << 4),
			ITEM_ANTIFLAG_SHAMAN        = (1 << 5),
			ITEM_ANTIFLAG_GET           = (1 << 6),
			ITEM_ANTIFLAG_DROP          = (1 << 7),
			ITEM_ANTIFLAG_SELL          = (1 << 8),
			ITEM_ANTIFLAG_EMPIRE_A      = (1 << 9),
			ITEM_ANTIFLAG_EMPIRE_B      = (1 << 10),
			ITEM_ANTIFLAG_EMPIRE_R      = (1 << 11),
			ITEM_ANTIFLAG_SAVE          = (1 << 12),
			ITEM_ANTIFLAG_GIVE          = (1 << 13),
			ITEM_ANTIFLAG_PKDROP        = (1 << 14),
			ITEM_ANTIFLAG_STACK         = (1 << 15),
			ITEM_ANTIFLAG_MYSHOP        = (1 << 16),
			ITEM_ANTIFLAG_SAFEBOX		= (1 << 17),
#ifdef ENABLE_WOLFMAN_CHARACTER
			ITEM_ANTIFLAG_WOLFMAN		= (1 << 18),
#endif
		};

		enum EItemFlag
		{
			ITEM_FLAG_REFINEABLE        = (1 << 0),
			ITEM_FLAG_SAVE              = (1 << 1),
			ITEM_FLAG_STACKABLE         = (1 << 2),
			ITEM_FLAG_COUNT_PER_1GOLD   = (1 << 3),
			ITEM_FLAG_SLOW_QUERY        = (1 << 4),
			ITEM_FLAG_UNIQUE            = (1 << 5),
			ITEM_FLAG_MAKECOUNT			= (1 << 6),
			ITEM_FLAG_IRREMOVABLE		= (1 << 7),
			ITEM_FLAG_CONFIRM_WHEN_USE	= (1 << 8),
			ITEM_FLAG_QUEST_USE         = (1 << 9),
			ITEM_FLAG_QUEST_USE_MULTIPLE= (1 << 10),
			ITEM_FLAG_QUEST_GIVE		= (1 << 11),    // UNUSED03
			ITEM_FLAG_LOG               = (1 << 12),
			ITEM_FLAG_APPLICABLE		= (1 << 13),
#ifdef __TIME_STACKEBLE__
			ITEM_FLAG_TIME_STACKEBLE = (1 << 14),
#endif
		};

		enum EWearPositions
		{
			WEAR_BODY,          // 0
			WEAR_HEAD,          // 1
			WEAR_FOOTS,         // 2
			WEAR_WRIST,         // 3
			WEAR_WEAPON,        // 4
			WEAR_NECK,          // 5
			WEAR_EAR,           // 6
			WEAR_UNIQUE1,       // 7
			WEAR_UNIQUE2,       // 8
			WEAR_ARROW,         // 9
			WEAR_SHIELD,        // 10

			WEAR_ABILITY1,  // 11
			WEAR_ABILITY2,  // 12
			WEAR_ABILITY3,  // 13
			WEAR_ABILITY4,  // 14
			WEAR_ABILITY5,  // 15
			WEAR_ABILITY6,  // 16
			WEAR_ABILITY7,  // 17
			WEAR_ABILITY8,  // 18
			WEAR_COSTUME_BODY,	// 19
			WEAR_COSTUME_HAIR,	// 20 WEAR 200

#ifdef ENABLE_MOUNT_COSTUME_SYSTEM
			WEAR_COSTUME_MOUNT,	// 21
#endif

#ifdef ENABLE_ACCE_COSTUME_SYSTEM
			WEAR_COSTUME_ACCE,	// 22 WEAR 202
#endif

			WEAR_BELT,			// 23 WEAR 203

#ifdef ENABLE_WEAPON_COSTUME_SYSTEM
			WEAR_COSTUME_WEAPON,// 24 WEAR 204
#endif

			WEAR_PENDANT,
			WEAR_GLOVE,

			WEAR_RING1,
			WEAR_RING2,
			WEAR_PET,
			WEAR_NORMAL_PET, // WEAR 210

			WEAR_COSTUME_ACCE_SKIN,
			WEAR_COSTUME_MOUNT_SKIN,
			WEAR_COSTUME_NORMAL_PET_SKIN,

			WEAR_BUFFI_BODY,
			WEAR_BUFFI_HEAD,
			WEAR_BUFFI_WEAPON,
			WEAR_BUFFI_SASH,

			WEAR_BUFFI_RING_0,
			WEAR_BUFFI_RING_1,
			WEAR_BUFFI_RING_2, // WEAR 220
#ifdef __PENDANT__
			WEAR_PENDANT_FIRE,
			WEAR_PENDANT_ICE,
			WEAR_PENDANT_THUNDER,
			WEAR_PENDANT_WIND,
			WEAR_PENDANT_DARK,
			WEAR_PENDANT_EARTH,
			WEAR_PENDANT_SOUL_FIRST,
			WEAR_PENDANT_SOUL_SECOND,
#endif
			WEAR_MAX_NUM = 300, // don't change or you will mess special inventory for players !!!!	
		};

		enum EItemWearableFlag
		{
			WEARABLE_BODY = (1 << 0),
			WEARABLE_HEAD = (1 << 1),
			WEARABLE_FOOTS = (1 << 2),
			WEARABLE_WRIST = (1 << 3),
			WEARABLE_WEAPON = (1 << 4),
			WEARABLE_NECK = (1 << 5),
			WEARABLE_EAR = (1 << 6),
			WEARABLE_UNIQUE = (1 << 7),
			WEARABLE_ARROW = (1 << 8),
			WEARABLE_SHIELD = (1 << 9),
			WEARABLE_ABILITY = (1 << 10),
			WEARABLE_BUFFI_1 = (1 << 11),
			WEARABLE_BUFFI_2 = (1 << 12),
			WEARABLE_BUFFI_3 = (1 << 13),
			WEARABLE_HAIR = (1 << 14),
			WEARABLE_PENDANT = (1 << 15),
			WEARABLE_GLOVE = (1 << 16),
			WEARABLE_RING1 = (1 << 17),
			WEARABLE_RING2 = (1 << 18),
		};

		enum EApplyTypes
		{
			APPLY_NONE,                 // 0
			APPLY_MAX_HP,               // 1
			APPLY_MAX_SP,               // 2
			APPLY_CON,                  // 3
			APPLY_INT,                  // 4
			APPLY_STR,                  // 5
			APPLY_DEX,                  // 6
			APPLY_ATT_SPEED,            // 7
			APPLY_MOV_SPEED,            // 8
			APPLY_CAST_SPEED,           // 9
			APPLY_HP_REGEN,             // 10
			APPLY_SP_REGEN,             // 11
			APPLY_POISON_PCT,           // 12
			APPLY_STUN_PCT,             // 13
			APPLY_SLOW_PCT,             // 14
			APPLY_CRITICAL_PCT,         // 15
			APPLY_PENETRATE_PCT,        // 16
			APPLY_ATTBONUS_HUMAN,       // 17
			APPLY_ATTBONUS_ANIMAL,      // 18
			APPLY_ATTBONUS_ORC,         // 19
			APPLY_ATTBONUS_MILGYO,      // 20
			APPLY_ATTBONUS_UNDEAD,      // 21
			APPLY_ATTBONUS_DEVIL,       // 22
			APPLY_STEAL_HP,             // 23
			APPLY_STEAL_SP,             // 24
			APPLY_MANA_BURN_PCT,        // 25
			APPLY_DAMAGE_SP_RECOVER,    // 26
			APPLY_BLOCK,                // 27
			APPLY_DODGE,                // 28
			APPLY_RESIST_SWORD,         // 29
			APPLY_RESIST_TWOHAND,       // 30
			APPLY_RESIST_DAGGER,        // 31
			APPLY_RESIST_BELL,          // 32
			APPLY_RESIST_FAN,           // 33
			APPLY_RESIST_BOW,           // 34
			APPLY_RESIST_FIRE,          // 35
			APPLY_RESIST_ELEC,          // 36
			APPLY_RESIST_MAGIC,         // 37
			APPLY_RESIST_WIND,          // 38
			APPLY_REFLECT_MELEE,        // 39
			APPLY_REFLECT_CURSE,        // 40
			APPLY_POISON_REDUCE,        // 41
			APPLY_KILL_SP_RECOVER,      // 42
			APPLY_EXP_DOUBLE_BONUS,     // 43
			APPLY_GOLD_DOUBLE_BONUS,    // 44
			APPLY_ITEM_DROP_BONUS,      // 45
			APPLY_POTION_BONUS,         // 46
			APPLY_KILL_HP_RECOVER,      // 47
			APPLY_IMMUNE_STUN,          // 48
			APPLY_IMMUNE_SLOW,          // 49
			APPLY_IMMUNE_FALL,          // 50
			APPLY_SKILL,                // 51
			APPLY_BOW_DISTANCE,         // 52
			APPLY_ATT_GRADE_BONUS,            // 53
			APPLY_DEF_GRADE_BONUS,            // 54
			APPLY_MAGIC_ATT_GRADE,      // 55
			APPLY_MAGIC_DEF_GRADE,      // 56
			APPLY_CURSE_PCT,            // 57
			APPLY_MAX_STAMINA,			// 58
			APPLY_ATT_BONUS_TO_WARRIOR, // 59
			APPLY_ATT_BONUS_TO_ASSASSIN,// 60
			APPLY_ATT_BONUS_TO_SURA,    // 61
			APPLY_ATT_BONUS_TO_SHAMAN,  // 62
			APPLY_ATT_BONUS_TO_MONSTER, // 63
			APPLY_MALL_ATTBONUS,
			APPLY_MALL_DEFBONUS,
			APPLY_MALL_EXPBONUS,
			APPLY_MALL_ITEMBONUS,
			APPLY_MALL_GOLDBONUS,
			APPLY_MAX_HP_PCT,
			APPLY_MAX_SP_PCT,
			APPLY_SKILL_DAMAGE_BONUS,
			APPLY_NORMAL_HIT_DAMAGE_BONUS,
			APPLY_SKILL_DEFEND_BONUS,
			APPLY_NORMAL_HIT_DEFEND_BONUS,
			APPLY_EXTRACT_HP_PCT,		//75
			APPLY_PC_BANG_EXP_BONUS,		//76
			APPLY_PC_BANG_DROP_BONUS,		//77
			APPLY_RESIST_WARRIOR,			//78
			APPLY_RESIST_ASSASSIN ,			//79
			APPLY_RESIST_SURA,				//80
			APPLY_RESIST_SHAMAN,			//81
			APPLY_ENERGY,					//82
			APPLY_DEF_GRADE,
			APPLY_COSTUME_ATTR_BONUS,
			APPLY_MAGIC_ATTBONUS_PER,
			APPLY_MELEE_MAGIC_ATTBONUS_PER,

			APPLY_RESIST_ICE,
			APPLY_RESIST_EARTH,
			APPLY_RESIST_DARK,

			APPLY_ANTI_CRITICAL_PCT,
			APPLY_ANTI_PENETRATE_PCT,

#ifdef ENABLE_WOLFMAN_CHARACTER
			APPLY_BLEEDING_REDUCE			= 92,	//92
			APPLY_BLEEDING_PCT				= 93,	//93
			APPLY_ATT_BONUS_TO_WOLFMAN		= 94,	//94
			APPLY_RESIST_WOLFMAN			= 95,	//95
			APPLY_RESIST_CLAW				= 96,	//96
#endif

#ifdef ENABLE_ACCE_COSTUME_SYSTEM
			APPLY_ACCEDRAIN_RATE			= 97,	//97
#endif

#ifdef ENABLE_MAGIC_REDUCTION_SYSTEM
			APPLY_RESIST_MAGIC_REDUCTION	= 98,	//98
#endif

			APPLY_ENCHANT_ELECT				= 99,
			APPLY_ENCHANT_FIRE				= 100,
			APPLY_ENCHANT_ICE				= 101,
			APPLY_ENCHANT_WIND				= 102,
			APPLY_ENCHANT_EARTH				= 103,
			APPLY_ENCHANT_DARK				= 104,

			APPLY_ATTBONUS_CZ				= 105,
			APPLY_ATTBONUS_INSECT			= 106,
			APPLY_ATTBONUS_DESERT			= 107,
			APPLY_ATTBONUS_SWORD			= 108,
			APPLY_ATTBONUS_TWOHAND			= 109,
			APPLY_ATTBONUS_DAGGER			= 110,
			APPLY_ATTBONUS_BELL				= 111,
			APPLY_ATTBONUS_FAN				= 112,
			APPLY_ATTBONUS_BOW				= 113,
#ifdef ENABLE_WOLFMAN_CHARACTER
			APPLY_ATTBONUS_CLAW				= 114,
#endif

			APPLY_RESIST_HUMAN				= 115,

			APPLY_ATTBONUS_BOSS,
			APPLY_RESIST_MONSTER,
			APPLY_RESIST_BOSS,
			APPLY_CRITICAL_DAMAGE_PVM,
			APPLY_RESIST_RACES,
			APPLY_ATTBONUS_STONE,
			APPLY_ATTBONUS_DUNGEON,

			APPLY_PARTY_ATTACKER_BONUS,
			APPLY_PARTY_HASTE_BONUS,
			APPLY_PARTY_TANKER_BONUS,
			APPLY_PARTY_DEFENDER_BONUS,
			APPLY_PARTY_BUFFER_BONUS,
			APPLY_PARTY_SKILL_MASTER_BONUS,
			APPLY_RESIST_NORMAL_DAMAGE,
			MAX_APPLY_NUM,
		};

		enum EImmuneFlags
		{
			IMMUNE_PARA         = (1 << 0),
			IMMUNE_CURSE        = (1 << 1),
			IMMUNE_STUN         = (1 << 2),
			IMMUNE_SLEEP        = (1 << 3),
			IMMUNE_SLOW         = (1 << 4),
			IMMUNE_POISON       = (1 << 5),
			IMMUNE_TERROR       = (1 << 6),
		};

#pragma pack(push)
#pragma pack(1)
		typedef struct SItemLimit
		{
			BYTE bType;
			long lValue;
		} TItemLimit;

		typedef struct SItemApply
		{
			BYTE bType;
			long lValue;
		} TItemApply;

		typedef struct SItemTable
		{
			DWORD dwVnum;
			DWORD dwVnumRange;
			char szName[ITEM_NAME_MAX_LEN + 1];
			char szLocaleName[ITEM_NAME_MAX_LEN + 1];
			BYTE bType;
			BYTE bSubType;

			BYTE bWeight;
			BYTE bSize;

			DWORD dwAntiFlags;
			DWORD dwFlags;
			DWORD dwWearFlags;
			DWORD dwImmuneFlag;

			DWORD dwIBuyItemPrice;
			DWORD dwISellItemPrice;

			TItemLimit aLimits[ITEM_LIMIT_MAX_NUM];
			TItemApply aApplies[ITEM_APPLY_MAX_NUM];
			long alValues[ITEM_VALUES_MAX_NUM];
			long alSockets[ITEM_SOCKET_MAX_NUM];
			DWORD dwRefinedVnum;
			WORD wRefineSet;
			BYTE bAlterToMagicItemPct;
			BYTE bSpecular;
			BYTE bGainSocketPct;
		} TItemTable;

#ifdef ENABLE_ACCE_COSTUME_SYSTEM
		struct SScaleInfo
		{
			float fScaleX, fScaleY, fScaleZ;
			float fPositionX, fPositionY, fPositionZ;
		};

		typedef struct SScaleTable
		{
			SScaleInfo tInfo[10];
		} TScaleTable;
#endif

#pragma pack(pop)

	public:
		CItemData();
		virtual ~CItemData();

		void Clear();
		void SetSummary(const std::string& c_rstSumm);
		void SetSummary2(const std::string& c_rstSumm);
		void SetSummary3(const std::string& c_rstSumm);
		void SetSummary4(const std::string& c_rstSumm);
		void SetDescription(const std::string& c_rstDesc);

		CGraphicThing * GetModelThing();
		CGraphicThing * GetSubModelThing();
		CGraphicThing * GetDropModelThing();
		CGraphicSubImage * GetIconImage();

		DWORD GetLODModelThingCount();
		BOOL GetLODModelThingPointer(DWORD dwIndex, CGraphicThing ** ppModelThing);

		DWORD GetAttachingDataCount();
		BOOL GetCollisionDataPointer(DWORD dwIndex, const NRaceData::TAttachingData ** c_ppAttachingData);
		BOOL GetAttachingDataPointer(DWORD dwIndex, const NRaceData::TAttachingData ** c_ppAttachingData);

		/////
		const TItemTable*	GetTable() const;
		DWORD GetIndex() const;
		const char * GetName() const;
		const char * GetDescription() const;
		const char * GetSummary() const;
		const char* GetSummary2() const;
		const char* GetSummary3() const;
		const char* GetSummary4() const;
		BYTE GetType() const;
		BYTE GetSubType() const;
		UINT GetRefine() const;
		const char* GetUseTypeString() const;
		DWORD GetWeaponType() const;
		BYTE GetSize() const;
		BOOL IsAntiFlag(DWORD dwFlag) const;
		BOOL IsFlag(DWORD dwFlag) const;
		BOOL IsWearableFlag(DWORD dwFlag) const;
		BOOL HasNextGrade() const;

#ifdef ENABLE_WIKI
		WORD GetRefinedSet() const;
		WORD GetRefinedVnum() const;
#endif

		DWORD GetWearFlags() const;
		DWORD GetIBuyItemPrice() const;
		DWORD GetISellItemPrice() const;
		BOOL GetLimit(BYTE byIndex, TItemLimit * pItemLimit) const;
		BOOL GetApply(BYTE byIndex, TItemApply * pItemApply) const;
		long GetValue(BYTE byIndex) const;
		long GetSocket(BYTE byIndex) const;
		long SetSocket(BYTE byIndex,DWORD value);
		int GetSocketCount() const;
		DWORD GetIconNumber() const;

		UINT	GetSpecularPoweru() const;
		float	GetSpecularPowerf() const;

		/////

		BOOL IsEquipment() const;

		/////

		//BOOL LoadItemData(const char * c_szFileName);
		void SetDefaultItemData(const char * c_szIconFileName, const char * c_szModelFileName  = NULL);
		void SetItemTableData(TItemTable * pItemTable);

#ifdef ENABLE_ACCE_COSTUME_SYSTEM
		void SetItemScale(const std::string strJob, const std::string strSex, const std::string strScaleX, const std::string strScaleY, const std::string strScaleZ, const std::string strPositionX, const std::string strPositionY, const std::string strPositionZ);
		bool GetItemScale(DWORD dwPos, float & fScaleX, float & fScaleY, float & fScaleZ, float & fPositionX, float & fPositionY, float & fPositionZ);
#endif

	protected:
		void __LoadFiles();
		void __SetIconImage(const char * c_szFileName);

	protected:
		std::string m_strModelFileName;
		std::string m_strSubModelFileName;
		std::string m_strDropModelFileName;
		std::string m_strIconFileName;
		std::string m_strDescription;
		std::string m_strSummary;
		std::string m_strSummary2;
		std::string m_strSummary3;
		std::string m_strSummary4;
		std::vector<std::string> m_strLODModelFileNameVector;

		CGraphicThing * m_pModelThing;
		CGraphicThing * m_pSubModelThing;
		CGraphicThing * m_pDropModelThing;
		CGraphicSubImage * m_pIconImage;
		std::vector<CGraphicThing *> m_pLODModelThingVector;

		NRaceData::TAttachingDataVector m_AttachingDataVector;
		DWORD		m_dwVnum;
		TItemTable m_ItemTable;
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
		TScaleTable	m_ScaleTable;
#endif

	public:
		static void DestroySystem();

		static CItemData* New();
		static void Delete(CItemData* pkItemData);

		static CMemoryPool<CItemData>		ms_kPool;
};
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
