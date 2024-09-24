#pragma once
#include "../GameLib/ItemData.h"

struct SAffects
{
	enum
	{
		AFFECT_MAX_NUM = 32,
	};

	SAffects() : dwAffects(0) {}
	SAffects(const DWORD & c_rAffects)
	{
		__SetAffects(c_rAffects);
	}
	int operator = (const DWORD & c_rAffects)
	{
		__SetAffects(c_rAffects);
	}

	BOOL IsAffect(BYTE byIndex)
	{
		return dwAffects & (1 << byIndex);
	}

	void __SetAffects(const DWORD & c_rAffects)
	{
		dwAffects = c_rAffects;
	}

	DWORD dwAffects;
};

extern std::string g_strGuildSymbolPathName;

constexpr DWORD c_Name_Max_Length = 64;
constexpr DWORD c_FileName_Max_Length = 128;
constexpr DWORD c_Short_Name_Max_Length = 32;

constexpr DWORD c_Inventory_Page_Column = 5;
constexpr DWORD c_Inventory_Page_Row = 9;
constexpr DWORD c_Inventory_Page_Size = c_Inventory_Page_Column*c_Inventory_Page_Row; // x*y
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
constexpr DWORD c_Inventory_Page_Count = 4;
#else
constexpr DWORD c_Inventory_Page_Count = 2;
#endif
#ifdef ENABLE_SPECIAL_INVENTORY_SYSTEM
constexpr DWORD c_Special_Inventory_Page_Size = 5 * 9; // x*y
const DWORD c_Special_Inventory_Page_Count = 5;
constexpr DWORD c_Special_ItemSlot_Count = c_Special_Inventory_Page_Size * c_Special_Inventory_Page_Count;
#endif
constexpr DWORD c_ItemSlot_Count = c_Inventory_Page_Size * c_Inventory_Page_Count;
constexpr DWORD c_Equipment_Count = 12;

const DWORD c_Equipment_Start = c_ItemSlot_Count;

const DWORD c_Equipment_Body = c_Equipment_Start + 0;
const DWORD c_Equipment_Head = c_Equipment_Start + 1;
const DWORD c_Equipment_Shoes = c_Equipment_Start + 2;
const DWORD c_Equipment_Wrist = c_Equipment_Start + 3;
const DWORD c_Equipment_Weapon = c_Equipment_Start + 4;
const DWORD c_Equipment_Neck = c_Equipment_Start + 5;
const DWORD c_Equipment_Ear = c_Equipment_Start + 6;
const DWORD c_Equipment_Unique1 = c_Equipment_Start + 7;
const DWORD c_Equipment_Unique2 = c_Equipment_Start + 8;
const DWORD c_Equipment_Arrow = c_Equipment_Start + 9;
const DWORD c_Equipment_Shield = c_Equipment_Start + 10;

// 새로 추가된 신규 반지 & 벨트
// 장착형 아이템에 할당할 수 있는 위치가 기존 장비, 채기랍 퀘스트 보상, 코스튬 시스템 등으로 인해서 공간이 잘려있다.
// 이게 다 채기랍 보상 버프를 장착아이템처럼 구현한 ㅅㄲ 때문에 난리났따... ㅆㅂ
//
// 정리하면, 기존 장비창들은 서버DB상 아이템 포지션이 90 ~ 102 이고,
// 2013년 초에 새로 추가되는 슬롯들은 111 ~ 부터 시작한다. 착용 장비에서 최대로 사용할 수 있는 값은 121 까지이고, 122부터는 용혼석에서 사용한다.
#ifdef ENABLE_NEW_EQUIPMENT_SYSTEM
///#if defined(ENABLE_MOUNT_COSTUME_SYSTEM) && defined(ENABLE_ACCE_COSTUME_SYSTEM) && defined(ENABLE_WEAPON_COSTUME_SYSTEM)
const DWORD c_New_Equipment_Start = c_Equipment_Start + 24;
const DWORD c_New_Equipment_Count = 5;
const DWORD c_Equipment_Ring1 = c_New_Equipment_Start + 0;
const DWORD c_Equipment_Ring2 = c_New_Equipment_Start + 1;
const DWORD c_Equipment_Belt = c_New_Equipment_Start + 2;
const DWORD c_Equipment_Pendant = c_New_Equipment_Start + 3;
#if defined(ENABLE_GLOVE_SYSTEM)
const DWORD c_Equipment_Glove = c_New_Equipment_Start + 4;
#endif
#endif

#ifdef __PENDANT__
const DWORD	c_EquipmentPendantFire = c_Equipment_Start + CItemData::WEAR_PENDANT_FIRE;
const DWORD	c_EquipmentPendantIce = c_Equipment_Start + CItemData::WEAR_PENDANT_ICE;
const DWORD	c_EquipmentPendantThunder = c_Equipment_Start + CItemData::WEAR_PENDANT_THUNDER;
const DWORD	c_EquipmentPendantWind = c_Equipment_Start + CItemData::WEAR_PENDANT_WIND;
const DWORD	c_EquipmentPendantDark = c_Equipment_Start + CItemData::WEAR_PENDANT_DARK;
const DWORD	c_EquipmentPendantEarth = c_Equipment_Start + CItemData::WEAR_PENDANT_EARTH;
const DWORD	c_EquipmentPendantFirst = c_Equipment_Start + CItemData::WEAR_PENDANT_SOUL_FIRST;
const DWORD	c_EquipmentPendantSecond = c_Equipment_Start + CItemData::WEAR_PENDANT_SOUL_SECOND;
#endif

enum EDragonSoulDeckType
{
	DS_DECK_1,
	DS_DECK_2,
	DS_DECK_MAX_NUM = 2,
};

enum EDragonSoulGradeTypes
{
	DRAGON_SOUL_GRADE_NORMAL,
	DRAGON_SOUL_GRADE_BRILLIANT,
	DRAGON_SOUL_GRADE_RARE,
	DRAGON_SOUL_GRADE_ANCIENT,
	DRAGON_SOUL_GRADE_LEGENDARY,
#ifdef ENABLE_DS_GRADE_MYTH
	DRAGON_SOUL_GRADE_MYTH,
#endif
	DRAGON_SOUL_GRADE_MAX,
};

enum EDragonSoulStepTypes
{
	DRAGON_SOUL_STEP_LOWEST,
	DRAGON_SOUL_STEP_LOW,
	DRAGON_SOUL_STEP_MID,
	DRAGON_SOUL_STEP_HIGH,
	DRAGON_SOUL_STEP_HIGHEST,
	DRAGON_SOUL_STEP_MAX,
};

#ifdef ENABLE_COSTUME_SYSTEM
const DWORD c_Costume_Slot_Start = c_Equipment_Start + 19;
const DWORD c_Costume_Slot_Body = c_Costume_Slot_Start + 0;
const DWORD c_Costume_Slot_Hair = c_Costume_Slot_Start + 1;

#ifdef ENABLE_MOUNT_COSTUME_SYSTEM
const DWORD c_Costume_Slot_Mount = c_Costume_Slot_Start + 2;
#endif

#ifdef ENABLE_ACCE_COSTUME_SYSTEM
const DWORD c_Costume_Slot_Acce = c_Costume_Slot_Start + 3;
#endif

#ifdef ENABLE_WEAPON_COSTUME_SYSTEM
const DWORD c_Costume_Slot_Weapon = c_Costume_Slot_Start + 4;
#endif

#ifdef ENABLE_NEW_PET_SYSTEM
const DWORD c_Slot_Pet = c_Costume_Slot_Start + 10;
const DWORD c_Slot_Normal_Pet = c_Costume_Slot_Start + 11;
#endif

const DWORD c_Slot_Acce_Skin = c_Costume_Slot_Start + 12;
const DWORD c_Slot_Mount_Skin = c_Costume_Slot_Start + 13;
const DWORD c_Slot_Normal_Pet_Skin = c_Costume_Slot_Start + 14;
#define COSTUME_SLOT_COUNT 9

#ifdef __BUFFI_SUPPORT__
const DWORD	c_Buffi_Slot_Body = c_Costume_Slot_Start + 15;
const DWORD	c_Buffi_Slot_Head = c_Costume_Slot_Start + 16;
const DWORD	c_Buffi_Slot_Weapon = c_Costume_Slot_Start + 17;
const DWORD	c_Buffi_Slot_Sash = c_Costume_Slot_Start + 18;
#ifdef __BUFFI_SHINING__
const DWORD	c_Buffi_Slot_ShiningWeapon = c_Costume_Slot_Start + 19;
const DWORD	c_Buffi_Slot_ShiningArmor = c_Costume_Slot_Start + 20;
#endif
const DWORD	c_Buffi_Slot_Ring0 = c_Costume_Slot_Start + CItemData::WEAR_BUFFI_RING_0;
const DWORD	c_Buffi_Slot_Ring1 = c_Costume_Slot_Start + CItemData::WEAR_BUFFI_RING_1;
const DWORD	c_Buffi_Slot_Ring2 = c_Costume_Slot_Start + CItemData::WEAR_BUFFI_RING_2;
#endif


const DWORD c_Costume_Slot_Count = COSTUME_SLOT_COUNT;
const DWORD c_Costume_Slot_End = c_Costume_Slot_Start + c_Costume_Slot_Count + 1;
#endif

const DWORD c_Wear_Max = CItemData::WEAR_MAX_NUM;
const DWORD c_DragonSoul_Equip_Start = c_ItemSlot_Count + c_Wear_Max;
const DWORD c_DragonSoul_Equip_Slot_Max = 6;
const DWORD c_DragonSoul_Equip_End = c_DragonSoul_Equip_Start + c_DragonSoul_Equip_Slot_Max * DS_DECK_MAX_NUM;

const DWORD c_DragonSoul_Equip_Reserved_Count = c_DragonSoul_Equip_Slot_Max * 3;

#ifdef ENABLE_NEW_EQUIPMENT_SYSTEM
const DWORD c_Belt_Inventory_Slot_Start = c_DragonSoul_Equip_End + c_DragonSoul_Equip_Reserved_Count;
const DWORD c_Belt_Inventory_Width = 4;
const DWORD c_Belt_Inventory_Height= 4;
const DWORD c_Belt_Inventory_Slot_Count = c_Belt_Inventory_Width * c_Belt_Inventory_Height;
const DWORD c_Belt_Inventory_Slot_End = c_Belt_Inventory_Slot_Start + c_Belt_Inventory_Slot_Count;
#endif

#ifdef ENABLE_SPECIAL_INVENTORY_SYSTEM
const DWORD c_Skill_Book_Inventory_Slot_Start = c_Belt_Inventory_Slot_End;
const DWORD c_Skill_Book_Inventory_Slot_Count = c_Special_ItemSlot_Count;
const DWORD c_Skill_Book_Inventory_Slot_End = c_Skill_Book_Inventory_Slot_Start + c_Skill_Book_Inventory_Slot_Count;

const DWORD c_Upgrade_Items_Inventory_Slot_Start = c_Skill_Book_Inventory_Slot_End;
const DWORD c_Upgrade_Items_Inventory_Slot_Count = c_Special_ItemSlot_Count;
const DWORD c_Upgrade_Items_Inventory_Slot_End = c_Upgrade_Items_Inventory_Slot_Start + c_Upgrade_Items_Inventory_Slot_Count;

const DWORD c_Stone_Inventory_Slot_Start = c_Upgrade_Items_Inventory_Slot_End;
const DWORD c_Stone_Inventory_Slot_Count = c_Special_ItemSlot_Count;
const DWORD c_Stone_Inventory_Slot_End = c_Stone_Inventory_Slot_Start + c_Stone_Inventory_Slot_Count;

const DWORD c_GiftBox_Inventory_Slot_Start = c_Stone_Inventory_Slot_End;
const DWORD c_GiftBox_Inventory_Slot_Count = c_Special_ItemSlot_Count;
const DWORD c_GiftBox_Inventory_Slot_End = c_GiftBox_Inventory_Slot_Start + c_GiftBox_Inventory_Slot_Count;

const DWORD c_Switch_Inventory_Slot_Start = c_GiftBox_Inventory_Slot_End;
const DWORD c_Switch_Inventory_Slot_Count = c_Special_ItemSlot_Count;
const DWORD c_Switch_Inventory_Slot_End = c_Switch_Inventory_Slot_Start + c_Switch_Inventory_Slot_Count;

const DWORD c_Costume_Inventory_Slot_Start = c_Switch_Inventory_Slot_End;
const DWORD c_Costume_Inventory_Slot_Count = c_Special_ItemSlot_Count;
const DWORD c_Costume_Inventory_Slot_End = c_Costume_Inventory_Slot_Start + c_Costume_Inventory_Slot_Count;
#endif



#ifdef ENABLE_SPECIAL_INVENTORY_SYSTEM
const DWORD c_Inventory_Count = c_Costume_Inventory_Slot_End;
#else
const DWORD c_Inventory_Count = c_Belt_Inventory_Slot_End;
#endif

const DWORD c_DragonSoul_Inventory_Start = 0;
const DWORD c_DragonSoul_Inventory_Box_Size = 32;
const DWORD c_DragonSoul_Inventory_Count = CItemData::DS_SLOT_NUM_TYPES * DRAGON_SOUL_GRADE_MAX * c_DragonSoul_Inventory_Box_Size;
const DWORD c_DragonSoul_Inventory_End = c_DragonSoul_Inventory_Start + c_DragonSoul_Inventory_Count;

enum ESlotType
{
	SLOT_TYPE_NONE,
	SLOT_TYPE_INVENTORY,
	SLOT_TYPE_SKILL,
	SLOT_TYPE_EMOTION,
	SLOT_TYPE_SHOP,
	SLOT_TYPE_EXCHANGE_OWNER,
	SLOT_TYPE_EXCHANGE_TARGET,
	SLOT_TYPE_QUICK_SLOT,
	SLOT_TYPE_SAFEBOX,
	SLOT_TYPE_PRIVATE_SHOP,
	SLOT_TYPE_MALL,
	SLOT_TYPE_DRAGON_SOUL_INVENTORY,
#ifdef ENABLE_SWITCHBOT
	SLOT_TYPE_SWITCHBOT,
#endif
#if defined(ENABLE_SPECIAL_INVENTORY_SYSTEM)
	SLOT_TYPE_SKILL_BOOK_INVENTORY,
	SLOT_TYPE_UPGRADE_ITEMS_INVENTORY,
	SLOT_TYPE_STONE_INVENTORY,
	SLOT_TYPE_GIFT_BOX_INVENTORY,
	SLOT_TYPE_SWITCH_INVENTORY,
	SLOT_TYPE_COSTUME_INVENTORY,
#endif

	SLOT_TYPE_MAX,
};

enum EWindows
{
	RESERVED_WINDOW,
	INVENTORY,
	EQUIPMENT,
	SAFEBOX,
	MALL,
	DRAGON_SOUL_INVENTORY,
	BELT_INVENTORY,
#ifdef ENABLE_SWITCHBOT
	SWITCHBOT,
#endif
#if defined(ENABLE_SPECIAL_INVENTORY_SYSTEM)
	SKILL_BOOK_INVENTORY,
	UPGRADE_ITEMS_INVENTORY,
	STONE_INVENTORY,
	GIFT_BOX_INVENTORY,
	SWITCH_INVENTORY,
	COSTUME_INVENTORY,
#endif
	GROUND,
	WINDOW_TYPE_MAX,
};

enum EDSInventoryMaxNum
{
	DS_INVENTORY_MAX_NUM = c_DragonSoul_Inventory_Count,
	DS_REFINE_WINDOW_MAX_NUM = 15,
};

#if defined(__BL_MOVE_COSTUME_ATTR__)
enum ECombSlotType
{
	COMB_WND_SLOT_MEDIUM,
	COMB_WND_SLOT_BASE,
	COMB_WND_SLOT_MATERIAL,
	COMB_WND_SLOT_RESULT,

	COMB_WND_SLOT_MAX
};
#endif

#if defined(ENABLE_DS_CHANGE_ATTR)
enum EDSRefineType
{
	DS_REFINE_TYPE_GRADE,
	DS_REFINE_TYPE_STEP,
	DS_REFINE_TYPE_STRENGTH,
	DS_REFINE_TYPE_CHANGE_ATTR,
	DS_REFINE_TYPE_MAX,
};
#endif

#pragma pack (push, 1)
#define WORD_MAX 0xffff

#ifdef WJ_ENABLE_TRADABLE_ICON
enum ETopWindowTypes
{
	ON_TOP_WND_NONE,					// 0
	ON_TOP_WND_SHOP,					// 1
	ON_TOP_WND_EXCHANGE,				// 1
	ON_TOP_WND_SAFEBOX,					// 3
	ON_TOP_WND_PRIVATE_SHOP,			// 4
	ON_TOP_WND_ITEM_COMB,				// 5
	ON_TOP_WND_PET_FEED,				// 6
	ON_TOP_WND_FISH_EVENT,				// 7
	ON_TOP_WND_MAILBOX,					// 8
	ON_TOP_WND_PET_ATTR_CHANGE,			// 9
	ON_TOP_WND_LUCKY_BOX,				// 10
	ON_TOP_WND_ATTR67,
	ON_TOP_WND_ACCE_COMBINE,			// 12
	ON_TOP_WND_ACCE_ABSORB,				// 13
	ON_TOP_WND_CHANGE_LOOK,				// 14

	ON_TOP_WND_MAX,
};
#endif

#ifdef ENABLE_SWITCHBOT
enum ESwitchbotValues
{
	SWITCHBOT_SLOT_COUNT = 6,
	SWITCHBOT_SLOT_COUNT_REAL = 5,
	SWITCHBOT_ALTERNATIVE_COUNT = 2,
	MAX_NORM_ATTR_NUM = 5,
};

enum EAttributeSet
{
	ATTRIBUTE_SET_WEAPON,
	ATTRIBUTE_SET_BODY,
	ATTRIBUTE_SET_WRIST,
	ATTRIBUTE_SET_FOOTS,
	ATTRIBUTE_SET_NECK,
	ATTRIBUTE_SET_HEAD,
	ATTRIBUTE_SET_SHIELD,
	ATTRIBUTE_SET_EAR,
	ATTRIBUTE_SET_GLOVE,
	ATTRIBUTE_SET_PENDANT,
	ATTRIBUTE_SET_PENDANT_SOUL,
	ATTRIBUTE_SET_ACCE_SKIN,
	ATTRIBUTE_SET_MAX_NUM
};

#endif

typedef struct SItemPos
{
	BYTE window_type;
	WORD cell;
    SItemPos ()
    {
		window_type =     INVENTORY;
		cell = WORD_MAX;
    }
	SItemPos (BYTE _window_type, WORD _cell)
    {
        window_type = _window_type;
        cell = _cell;
    }

  //  int operator=(const int _cell)
  //  {
		//window_type = INVENTORY;
  //      cell = _cell;
  //      return cell;
  //  }
	bool IsValidCell()
	{
		switch (window_type)
		{
		case INVENTORY:
		case SKILL_BOOK_INVENTORY:
		case UPGRADE_ITEMS_INVENTORY:
		case STONE_INVENTORY:
		case GIFT_BOX_INVENTORY:
			return cell < c_Inventory_Count;
			break;
		case EQUIPMENT:
			return cell < c_DragonSoul_Equip_End;
			break;
		case DRAGON_SOUL_INVENTORY:
			return cell < (DS_INVENTORY_MAX_NUM);
			break;
#ifdef ENABLE_SWITCHBOT
		case SWITCHBOT:
			return cell < SWITCHBOT_SLOT_COUNT;
			break;
#endif
		default:
			return false;
		}
	}
	bool IsEquipCell()
	{
		switch (window_type)
		{
		case INVENTORY:
		case EQUIPMENT:
			return (c_Equipment_Start + c_Wear_Max > cell) && (c_Equipment_Start <= cell);
			break;

		case BELT_INVENTORY:
		case DRAGON_SOUL_INVENTORY:
			return false;
			break;

		default:
			return false;
		}
	}

#ifdef ENABLE_NEW_EQUIPMENT_SYSTEM
	bool IsBeltInventoryCell()
	{
		bool bResult = c_Belt_Inventory_Slot_Start <= cell && c_Belt_Inventory_Slot_End > cell;
		return bResult;
	}
#endif

#ifdef ENABLE_SPECIAL_INVENTORY_SYSTEM
	bool IsSkillBookInventoryCell()
	{
		bool bResult = c_Skill_Book_Inventory_Slot_Start <= cell && c_Skill_Book_Inventory_Slot_End > cell;
		return bResult;
	}

	bool IsUpgradeItemsInventoryCell()
	{
		bool bResult = c_Upgrade_Items_Inventory_Slot_Start <= cell && c_Upgrade_Items_Inventory_Slot_End > cell;
		return bResult;
	}

	bool IsStoneInventoryCell()
	{
		bool bResult = c_Stone_Inventory_Slot_Start <= cell && c_Stone_Inventory_Slot_End > cell;
		return bResult;
	}

	bool IsGiftBoxInventoryCell()
	{
		bool bResult = c_GiftBox_Inventory_Slot_Start <= cell && c_GiftBox_Inventory_Slot_End > cell;
		return bResult;
	}

	bool IsSwitchInventoryCell()
	{
		bool bResult = c_Switch_Inventory_Slot_Start <= cell && c_Switch_Inventory_Slot_End > cell;
		return bResult;
	}


	bool IsCostumeInventoryCell()
	{
		bool bResult = c_Costume_Inventory_Slot_Start <= cell && c_Costume_Inventory_Slot_End > cell;
		return bResult;
	}

#endif

	bool operator==(const struct SItemPos& rhs) const
	{
		return (window_type == rhs.window_type) && (cell == rhs.cell);
	}

	bool operator<(const struct SItemPos& rhs) const
	{
		return (window_type < rhs.window_type) || ((window_type == rhs.window_type) && (cell < rhs.cell));
	}
} TItemPos;
#pragma pack(pop)

const DWORD c_QuickBar_Line_Count = 3;
const DWORD c_QuickBar_Slot_Count = 12;

const float c_Idle_WaitTime = 5.0f;

const int c_Monster_Race_Start_Number = 6;
const int c_Monster_Model_Start_Number = 20001;

const float c_fAttack_Delay_Time = 0.2f;
const float c_fHit_Delay_Time = 0.1f;
const float c_fCrash_Wave_Time = 0.2f;
const float c_fCrash_Wave_Distance = 3.0f;

const float c_fHeight_Step_Distance = 50.0f;

enum
{
	DISTANCE_TYPE_FOUR_WAY,
	DISTANCE_TYPE_EIGHT_WAY,
	DISTANCE_TYPE_ONE_WAY,
	DISTANCE_TYPE_MAX_NUM,
};

const float c_fMagic_Script_Version = 1.0f;
const float c_fSkill_Script_Version = 1.0f;
const float c_fMagicSoundInformation_Version = 1.0f;
const float c_fBattleCommand_Script_Version = 1.0f;
const float c_fEmotionCommand_Script_Version = 1.0f;
const float c_fActive_Script_Version = 1.0f;
const float c_fPassive_Script_Version = 1.0f;

// Used by PushMove
const float c_fWalkDistance = 175.0f;
const float c_fRunDistance = 310.0f;

#define FILE_MAX_LEN 128

enum
{
	ITEM_SOCKET_SLOT_MAX_NUM = 8,
	// refactored attribute slot begin
	ITEM_ATTRIBUTE_SLOT_NORM_NUM	= 5,
	ITEM_ATTRIBUTE_SLOT_RARE_NUM	= 2,

	ITEM_ATTRIBUTE_SLOT_NORM_START	= 0,
	ITEM_ATTRIBUTE_SLOT_NORM_END	= ITEM_ATTRIBUTE_SLOT_NORM_START + ITEM_ATTRIBUTE_SLOT_NORM_NUM,

	ITEM_ATTRIBUTE_SLOT_RARE_START	= ITEM_ATTRIBUTE_SLOT_NORM_END,
	ITEM_ATTRIBUTE_SLOT_RARE_END	= ITEM_ATTRIBUTE_SLOT_RARE_START + ITEM_ATTRIBUTE_SLOT_RARE_NUM,
	ITEM_ATTRIBUTE_PET				= 8,
	ITEM_ATTRIBUTE_SLOT_MAX_NUM		= ITEM_ATTRIBUTE_SLOT_RARE_END + 8, // 7
	// refactored attribute slot end
};

#pragma pack(push)
#pragma pack(1)

typedef struct SQuickSlot
{
	DWORD Type;
	DWORD Position;
} TQuickSlot;

typedef struct TPlayerItemAttribute
{
    BYTE        bType;
    short       sValue;
} TPlayerItemAttribute;

struct ItemData
{
	TItemPos	Cell;
	DWORD		vnum;
	DWORD		count;
	DWORD		flags;
	DWORD		anti_flags;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
};

typedef struct packet_item
{
    DWORD       vnum;
    DWORD        count;
	DWORD		flags;
	DWORD		anti_flags;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
    TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TItemData;

typedef struct packet_shop_item
{
    DWORD       vnum;
    DWORD       price;
#ifdef ENABLE_SHOPEX_RENEWAL
	DWORD		price1;
	DWORD		price2;
	DWORD		price3;
	DWORD		price4;
#endif
    DWORD       count;
	BYTE		display_pos;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
    TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
#ifdef ENABLE_SHOPEX_RENEWAL
	DWORD price_type = 1;
	DWORD price_vnum = 0;
	DWORD price_vnum1 = 0;
	DWORD price_vnum2 = 0;
	DWORD price_vnum3 = 0;
	DWORD price_vnum4 = 0;
#endif
} TShopItemData;

#pragma pack(pop)

inline float GetSqrtDistance(int ix1, int iy1, int ix2, int iy2) // By sqrt
{
	float dx, dy;

	dx = float(ix1 - ix2);
	dy = float(iy1 - iy2);

	return sqrtf(dx*dx + dy*dy);
}

// DEFAULT_FONT
void DefaultFont_Startup();
void DefaultFont_Cleanup();
void DefaultFont_SetName(const char * c_szFontName);
CResource* DefaultFont_GetResource();
CResource* DefaultItalicFont_GetResource();
// END_OF_DEFAULT_FONT

void SetGuildSymbolPath(const char * c_szPathName);
const char * GetGuildSymbolFileName(DWORD dwGuildID);
BYTE SlotTypeToInvenType(BYTE bSlotType);
#ifdef ENABLE_DETAILS_UI
BYTE ApplyTypeToPointType(BYTE bApplyType);
#endif
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
