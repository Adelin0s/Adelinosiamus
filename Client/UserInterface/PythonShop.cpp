#include "stdafx.h"
#include "PythonShop.h"

#include "PythonNetworkStream.h"

//BOOL CPythonShop::GetSlotItemID(DWORD dwSlotPos, DWORD* pdwItemID)
//{
//	if (!CheckSlotIndex(dwSlotPos))
//		return FALSE;
//	const TShopItemData * itemData;
//	if (!GetItemData(dwSlotPos, &itemData))
//		return FALSE;
//	*pdwItemID=itemData->vnum;
//	return TRUE;
//}
void CPythonShop::SetTabCoinType(BYTE tabIdx, BYTE coinType)
{
	if (tabIdx >= m_bTabCount)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d.", tabIdx, SHOP_TAB_COUNT_MAX);
		return;
	}
	m_aShoptabs[tabIdx].coinType = coinType;
}

BYTE CPythonShop::GetTabCoinType(BYTE tabIdx)
{
	if (tabIdx >= m_bTabCount)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d.", tabIdx, SHOP_TAB_COUNT_MAX);
		return 0xff;
	}
	return m_aShoptabs[tabIdx].coinType;
}

void CPythonShop::SetTabName(BYTE tabIdx, const char* name)
{
	if (tabIdx >= m_bTabCount)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d.", tabIdx, SHOP_TAB_COUNT_MAX);
		return;
	}
	m_aShoptabs[tabIdx].name = name;
}

const char* CPythonShop::GetTabName(BYTE tabIdx)
{
	if (tabIdx >= m_bTabCount)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d.", tabIdx, SHOP_TAB_COUNT_MAX);
		return NULL;
	}

	return m_aShoptabs[tabIdx].name.c_str();
}

void CPythonShop::SetItemData(DWORD dwIndex, const TShopItemData & c_rShopItemData)
{
	BYTE tabIdx = dwIndex / SHOP_HOST_ITEM_MAX_NUM;
	DWORD dwSlotPos = dwIndex % SHOP_HOST_ITEM_MAX_NUM;

	SetItemData(tabIdx, dwSlotPos, c_rShopItemData);
}

BOOL CPythonShop::GetItemData(DWORD dwIndex, const TShopItemData ** c_ppItemData)
{
	BYTE tabIdx = dwIndex / SHOP_HOST_ITEM_MAX_NUM;
	DWORD dwSlotPos = dwIndex % SHOP_HOST_ITEM_MAX_NUM;

	return GetItemData(tabIdx, dwSlotPos, c_ppItemData);
}

void CPythonShop::SetItemData(BYTE tabIdx, DWORD dwSlotPos, const TShopItemData & c_rShopItemData)
{
	if (tabIdx >= SHOP_TAB_COUNT_MAX || dwSlotPos >= SHOP_HOST_ITEM_MAX_NUM)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d. dwSlotPos(%d) must be less than %d", tabIdx, SHOP_TAB_COUNT_MAX, dwSlotPos, SHOP_HOST_ITEM_MAX_NUM);
		return;
	}

	m_aShoptabs[tabIdx].items[dwSlotPos] = c_rShopItemData;
}

BOOL CPythonShop::GetItemData(BYTE tabIdx, DWORD dwSlotPos, const TShopItemData ** c_ppItemData)
{
	if (tabIdx >= SHOP_TAB_COUNT_MAX || dwSlotPos >= SHOP_HOST_ITEM_MAX_NUM)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d. dwSlotPos(%d) must be less than %d", tabIdx, SHOP_TAB_COUNT_MAX, dwSlotPos, SHOP_HOST_ITEM_MAX_NUM);
		return FALSE;
	}

	*c_ppItemData = &m_aShoptabs[tabIdx].items[dwSlotPos];

	return TRUE;
}
//
//BOOL CPythonShop::CheckSlotIndex(DWORD dwSlotPos)
//{
//	if (dwSlotPos >= SHOP_HOST_ITEM_MAX_NUM * SHOP_TAB_COUNT_MAX)
//		return FALSE;
//
//	return TRUE;
//}

void CPythonShop::ClearPrivateShopStock()
{
	m_PrivateShopItemStock.clear();
}
void CPythonShop::AddPrivateShopItemStock(TItemPos ItemPos, BYTE dwDisplayPos, DWORD dwPrice)
{
	DelPrivateShopItemStock(ItemPos);

	TShopItemTable SellingItem;
	SellingItem.vnum = 0;
	SellingItem.count = 0;
	SellingItem.pos = ItemPos;
	SellingItem.price = dwPrice;
	SellingItem.display_pos = dwDisplayPos;
	m_PrivateShopItemStock.emplace(ItemPos, SellingItem);
}
void CPythonShop::DelPrivateShopItemStock(TItemPos ItemPos)
{
	if (m_PrivateShopItemStock.end() == m_PrivateShopItemStock.find(ItemPos))
		return;

	m_PrivateShopItemStock.erase(ItemPos);
}

int CPythonShop::GetPrivateShopItemPrice(TItemPos ItemPos)
{
	TPrivateShopItemStock::iterator itor = m_PrivateShopItemStock.find(ItemPos);

	if (m_PrivateShopItemStock.end() == itor)
		return 0;

	TShopItemTable& rShopItemTable = itor->second;
	return rShopItemTable.price;
}

int CPythonShop::GetPrivateShopItemPrice1(TItemPos ItemPos)
{
	TPrivateShopItemStock::iterator itor = m_PrivateShopItemStock.find(ItemPos);

	if (m_PrivateShopItemStock.end() == itor)
		return 0;

	TShopItemTable& rShopItemTable = itor->second;
	return rShopItemTable.price1;
}

int CPythonShop::GetPrivateShopItemPrice2(TItemPos ItemPos)
{
	TPrivateShopItemStock::iterator itor = m_PrivateShopItemStock.find(ItemPos);

	if (m_PrivateShopItemStock.end() == itor)
		return 0;

	TShopItemTable& rShopItemTable = itor->second;
	return rShopItemTable.price2;
}

int CPythonShop::GetPrivateShopItemPrice3(TItemPos ItemPos)
{
	TPrivateShopItemStock::iterator itor = m_PrivateShopItemStock.find(ItemPos);

	if (m_PrivateShopItemStock.end() == itor)
		return 0;

	TShopItemTable& rShopItemTable = itor->second;
	return rShopItemTable.price3;
}

int CPythonShop::GetPrivateShopItemPrice4(TItemPos ItemPos)
{
	TPrivateShopItemStock::iterator itor = m_PrivateShopItemStock.find(ItemPos);

	if (m_PrivateShopItemStock.end() == itor)
		return 0;

	TShopItemTable& rShopItemTable = itor->second;
	return rShopItemTable.price4;
}

struct ItemStockSortFunc
{
	bool operator() (TShopItemTable & rkLeft, TShopItemTable & rkRight)
	{
		return rkLeft.display_pos < rkRight.display_pos;
	}
};
void CPythonShop::BuildPrivateShop(const char * c_szName)
{
	std::vector<TShopItemTable> ItemStock;
	ItemStock.reserve(m_PrivateShopItemStock.size());

	TPrivateShopItemStock::iterator itor = m_PrivateShopItemStock.begin();
	for (; itor != m_PrivateShopItemStock.end(); ++itor)
	{
		ItemStock.push_back(itor->second);
	}

	std::sort(ItemStock.begin(), ItemStock.end(), ItemStockSortFunc());

	CPythonNetworkStream::Instance().SendBuildPrivateShopPacket(c_szName, ItemStock);
}

void CPythonShop::Open(BOOL isPrivateShop, BOOL isMainPrivateShop)
{
	m_isShoping = TRUE;
	m_isPrivateShop = isPrivateShop;
	m_isMainPlayerPrivateShop = isMainPrivateShop;
}

void CPythonShop::Close()
{
	m_isShoping = FALSE;
	m_isPrivateShop = FALSE;
	m_isMainPlayerPrivateShop = FALSE;
}

BOOL CPythonShop::IsOpen()
{
	return m_isShoping;
}

BOOL CPythonShop::IsPrivateShop()
{
	return m_isPrivateShop;
}

BOOL CPythonShop::IsMainPlayerPrivateShop()
{
	return m_isMainPlayerPrivateShop;
}

void CPythonShop::Clear()
{
	m_isShoping = FALSE;
	m_isPrivateShop = FALSE;
	m_isMainPlayerPrivateShop = FALSE;
	ClearPrivateShopStock();
	m_bTabCount = 1;

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	ClearOfflineShopStock();
	m_isOfflineShop = FALSE;
	m_bHasOfflineShop = false;
	m_llCurrentOfflineShopMoney = 0;
	m_dwDisplayedCount = 0;
	m_shopFlag = 0;
	time = 0;
	type = 0;
	m_dwRealWatcherCount = 0;
	SetShopSign("NONE");
	memset(m_aOfflineShoptabsItems, 0, sizeof(TOfflineShopItemData) * OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
#endif


	for (int i = 0; i < SHOP_TAB_COUNT_MAX; i++)
	{
		// @fixme016 BEGIN
		m_aShoptabs[i].coinType = SHOP_COIN_TYPE_GOLD;
		m_aShoptabs[i].name = "";
		// @fixme016 END
		memset (m_aShoptabs[i].items, 0, sizeof(TShopItemData) * SHOP_HOST_ITEM_MAX_NUM);
	}
}

CPythonShop::CPythonShop(void)
{
	Clear();
}

CPythonShop::~CPythonShop(void)
{
}

PyObject * shopOpen(PyObject * poSelf, PyObject * poArgs)
{
	int isPrivateShop = false;
	PyTuple_GetInteger(poArgs, 0, &isPrivateShop);
	int isMainPrivateShop = false;
	PyTuple_GetInteger(poArgs, 1, &isMainPrivateShop);

	CPythonShop& rkShop=CPythonShop::Instance();
	rkShop.Open(isPrivateShop, isMainPrivateShop);
	return Py_BuildNone();
}

PyObject * shopClose(PyObject * poSelf, PyObject * poArgs)
{
	CPythonShop& rkShop=CPythonShop::Instance();
	rkShop.Close();
	return Py_BuildNone();
}

PyObject * shopIsOpen(PyObject * poSelf, PyObject * poArgs)
{
	CPythonShop& rkShop=CPythonShop::Instance();
	return Py_BuildValue("i", rkShop.IsOpen());
}

PyObject * shopIsPrviateShop(PyObject * poSelf, PyObject * poArgs)
{
	CPythonShop& rkShop=CPythonShop::Instance();
	return Py_BuildValue("i", rkShop.IsPrivateShop());
}

PyObject * shopIsMainPlayerPrivateShop(PyObject * poSelf, PyObject * poArgs)
{
	CPythonShop& rkShop=CPythonShop::Instance();
	return Py_BuildValue("i", rkShop.IsMainPlayerPrivateShop());
}

PyObject * shopGetItemID(PyObject * poSelf, PyObject * poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->vnum);

	return Py_BuildValue("i", 0);
}

PyObject * shopGetItemCount(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->count);

	return Py_BuildValue("i", 0);
}

PyObject * shopGetItemPrice(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetItemPrice1(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price1);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetItemPrice2(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price2);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetItemPrice3(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price3);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetItemPrice4(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price4);

	return Py_BuildValue("i", 0);
}

PyObject * shopGetItemMetinSocket(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	int iMetinSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iMetinSocketIndex))
		return Py_BuildException();

	const TShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->alSockets[iMetinSocketIndex]);

	return Py_BuildValue("i", 0);
}

PyObject * shopGetItemAttribute(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM)
	{
		const TShopItemData * c_pItemData;
		if (CPythonShop::Instance().GetItemData(iIndex, &c_pItemData))
			return Py_BuildValue("ii", c_pItemData->aAttr[iAttrSlotIndex].bType, c_pItemData->aAttr[iAttrSlotIndex].sValue);
	}

	return Py_BuildValue("ii", 0, 0);
}

PyObject* shopClear(PyObject* poSelf, PyObject* poArgs)
{
	CPythonShop::instance().Clear();
	return Py_BuildNone();
}


PyObject * shopClearPrivateShopStock(PyObject * poSelf, PyObject * poArgs)
{
	CPythonShop::Instance().ClearPrivateShopStock();
	return Py_BuildNone();
}
PyObject * shopAddPrivateShopItemStock(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();
	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();
	int iDisplaySlotIndex;
	if (!PyTuple_GetInteger(poArgs, 2, &iDisplaySlotIndex))
		return Py_BuildException();
	int iPrice;
	if (!PyTuple_GetInteger(poArgs, 3, &iPrice))
		return Py_BuildException();

	CPythonShop::Instance().AddPrivateShopItemStock(TItemPos(bItemWindowType, wItemSlotIndex), iDisplaySlotIndex, iPrice);
	return Py_BuildNone();
}
PyObject * shopDelPrivateShopItemStock(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();
	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	CPythonShop::Instance().DelPrivateShopItemStock(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildNone();
}
PyObject * shopGetPrivateShopItemPrice(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();
	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	int iValue = CPythonShop::Instance().GetPrivateShopItemPrice(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildValue("i", iValue);
}

#ifdef ENABLE_SHOPEX_RENEWAL
PyObject* shopGetPrivateShopItemPrice1(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();

	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	int iValue = CPythonShop::Instance().GetPrivateShopItemPrice1(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildValue("i", iValue);
}
PyObject* shopGetPrivateShopItemPrice2(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();

	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	int iValue = CPythonShop::Instance().GetPrivateShopItemPrice2(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildValue("i", iValue);
}
PyObject* shopGetPrivateShopItemPrice3(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();

	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	int iValue = CPythonShop::Instance().GetPrivateShopItemPrice3(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildValue("i", iValue);
}
PyObject* shopGetPrivateShopItemPrice4(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();

	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	int iValue = CPythonShop::Instance().GetPrivateShopItemPrice4(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildValue("i", iValue);
}
#endif

PyObject * shopBuildPrivateShop(PyObject * poSelf, PyObject * poArgs)
{
	char * szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	CPythonShop::Instance().BuildPrivateShop(szName);
	return Py_BuildNone();
}

PyObject * shopGetTabCount(PyObject * poSelf, PyObject * poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetTabCount());
}

PyObject * shopGetTabName(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bTabIdx;
	if (!PyTuple_GetInteger(poArgs, 0, &bTabIdx))
		return Py_BuildException();

	return Py_BuildValue("s", CPythonShop::instance().GetTabName(bTabIdx));
}

PyObject * shopGetTabCoinType(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bTabIdx;
	if (!PyTuple_GetInteger(poArgs, 0, &bTabIdx))
		return Py_BuildException();

	return Py_BuildValue("i", CPythonShop::instance().GetTabCoinType(bTabIdx));
}

#ifdef ENABLE_SHOPEX_RENEWAL
PyObject* shopGetItemPriceType(PyObject* poSelf, PyObject* poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price_type);

	return Py_BuildValue("i", 1);
}

PyObject* shopGetItemPriceVnum(PyObject* poSelf, PyObject* poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price_vnum);

	return Py_BuildValue("i", 0);
}
PyObject* shopGetItemPriceVnum1(PyObject* poSelf, PyObject* poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price_vnum1);

	return Py_BuildValue("i", 0);
}
PyObject* shopGetItemPriceVnum2(PyObject* poSelf, PyObject* poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price_vnum2);

	return Py_BuildValue("i", 0);
}
PyObject* shopGetItemPriceVnum3(PyObject* poSelf, PyObject* poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price_vnum3);

	return Py_BuildValue("i", 0);
}
PyObject* shopGetItemPriceVnum4(PyObject* poSelf, PyObject* poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price_vnum4);

	return Py_BuildValue("i", 0);
}
#endif

#ifdef ENABLE_OFFLINESHOP_SYSTEM
void CPythonShop::SetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData& c_rShopItemData)
{
	if (dwIndex >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		TraceError("dwSlotPos(%d) must be less than %d", dwIndex, OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
		return;
	}
	m_aOfflineShoptabsItems[dwIndex] = c_rShopItemData;
}

BOOL CPythonShop::GetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData** c_ppItemData)
{
	if (dwIndex >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		TraceError("dwSlotPos(%d) must be less than %d", dwIndex, OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
		return FALSE;
	}

	if (m_aOfflineShoptabsItems[dwIndex].vnum)
	{
		*c_ppItemData = &m_aOfflineShoptabsItems[dwIndex];
		return TRUE;
	}

	*c_ppItemData = NULL;

	return FALSE;
}
struct OfflineShopItemStockSortFunc
{
	bool operator() (TOfflineShopItemTable& rkLeft, TOfflineShopItemTable& rkRight)
	{
		return rkLeft.display_pos < rkRight.display_pos;
	}
};
void CPythonShop::AddOfflineShopItemStock(TItemPos ItemPos, BYTE dwDisplayPos, long long dwPrice)
{
	DelOfflineShopItemStock(ItemPos);
	TOfflineShopItemTable SellingItem;
	SellingItem.vnum = 0;
	SellingItem.count = 0;
	SellingItem.pos = ItemPos;
	SellingItem.price = dwPrice;
	SellingItem.display_pos = dwDisplayPos;
	m_OfflineShopItemStock.insert(std::make_pair(ItemPos, SellingItem));
}
void CPythonShop::DelOfflineShopItemStock(TItemPos ItemPos)
{
	if (m_OfflineShopItemStock.end() == m_OfflineShopItemStock.find(ItemPos))
		return;
	m_OfflineShopItemStock.erase(ItemPos);
}
long long CPythonShop::GetOfflineShopItemPrice(TItemPos ItemPos)
{
	auto itor = m_OfflineShopItemStock.find(ItemPos);

	if (m_OfflineShopItemStock.end() == itor)
		return 0;

	TOfflineShopItemTable& rShopItemTable = itor->second;
	return rShopItemTable.price;
}

void CPythonShop::BuildOfflineShop(const char* c_szName, DWORD shopVnum, BYTE shopTitle)
{
	std::vector<TOfflineShopItemTable> ItemStock;
	ItemStock.reserve(m_OfflineShopItemStock.size());

	auto itor = m_OfflineShopItemStock.begin();
	for (; itor != m_OfflineShopItemStock.end(); ++itor)
	{
		ItemStock.push_back(itor->second);
	}

	std::sort(ItemStock.begin(), ItemStock.end(), OfflineShopItemStockSortFunc());

	CPythonNetworkStream::Instance().SendBuildOfflineShopPacket(c_szName, ItemStock, shopVnum, shopTitle);
}

#ifdef WJ_CHANGELOOK_SYSTEM
PyObject* shopGetOfflineShopItemTransmutation(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->transmutation);

	return Py_BuildValue("i", 0);
}
#endif
#ifdef ENABLE_NEW_NAME_ITEM
PyObject* shopGetOfflineShopItemNewName(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("s", c_pItemData->name);

	return Py_BuildValue("s", "^");
}
#endif
PyObject* shopIsOfflineShop(PyObject* poSelf, PyObject* poArgs)
{
	CPythonShop& rkShop = CPythonShop::Instance();
	return Py_BuildValue("i", rkShop.IsOfflineShop());
}

PyObject* shopGetOfflineShopItemIDReal(PyObject* poSelf, PyObject* poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->id);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemID(PyObject* poSelf, PyObject* poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->vnum);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemCount(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->count);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemVnum(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->vnum);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemPrice(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return PyLong_FromLongLong(c_pItemData->price);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetSign(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("s", CPythonShop::Instance().GetShopSign());
}

PyObject* shopGetOfflineShopItemMetinSocket(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	int iMetinSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iMetinSocketIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->alSockets[iMetinSocketIndex]);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemAttribute(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM)
	{
		const TOfflineShopItemData* c_pItemData;
		if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
			return Py_BuildValue("ii", c_pItemData->aAttr[iAttrSlotIndex].bType, c_pItemData->aAttr[iAttrSlotIndex].sValue);
	}

	return Py_BuildValue("ii", 0, 0);
}

PyObject* shopClearOfflineShopStock(PyObject* poSelf, PyObject* poArgs)
{
	CPythonShop::Instance().ClearOfflineShopStock();
	return Py_BuildNone();
}

PyObject* shopAddOfflineShopItemStock(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();
	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();
	int iDisplaySlotIndex;
	if (!PyTuple_GetInteger(poArgs, 2, &iDisplaySlotIndex))
		return Py_BuildException();
	long long iPrice;
	if (!PyTuple_GetLongLong(poArgs, 3, &iPrice))
		return Py_BuildException();

	CPythonShop::Instance().AddOfflineShopItemStock(TItemPos(bItemWindowType, wItemSlotIndex), iDisplaySlotIndex, iPrice);
	return Py_BuildNone();
}

PyObject* shopDelOfflineShopItemStock(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();
	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	CPythonShop::Instance().DelOfflineShopItemStock(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildNone();
}

PyObject* shopGetOfflineShopItemPriceReal(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();
	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();
	return PyLong_FromLongLong(CPythonShop::Instance().GetOfflineShopItemPrice(TItemPos(bItemWindowType, wItemSlotIndex)));
}

PyObject* shopGetOfflineShopItemGetStatus(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->status);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemGetBuyerName(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("s", c_pItemData->szBuyerName);

	return Py_BuildValue("s", "None");
}

PyObject* shopBuildOfflineShop(PyObject* poSelf, PyObject* poArgs)
{
	char* szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();
	int szshopVnum;
	if (!PyTuple_GetInteger(poArgs, 1, &szshopVnum))
		return Py_BuildException();
	int szshopTitle;
	if (!PyTuple_GetInteger(poArgs, 2, &szshopTitle))
		return Py_BuildException();

	CPythonShop::Instance().BuildOfflineShop(szName, (DWORD)szshopVnum, szshopTitle);
	return Py_BuildNone();
}
PyObject* shopGetDisplayedCount(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetShopDisplayedCount());
}
PyObject* shopGetOfflineShopID(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->owner_id);
	return Py_BuildValue("i", 0);
}
PyObject* shopGetCurrentOfflineShopMoney(PyObject* poSelf, PyObject* poArgs)
{
	return	PyLong_FromLongLong(CPythonShop::instance().GetCurrentOfflineShopMoney());
}
PyObject* shopHasOfflineShop(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().HasOfflineShop());
}

PyObject* shopChangeDecoration(PyObject* poSelf, PyObject* poArgs)
{
	char* sign;
	if (!PyTuple_GetString(poArgs, 0, &sign))
		return Py_BuildException();
	int vnum;
	if (!PyTuple_GetInteger(poArgs, 1, &vnum))
		return Py_BuildException();
	int type;
	if (!PyTuple_GetInteger(poArgs, 2, &type))
		return Py_BuildException();
	CPythonNetworkStream::instance().SendOfflineShopChangeDecoration(sign, vnum, type);
	return Py_BuildNone();
}
PyObject* shopGetRealWatcherCount(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetRealWatcherCount());
}
PyObject* shopGetShopFlag(PyObject* poSelf, PyObject* poArgs)
{
	return PyLong_FromLongLong(CPythonShop::instance().GetShopFlag());
}
PyObject* shopSetShopFlag(PyObject* poSelf, PyObject* poArgs)
{
	long long flag;
	if (!PyTuple_GetLongLong(poArgs, 0, &flag))
		return Py_BuildException();
	CPythonShop::instance().SetShopFlag(flag);
	return Py_BuildNone();
}
PyObject* shopGetShopType(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetShopType());
}
PyObject* shopSetShopType(PyObject* poSelf, PyObject* poArgs)
{
	int type;
	if (!PyTuple_GetInteger(poArgs, 0, &type))
		return Py_BuildException();
	CPythonShop::instance().SetShopType(type);
	return Py_BuildNone();
}
PyObject* shopGetShopTime(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetShopTime());
}
PyObject* shopSetShopTime(PyObject* poSelf, PyObject* poArgs)
{
	int type;
	if (!PyTuple_GetInteger(poArgs, 0, &type))
		return Py_BuildException();
	CPythonShop::instance().SetShopTime(type);
	return Py_BuildNone();
}
PyObject* shopAddItemShortcut(PyObject* poSelf, PyObject* poArgs)
{
	int itemWindow;
	if (!PyTuple_GetInteger(poArgs, 0, &itemWindow))
		return Py_BuildException();
	int itemSlot;
	if (!PyTuple_GetInteger(poArgs, 1, &itemSlot))
		return Py_BuildException();
	long long itemPrice;
	if (!PyTuple_GetLongLong(poArgs, 2, &itemPrice))
		return Py_BuildException();
	CPythonNetworkStream::instance().SendOfflineShopAddItemShortcut(itemWindow, itemSlot, itemPrice);
	return Py_BuildNone();
}
PyObject* shopGetAveragePrice(PyObject* poSelf, PyObject* poArgs)
{
	int itemIdx;
	if (!PyTuple_GetInteger(poArgs, 0, &itemIdx))
		return Py_BuildException();
	CPythonNetworkStream::instance().SendOfflineShopAverageItem((DWORD)itemIdx);
	return Py_BuildNone();
}
#endif

void initshop()
{
	static PyMethodDef s_methods[] =
	{
		// Shop
		{ "Open",						shopOpen,						METH_VARARGS },
		{ "Close",						shopClose,						METH_VARARGS },
		{ "IsOpen",						shopIsOpen,						METH_VARARGS },
		{ "IsPrivateShop",				shopIsPrviateShop,				METH_VARARGS },
		{ "IsMainPlayerPrivateShop",	shopIsMainPlayerPrivateShop,	METH_VARARGS },
		{ "GetItemID",					shopGetItemID,					METH_VARARGS },
		{ "GetItemCount",				shopGetItemCount,				METH_VARARGS },
		{ "GetItemPrice",				shopGetItemPrice,				METH_VARARGS },

		{ "GetItemPrice1",				shopGetItemPrice1, METH_VARARGS },
		{ "GetItemPrice2",				shopGetItemPrice2, METH_VARARGS },
		{ "GetItemPrice3",				shopGetItemPrice3, METH_VARARGS },
		{ "GetItemPrice4",				shopGetItemPrice4, METH_VARARGS },
#ifdef ENABLE_OFFLINESHOP_SYSTEM
#ifdef WJ_CHANGELOOK_SYSTEM
		{ "GetOfflineShopItemTransmutation", shopGetOfflineShopItemTransmutation, METH_VARARGS },
#endif
#ifdef ENABLE_NEW_NAME_ITEM
		{ "GetOfflineShopItemNewName", shopGetOfflineShopItemNewName, METH_VARARGS },
#endif

		#if defined(ENABLE_SHOPEX_RENEWAL)
		// ShopEx
		{ "GetItemPriceType", shopGetItemPriceType, METH_VARARGS },
		{ "GetItemPriceVnum", shopGetItemPriceVnum, METH_VARARGS },
		{ "GetItemPriceVnum1", shopGetItemPriceVnum1, METH_VARARGS },
		{ "GetItemPriceVnum2", shopGetItemPriceVnum2, METH_VARARGS },
		{ "GetItemPriceVnum3", shopGetItemPriceVnum3, METH_VARARGS },
		{ "GetItemPriceVnum4", shopGetItemPriceVnum4, METH_VARARGS },
#endif

		{ "IsOfflineShop", shopIsOfflineShop, METH_VARARGS },
		{ "GetOfflineShopItemIDReal", shopGetOfflineShopItemIDReal, METH_VARARGS },
		{ "GetOfflineShopItemID", shopGetOfflineShopItemID, METH_VARARGS },
		{ "GetOfflineShopItemCount", shopGetOfflineShopItemCount, METH_VARARGS },
		{ "GetOfflineShopItemVnum", shopGetOfflineShopItemVnum, METH_VARARGS },
		{ "GetOfflineShopItemPrice", shopGetOfflineShopItemPrice, METH_VARARGS },
		{ "GetOfflineShopItemMetinSocket", shopGetOfflineShopItemMetinSocket, METH_VARARGS },
		{ "GetOfflineShopItemAttribute", shopGetOfflineShopItemAttribute, METH_VARARGS },
		{ "GetSign", shopGetSign, METH_VARARGS },
		{ "ClearOfflineShopStock", shopClearOfflineShopStock, METH_VARARGS },
		{ "AddOfflineShopItemStock", shopAddOfflineShopItemStock, METH_VARARGS },
		{ "DelOfflineShopItemStock", shopDelOfflineShopItemStock, METH_VARARGS },
		{ "GetOfflineShopItemPriceReal", shopGetOfflineShopItemPriceReal, METH_VARARGS },
		{ "GetOfflineShopItemStatus", shopGetOfflineShopItemGetStatus, METH_VARARGS },
		{ "GetOfflineShopItemBuyerName", shopGetOfflineShopItemGetBuyerName, METH_VARARGS },
		{ "BuildOfflineShop", shopBuildOfflineShop, METH_VARARGS },
		{ "GetDisplayedCount", shopGetDisplayedCount, METH_VARARGS },
		{ "GetOfflineShopID", shopGetOfflineShopID, METH_VARARGS },
		{ "GetCurrentOfflineShopMoney", shopGetCurrentOfflineShopMoney, METH_VARARGS },
		{ "HasOfflineShop", shopHasOfflineShop, METH_VARARGS },
		{ "GetRealWatcherCount", shopGetRealWatcherCount, METH_VARARGS },
		{ "ChangeDecoration", shopChangeDecoration, METH_VARARGS },
		{ "GetShopFlag", shopGetShopFlag, METH_VARARGS },
		{ "SetShopFlag", shopSetShopFlag, METH_VARARGS },
		{ "GetShopType", shopGetShopType, METH_VARARGS },
		{ "SetShopType", shopSetShopType, METH_VARARGS },
		{ "GetShopTime", shopGetShopTime, METH_VARARGS },
		{ "SetShopTime", shopSetShopTime, METH_VARARGS },
		{ "AddItemShortcut", shopAddItemShortcut, METH_VARARGS },
		{ "GetAveragePrice", shopGetAveragePrice, METH_VARARGS },
#endif
		{ "GetItemMetinSocket",			shopGetItemMetinSocket,			METH_VARARGS },
		{ "GetItemAttribute",			shopGetItemAttribute,			METH_VARARGS },
		{ "GetTabCount",				shopGetTabCount,				METH_VARARGS },
		{ "GetTabName",					shopGetTabName,					METH_VARARGS },
		{ "GetTabCoinType",				shopGetTabCoinType,				METH_VARARGS },

		// Private Shop
		{ "ClearPrivateShopStock",		shopClearPrivateShopStock,		METH_VARARGS },
		{ "AddPrivateShopItemStock",	shopAddPrivateShopItemStock,	METH_VARARGS },
		{ "DelPrivateShopItemStock",	shopDelPrivateShopItemStock,	METH_VARARGS },
		{ "GetPrivateShopItemPrice",	shopGetPrivateShopItemPrice,	METH_VARARGS },
		{ "BuildPrivateShop",			shopBuildPrivateShop,			METH_VARARGS },
		{ "Clear",						shopClear,						METH_VARARGS },
		{ NULL,							NULL,							NULL },
	};
	PyObject * poModule = Py_InitModule("shop", s_methods);
#ifdef ENABLE_OFFLINESHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "OFFLINE_SHOP_SLOT_COUNT", OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
#endif
	PyModule_AddIntConstant(poModule, "SHOP_SLOT_COUNT", SHOP_HOST_ITEM_MAX_NUM);
	PyModule_AddIntConstant(poModule, "SHOP_COIN_TYPE_GOLD", SHOP_COIN_TYPE_GOLD);
	PyModule_AddIntConstant(poModule, "SHOP_COIN_TYPE_SECONDARY_COIN", SHOP_COIN_TYPE_SECONDARY_COIN);
}
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
