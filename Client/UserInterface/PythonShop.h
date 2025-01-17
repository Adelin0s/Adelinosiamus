#pragma once

#include "Packet.h"

typedef enum
{
	SHOP_COIN_TYPE_GOLD, // DEFAULT VALUE
	SHOP_COIN_TYPE_SECONDARY_COIN,
} EShopCoinType;

class CPythonShop : public CSingleton<CPythonShop>
{
	public:
		CPythonShop(void);
		virtual ~CPythonShop(void);

		void Clear();

		void SetItemData(DWORD dwIndex, const TShopItemData & c_rShopItemData);
		BOOL GetItemData(DWORD dwIndex, const TShopItemData ** c_ppItemData);

		void SetItemData(BYTE tabIdx, DWORD dwSlotPos, const TShopItemData & c_rShopItemData);
		BOOL GetItemData(BYTE tabIdx, DWORD dwSlotPos, const TShopItemData ** c_ppItemData);

		void SetTabCount(BYTE bTabCount) { m_bTabCount = bTabCount; }
		BYTE GetTabCount() { return m_bTabCount; }

		void SetTabCoinType(BYTE tabIdx, BYTE coinType);
		BYTE GetTabCoinType(BYTE tabIdx);

		void SetTabName(BYTE tabIdx, const char* name);
		const char* GetTabName(BYTE tabIdx);

		//BOOL GetSlotItemID(DWORD dwSlotPos, DWORD* pdwItemID);

		void Open(BOOL isPrivateShop, BOOL isMainPrivateShop);
		void Close();
		BOOL IsOpen();
#ifdef ENABLE_OFFLINESHOP_SYSTEM
		void SetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData& c_rShopItemData);
		BOOL GetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData** c_ppItemData);

		void SetShopDisplayedCount(DWORD dwDisplayedCount) { m_dwDisplayedCount = dwDisplayedCount; }
		void SetShopSign(const char* g_sign) { strcpy(sign, g_sign); }
		const char* GetShopSign() { return sign; }
		DWORD	GetShopDisplayedCount() { return m_dwDisplayedCount; }
		BOOL IsOfflineShop() { return m_isOfflineShop; }
		void ClearOfflineShopStock() { m_OfflineShopItemStock.clear(); }
		void AddOfflineShopItemStock(TItemPos ItemPos, BYTE byDisplayPos, long long dwPrice);
		void DelOfflineShopItemStock(TItemPos ItemPos);
		long long	 GetOfflineShopItemPrice(TItemPos ItemPos);
		//BYTE	GetOfflineShopItemStatus(TItemPos ItemPos);
		void BuildOfflineShop(const char* c_szName, DWORD shopVnum, BYTE shopTitle);

		void	SetCurrentOfflineShopMoney(long long llMoney) { m_llCurrentOfflineShopMoney = llMoney; }
		long long	GetCurrentOfflineShopMoney() { return m_llCurrentOfflineShopMoney; }

		bool	HasOfflineShop() { return m_bHasOfflineShop; }
		void	SetHasOfflineShop(bool bStatus) { m_bHasOfflineShop = bStatus; }

		DWORD	GetRealWatcherCount() { return m_dwRealWatcherCount; }
		void	SetRealWatcherCount(DWORD p) { m_dwRealWatcherCount = p; }

		unsigned long long	GetShopFlag() { return m_shopFlag; }
		void	SetShopFlag(unsigned long long p) { m_shopFlag = p; }

		int		GetShopTime() { return time; }
		void	SetShopTime(int a) { time = a; }

		DWORD	GetShopType() { return type; }
		void	SetShopType(DWORD a) { type = a; }
#endif
		BOOL IsPrivateShop();
		BOOL IsMainPlayerPrivateShop();

		void ClearPrivateShopStock();
		void AddPrivateShopItemStock(TItemPos ItemPos, BYTE byDisplayPos, DWORD dwPrice);
		void DelPrivateShopItemStock(TItemPos ItemPos);
		int GetPrivateShopItemPrice(TItemPos ItemPos);
		int GetPrivateShopItemPrice1(TItemPos ItemPos);
		int GetPrivateShopItemPrice2(TItemPos ItemPos);
		int GetPrivateShopItemPrice3(TItemPos ItemPos);
		int GetPrivateShopItemPrice4(TItemPos ItemPos);
		void BuildPrivateShop(const char * c_szName);

	protected:
		BOOL	CheckSlotIndex(DWORD dwIndex);

	protected:
		BOOL				m_isShoping;
		BOOL				m_isPrivateShop;
		BOOL				m_isMainPlayerPrivateShop;
#ifdef ENABLE_OFFLINESHOP_SYSTEM
		DWORD				m_dwDisplayedCount;
		DWORD				m_dwRealWatcherCount;
		TOfflineShopItemData m_aOfflineShoptabsItems[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
		std::map<TItemPos, TOfflineShopItemTable>	m_OfflineShopItemStock;
		BOOL				m_isOfflineShop;
		char				sign[SHOP_SIGN_MAX_LEN + 1];
		bool				m_bHasOfflineShop;
		long long			m_llCurrentOfflineShopMoney;
		unsigned long long			m_shopFlag;
		int					time;
		DWORD				type;
#endif

		struct ShopTab
		{
			ShopTab()
			{
				coinType = SHOP_COIN_TYPE_GOLD;
			}
			BYTE				coinType;
			std::string			name;
			TShopItemData		items[SHOP_HOST_ITEM_MAX_NUM];
		};

		BYTE m_bTabCount;
		ShopTab m_aShoptabs[SHOP_TAB_COUNT_MAX];

		typedef std::map<TItemPos, TShopItemTable> TPrivateShopItemStock;
		TPrivateShopItemStock	m_PrivateShopItemStock;
};
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
