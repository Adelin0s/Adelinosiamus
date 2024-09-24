#include "StdAfx.h"
#include "PythonNetworkStream.h"
#include "NetworkActorManager.h"
#include "PythonBackground.h"

#include "PythonApplication.h"
#include "AbstractPlayer.h"
#include "../gamelib/ActorInstance.h"
#ifdef ENABLE_CUBE_RENEWAL_WORLDARD
#include "PythonCubeRenewal.h"
#endif

void CPythonNetworkStream::__GlobalPositionToLocalPosition(LONG& rGlobalX, LONG& rGlobalY)
{
	CPythonBackground&rkBgMgr=CPythonBackground::Instance();
	rkBgMgr.GlobalPositionToLocalPosition(rGlobalX, rGlobalY);
}

void CPythonNetworkStream::__LocalPositionToGlobalPosition(LONG& rLocalX, LONG& rLocalY)
{
	CPythonBackground&rkBgMgr=CPythonBackground::Instance();
	rkBgMgr.LocalPositionToGlobalPosition(rLocalX, rLocalY);
}

bool CPythonNetworkStream::__CanActMainInstance()
{
	CPythonCharacterManager& rkChrMgr=CPythonCharacterManager::Instance();
	CInstanceBase* pkInstMain=rkChrMgr.GetMainInstancePtr();
	if (!pkInstMain)
		return false;

	return pkInstMain->CanAct();
}

void CPythonNetworkStream::__ClearNetworkActorManager()
{
	m_rokNetActorMgr->Destroy();
}

void __SetWeaponPower(IAbstractPlayer& rkPlayer, DWORD dwWeaponID)
{
	DWORD minPower=0;
	DWORD maxPower=0;
	DWORD minMagicPower=0;
	DWORD maxMagicPower=0;
	DWORD addPower=0;

	CItemData* pkWeapon;
	if (CItemManager::Instance().GetItemDataPointer(dwWeaponID, &pkWeapon))
	{
		if (pkWeapon->GetType()==CItemData::ITEM_TYPE_WEAPON)
		{
			minPower=pkWeapon->GetValue(3);
			maxPower=pkWeapon->GetValue(4);
			minMagicPower=pkWeapon->GetValue(1);
			maxMagicPower=pkWeapon->GetValue(2);
			addPower=pkWeapon->GetValue(5);
		}
#ifdef ENABLE_WEAPON_COSTUME_SYSTEM
		else if (pkWeapon->GetType()==CItemData::ITEM_TYPE_COSTUME && pkWeapon->GetSubType()==CItemData::COSTUME_WEAPON)
		{
			CItemData* pkRealWeapon;
			if (CItemManager::Instance().GetItemDataPointer(CPythonPlayer::Instance().GetItemIndex(TItemPos(INVENTORY, c_Equipment_Weapon)), &pkRealWeapon))
			{
				minPower=pkRealWeapon->GetValue(3);
				maxPower=pkRealWeapon->GetValue(4);
				minMagicPower=pkRealWeapon->GetValue(1);
				maxMagicPower=pkRealWeapon->GetValue(2);
				addPower=pkRealWeapon->GetValue(5);
			}
		}
#endif
	}

	rkPlayer.SetWeaponPower(minPower, maxPower, minMagicPower, maxMagicPower, addPower);
}

bool IsInvisibleRace(WORD raceNum)
{
	switch(raceNum)
	{
	case 20025:
	case 20038:
	case 20039:
		return true;
	default:
		return false;
	}
}

static SNetworkActorData s_kNetActorData;

bool CPythonNetworkStream::RecvCharacterAppendPacket()
{
	TPacketGCCharacterAdd chrAddPacket;
	if (!Recv(sizeof(chrAddPacket), &chrAddPacket))
		return false;

	__GlobalPositionToLocalPosition(chrAddPacket.x, chrAddPacket.y);

	SNetworkActorData kNetActorData;
	kNetActorData.m_bType=chrAddPacket.bType;
	kNetActorData.m_dwMovSpd=chrAddPacket.bMovingSpeed;
	kNetActorData.m_dwAtkSpd=chrAddPacket.bAttackSpeed;
	kNetActorData.m_dwRace=chrAddPacket.wRaceNum;

	kNetActorData.m_dwStateFlags=chrAddPacket.bStateFlag;
	kNetActorData.m_dwVID=chrAddPacket.dwVID;
	kNetActorData.m_fRot=chrAddPacket.angle;

	kNetActorData.m_stName="";

	kNetActorData.m_stName="";
	kNetActorData.m_kAffectFlags.CopyData(0, sizeof(chrAddPacket.dwAffectFlag[0]), &chrAddPacket.dwAffectFlag[0]);
	kNetActorData.m_kAffectFlags.CopyData(32, sizeof(chrAddPacket.dwAffectFlag[1]), &chrAddPacket.dwAffectFlag[1]);

	kNetActorData.SetPosition(chrAddPacket.x, chrAddPacket.y);

	kNetActorData.m_sAlignment=0;/*chrAddPacket.sAlignment*/;
	kNetActorData.m_byPKMode=0;/*chrAddPacket.bPKMode*/;
	kNetActorData.m_dwGuildID=0;/*chrAddPacket.dwGuild*/;
	kNetActorData.m_dwEmpireID=0;/*chrAddPacket.bEmpire*/;
	kNetActorData.m_dwArmor=0;/*chrAddPacket.awPart[CHR_EQUIPPART_ARMOR]*/;
	kNetActorData.m_dwWeapon=0;/*chrAddPacket.awPart[CHR_EQUIPPART_WEAPON]*/;
	kNetActorData.m_dwHair=0;/*chrAddPacket.awPart[CHR_EQUIPPART_HAIR]*/;
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
	kNetActorData.m_dwAcce = 0;
#endif
#ifdef ENABLE_QUIVER_SYSTEM
	kNetActorData.m_dwArrow=0;/*chrAddPacket.m_dwArrow*/
#endif
	kNetActorData.m_dwMountVnum=0;/*chrAddPacket.dwMountVnum*/;
	kNetActorData.m_dwLevel = 0;

	if(kNetActorData.m_bType != CActorInstance::TYPE_PC &&
		kNetActorData.m_bType != CActorInstance::TYPE_HORSE
#ifdef ENABLE_NEW_PET_SYSTEM
		&& kNetActorData.m_bType != CActorInstance::TYPE_PET && kNetActorData.m_dwRace != 65000 && false == ShopRace(kNetActorData.m_dwRace)
#endif
		)
	{
		const char * c_szName;
		CPythonNonPlayer& rkNonPlayer=CPythonNonPlayer::Instance();
		if (rkNonPlayer.GetName(kNetActorData.m_dwRace, &c_szName))
			kNetActorData.m_stName = c_szName;
		//else
		//	kNetActorData.m_stName=chrAddPacket.name;

		__RecvCharacterAppendPacket(&kNetActorData);
	}
	else
	{
		s_kNetActorData = kNetActorData;
	}

	return true;
}

bool CPythonNetworkStream::RecvCharacterAdditionalInfo()
{
	TPacketGCCharacterAdditionalInfo chrInfoPacket;
	if (!Recv(sizeof(chrInfoPacket), &chrInfoPacket))
		return false;

	SNetworkActorData kNetActorData = s_kNetActorData;
	if (IsInvisibleRace(kNetActorData.m_dwRace))
		return true;

	if(kNetActorData.m_dwVID == chrInfoPacket.dwVID)
	{
		const char* c_szName;

		if (kNetActorData.m_bType == CActorInstance::TYPE_NPC && kNetActorData.m_bType != CActorInstance::TYPE_HORSE && kNetActorData.m_bType != CActorInstance::TYPE_PET && kNetActorData.m_dwRace < 30000 && kNetActorData.m_dwRace > 30007 && kNetActorData.m_dwRace != 65000)
		{
			if (CPythonNonPlayer::Instance().GetName(kNetActorData.m_dwRace, &c_szName))
				kNetActorData.m_stName = c_szName;
			else
				kNetActorData.m_stName = chrInfoPacket.name;
		}
		else
			kNetActorData.m_stName = chrInfoPacket.name;

		kNetActorData.m_dwGuildID	= chrInfoPacket.dwGuildID;
		kNetActorData.m_dwLevel		= chrInfoPacket.dwLevel;
		kNetActorData.m_sAlignment	= chrInfoPacket.sAlignment;
		kNetActorData.m_byPKMode	= chrInfoPacket.bPKMode;
		kNetActorData.m_dwGuildID	= chrInfoPacket.dwGuildID;
		kNetActorData.m_dwEmpireID	= chrInfoPacket.bEmpire;
		kNetActorData.m_dwArmor		= chrInfoPacket.awPart[CHR_EQUIPPART_ARMOR];
		kNetActorData.m_dwWeapon	= chrInfoPacket.awPart[CHR_EQUIPPART_WEAPON];
		kNetActorData.m_dwHair		= chrInfoPacket.awPart[CHR_EQUIPPART_HAIR];
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
		kNetActorData.m_dwAcce		= chrInfoPacket.awPart[CHR_EQUIPPART_ACCE];
#endif
#ifdef ENABLE_QUIVER_SYSTEM
		kNetActorData.m_dwArrow		= chrInfoPacket.dwArrow;
#endif
		kNetActorData.m_dwMountVnum	= chrInfoPacket.dwMountVnum;
		kNetActorData.m_bLanguage = chrInfoPacket.bLanguage;

		__RecvCharacterAppendPacket(&kNetActorData);
	}
	//else
	//{
	//	TraceError("TPacketGCCharacterAdditionalInfo name=%s vid=%d race=%d Error",chrInfoPacket.name,chrInfoPacket.dwVID,kNetActorData.m_dwRace);
	//}
	return true;
}

bool CPythonNetworkStream::RecvCharacterAppendPacketNew()
{
	TraceError("TPacketGCCharacterAdd2 is packet that doesn't write.");
	TPacketGCCharacterAdd2 chrAddPacket;
	if (!Recv(sizeof(chrAddPacket), &chrAddPacket))
		return false;
	if(IsInvisibleRace(chrAddPacket.wRaceNum))
		return true;

	__GlobalPositionToLocalPosition(chrAddPacket.x, chrAddPacket.y);

	SNetworkActorData kNetActorData;
	kNetActorData.m_dwLevel		= 0;
	kNetActorData.m_bType		= chrAddPacket.bType;
	kNetActorData.m_dwGuildID	= chrAddPacket.dwGuild;
	kNetActorData.m_dwEmpireID	= chrAddPacket.bEmpire;
	kNetActorData.m_dwMovSpd	= chrAddPacket.bMovingSpeed;
	kNetActorData.m_dwAtkSpd	= chrAddPacket.bAttackSpeed;
	kNetActorData.m_dwRace		= chrAddPacket.wRaceNum;
	kNetActorData.m_dwArmor		= chrAddPacket.awPart[CHR_EQUIPPART_ARMOR];
	kNetActorData.m_dwWeapon	= chrAddPacket.awPart[CHR_EQUIPPART_WEAPON];
	kNetActorData.m_dwHair		= chrAddPacket.awPart[CHR_EQUIPPART_HAIR];
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
	kNetActorData.m_dwAcce		= chrAddPacket.awPart[CHR_EQUIPPART_ACCE];
#endif
#ifdef ENABLE_QUIVER_SYSTEM
	kNetActorData.m_dwArrow		= chrAddPacket.dwArrow;
#endif
	kNetActorData.m_bLanguage = 0;

	kNetActorData.m_dwStateFlags= chrAddPacket.bStateFlag;
	kNetActorData.m_dwVID		= chrAddPacket.dwVID;
	kNetActorData.m_dwMountVnum	= chrAddPacket.dwMountVnum;
	kNetActorData.m_fRot		= chrAddPacket.angle;

	kNetActorData.m_kAffectFlags.CopyData(0, sizeof(chrAddPacket.dwAffectFlag[0]), &chrAddPacket.dwAffectFlag[0]);
	kNetActorData.m_kAffectFlags.CopyData(32, sizeof(chrAddPacket.dwAffectFlag[1]), &chrAddPacket.dwAffectFlag[1]);

	kNetActorData.SetPosition(chrAddPacket.x, chrAddPacket.y);
	kNetActorData.m_sAlignment=chrAddPacket.sAlignment;
	kNetActorData.m_byPKMode=chrAddPacket.bPKMode;
	kNetActorData.m_stName=chrAddPacket.name;
	__RecvCharacterAppendPacket(&kNetActorData);

	return true;
}

bool CPythonNetworkStream::RecvCharacterUpdatePacket()
{
	TPacketGCCharacterUpdate chrUpdatePacket;
	if (!Recv(sizeof(chrUpdatePacket), &chrUpdatePacket))
		return false;

	SNetworkUpdateActorData kNetUpdateActorData;
	kNetUpdateActorData.m_dwGuildID	= chrUpdatePacket.dwGuildID;
	kNetUpdateActorData.m_dwMovSpd	= chrUpdatePacket.bMovingSpeed;
	kNetUpdateActorData.m_dwAtkSpd	= chrUpdatePacket.bAttackSpeed;
	kNetUpdateActorData.m_dwArmor	= chrUpdatePacket.awPart[CHR_EQUIPPART_ARMOR];
	kNetUpdateActorData.m_dwWeapon	= chrUpdatePacket.awPart[CHR_EQUIPPART_WEAPON];
	kNetUpdateActorData.m_dwHair	= chrUpdatePacket.awPart[CHR_EQUIPPART_HAIR];
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
	kNetUpdateActorData.m_dwAcce	= chrUpdatePacket.awPart[CHR_EQUIPPART_ACCE];
#endif
#ifdef ENABLE_QUIVER_SYSTEM
	kNetUpdateActorData.m_dwArrow	= chrUpdatePacket.dwArrow;
#endif
	kNetUpdateActorData.m_dwVID		= chrUpdatePacket.dwVID;

	kNetUpdateActorData.m_kAffectFlags.CopyData(0, sizeof(chrUpdatePacket.dwAffectFlag[0]), &chrUpdatePacket.dwAffectFlag[0]);
	kNetUpdateActorData.m_kAffectFlags.CopyData(32, sizeof(chrUpdatePacket.dwAffectFlag[1]), &chrUpdatePacket.dwAffectFlag[1]);

	kNetUpdateActorData.m_sAlignment	= chrUpdatePacket.sAlignment;
	kNetUpdateActorData.m_byPKMode		= chrUpdatePacket.bPKMode;
	kNetUpdateActorData.m_dwStateFlags	= chrUpdatePacket.bStateFlag;
	kNetUpdateActorData.m_dwMountVnum	= chrUpdatePacket.dwMountVnum;
	kNetUpdateActorData.m_bLanguage = chrUpdatePacket.bLanguage;

	__RecvCharacterUpdatePacket(&kNetUpdateActorData);

	return true;
}

void CPythonNetworkStream::__RecvCharacterAppendPacket(SNetworkActorData * pkNetActorData)
{
	IAbstractPlayer& rkPlayer = IAbstractPlayer::GetSingleton();
	if (rkPlayer.IsMainCharacterIndex(pkNetActorData->m_dwVID))
	{
		rkPlayer.SetRace(pkNetActorData->m_dwRace);

		__SetWeaponPower(rkPlayer, pkNetActorData->m_dwWeapon);

		if (rkPlayer.NEW_GetMainActorPtr())
		{
			CPythonBackground::Instance().Update(pkNetActorData->m_lCurX, pkNetActorData->m_lCurY, 0.0f);
			CPythonCharacterManager::Instance().Update();

			{
				std::string strMapName = CPythonBackground::Instance().GetWarpMapName();
				if (strMapName == "metin2_map_deviltower1")
					__ShowMapName(pkNetActorData->m_lCurX, pkNetActorData->m_lCurY);
			}
		}
		else
		{
			__ShowMapName(pkNetActorData->m_lCurX, pkNetActorData->m_lCurY);
		}
	}

	m_rokNetActorMgr->AppendActor(*pkNetActorData);

	if (GetMainActorVID()==pkNetActorData->m_dwVID)
	{
		rkPlayer.SetTarget(0);
		if (m_bComboSkillFlag)
			rkPlayer.SetComboSkillFlag(m_bComboSkillFlag);

		__SetGuildID(pkNetActorData->m_dwGuildID);
		//CPythonApplication::Instance().SkipRenderBuffering(10000);
	}
}

void CPythonNetworkStream::__RecvCharacterUpdatePacket(SNetworkUpdateActorData * pkNetUpdateActorData)
{
	m_rokNetActorMgr->UpdateActor(*pkNetUpdateActorData);

	IAbstractPlayer& rkPlayer = IAbstractPlayer::GetSingleton();
	if (rkPlayer.IsMainCharacterIndex(pkNetUpdateActorData->m_dwVID))
	{
		__SetGuildID(pkNetUpdateActorData->m_dwGuildID);
		__SetWeaponPower(rkPlayer, pkNetUpdateActorData->m_dwWeapon);

		__RefreshStatus();
		__RefreshAlignmentWindow();
		__RefreshEquipmentWindow();
		__RefreshInventoryWindow();

#ifdef ENABLE_IMPROVED_LOGOUT_POINTS
		m_akSimplePlayerInfo[m_dwSelectedCharacterIndex].wHairPart = pkNetUpdateActorData->m_dwHair;
		m_akSimplePlayerInfo[m_dwSelectedCharacterIndex].wMainPart = pkNetUpdateActorData->m_dwArmor;
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
		m_akSimplePlayerInfo[m_dwSelectedCharacterIndex].wAccePart = pkNetUpdateActorData->m_dwAcce;
#endif
#endif
	}
	else
	{
		rkPlayer.NotifyCharacterUpdate(pkNetUpdateActorData->m_dwVID);
	}
}

bool CPythonNetworkStream::RecvCharacterDeletePacket()
{
	TPacketGCCharacterDelete chrDelPacket;

	if (!Recv(sizeof(chrDelPacket), &chrDelPacket))
	{
		TraceError("CPythonNetworkStream::RecvCharacterDeletePacket - Recv Error");
		return false;
	}

	m_rokNetActorMgr->RemoveActor(chrDelPacket.dwVID);

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME],
		"BINARY_PrivateShop_Disappear",
		Py_BuildValue("(i)", chrDelPacket.dwVID)
	);

	return true;
}

bool CPythonNetworkStream::RecvCharacterMovePacket()
{
	TPacketGCMove kMovePacket;
	if (!Recv(sizeof(TPacketGCMove), &kMovePacket))
	{
		Tracen("CPythonNetworkStream::RecvCharacterMovePacket - PACKET READ ERROR");
		return false;
	}

	__GlobalPositionToLocalPosition(kMovePacket.lX, kMovePacket.lY);

	SNetworkMoveActorData kNetMoveActorData;
	kNetMoveActorData.m_dwArg=kMovePacket.bArg;
	kNetMoveActorData.m_dwFunc=kMovePacket.bFunc;
	kNetMoveActorData.m_dwTime=kMovePacket.dwTime;
	kNetMoveActorData.m_dwVID=kMovePacket.dwVID;
	kNetMoveActorData.m_fRot=kMovePacket.bRot*5.0f;
	kNetMoveActorData.m_lPosX=kMovePacket.lX;
	kNetMoveActorData.m_lPosY=kMovePacket.lY;
	kNetMoveActorData.m_dwDuration=kMovePacket.dwDuration;

	m_rokNetActorMgr->MoveActor(kNetMoveActorData);

	return true;
}

bool CPythonNetworkStream::RecvOwnerShipPacket()
{
	TPacketGCOwnership kPacketOwnership;

	if (!Recv(sizeof(kPacketOwnership), &kPacketOwnership))
		return false;

	m_rokNetActorMgr->SetActorOwner(kPacketOwnership.dwOwnerVID, kPacketOwnership.dwVictimVID);

	return true;
}

bool CPythonNetworkStream::RecvSyncPositionPacket()
{
	TPacketGCSyncPosition kPacketSyncPos;
	if (!Recv(sizeof(kPacketSyncPos), &kPacketSyncPos))
		return false;

	TPacketGCSyncPositionElement kSyncPos;

	UINT uSyncPosCount=(kPacketSyncPos.wSize-sizeof(kPacketSyncPos))/sizeof(kSyncPos);
	for (UINT iSyncPos=0; iSyncPos<uSyncPosCount; ++iSyncPos)
	{
		if (!Recv(sizeof(TPacketGCSyncPositionElement), &kSyncPos))
			return false;

#ifdef __MOVIE_MODE__
		return true;
#endif __MOVIE_MODE__

		//Tracenf("CPythonNetworkStream::RecvSyncPositionPacket %d (%d, %d)", kSyncPos.dwVID, kSyncPos.lX, kSyncPos.lY);

		__GlobalPositionToLocalPosition(kSyncPos.lX, kSyncPos.lY);
		m_rokNetActorMgr->SyncActor(kSyncPos.dwVID, kSyncPos.lX, kSyncPos.lY);
	}

	return true;
}

#ifdef ENABLE_OFFLINESHOP_SYSTEM
bool CPythonNetworkStream::SendOfflineShopEndPacket()
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGShop packet_shop;
	packet_shop.header = HEADER_CG_OFFLINE_SHOP;
	packet_shop.subheader = SHOP_SUBHEADER_CG_END;

	if (!Send(sizeof(packet_shop), &packet_shop))
	{
		Tracef("SendOfflineShopEndPacket Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopBuyPacket(DWORD vid, BYTE bPos, DWORD itemID)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_BUY;
	PacketShop.vid = vid;
	PacketShop.pos = bPos;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopBuyPacket Error\n");
		return false;
	}
	if (!Send(sizeof(DWORD), &itemID))
	{
		Tracef("SendOfflineShopBuyPacket Error\n");
		return false;
	}
	//TraceError("SendOfflineShopBuyPacket vid=%d sub=%d",vid,bPos);
	return SendSequence();
}

bool CPythonNetworkStream::SendAddOfflineShopItem(TItemPos bDisplayPos, BYTE bPos, long long lPrice)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_ADD_ITEM;

	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendAddOfflineShopItem Error\n");
		return false;
	}

	TOfflineShopAddItem pTable;

	pTable.bDisplayPos = bDisplayPos;
	pTable.bPos = bPos;
	pTable.lPrice = lPrice;
	if (!Send(sizeof(TOfflineShopAddItem), &pTable))
	{
		Tracef("SendAddOfflineShopItem Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendRemoveOfflineShopItem(BYTE bPos, DWORD dwItemID, BYTE bTakeAll)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_REMOVE_ITEM;

	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendRemoveOfflineShopItem Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bPos))
	{
		Tracef("SendRemoveOfflineShopItem Packet Error\n");
		return false;
	}

	if (!Send(sizeof(DWORD), &dwItemID))
	{
		Tracef("SendRemoveOfflineShopItem Packet Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bTakeAll))
	{
		Tracef("SendRemoveOfflineShopItem Packet Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopChangePrice(BYTE bPos, DWORD dwItemID, long long itemPrice, BYTE bAllSameItem)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_CHANGE_PRICE;

	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopChangePrice Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bPos))
	{
		Tracef("SendOfflineShopChangePrice Packet Error\n");
		return false;
	}

	if (!Send(sizeof(DWORD), &dwItemID))
	{
		Tracef("SendOfflineShopChangePrice Packet Error\n");
		return false;
	}

	if (!Send(sizeof(long long), &itemPrice))
	{
		Tracef("SendOfflineShopChangePrice Packet Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bAllSameItem))
	{
		Tracef("SendOfflineShopChangePrice Packet Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendOpenShopSlot(BYTE bPos)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_OPEN_SLOT;

	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOpenShopSlot Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bPos))
	{
		Tracef("SendOpenShopSlot Packet Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendGetBackItems()
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_GET_ITEM;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOpenShopSlot Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendAddTime()
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_ADD_TIME;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOpenShopSlot Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendDestroyOfflineShop()
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_DESTROY_OFFLINE_SHOP;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendDestroyOfflineShop Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendTeleportOfflineShop(const char* shopOwnerName)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_TELEPORT;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendTeleportOfflineShop Packet Error\n");
		return false;
	}
	char ownerName[CHARACTER_NAME_MAX_LEN + 1];
	strcpy(ownerName, shopOwnerName);
	if (!Send(CHARACTER_NAME_MAX_LEN + 1, &ownerName))
	{
		Tracef("SendTeleportOfflineShop Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendTakeOutAllItemsOfflineShop()
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_TAKE_OUT_ALL_ITEM;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendTakeOutAllItemsOfflineShop Packet Error\n");
		return false;
	}
	return SendSequence();
}
bool CPythonNetworkStream::SendMoveItemOfflineMoney(WORD slotPos, WORD targetPos)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_MOVE_ITEM;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendMoveItemOfflineMoney Packet Error\n");
		return false;
	}
	if (!Send(sizeof(WORD), &slotPos))
	{
		Tracef("SendMoveItemOfflineMoney Packet Error\n");
		return false;
	}
	if (!Send(sizeof(WORD), &targetPos))
	{
		Tracef("SendMoveItemOfflineMoney Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendTakeOfflineMoney()
{
	static DWORD s_LastTime = timeGetTime() - 5001;
	if (timeGetTime() - s_LastTime < 5000)
		return true;
	s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_TAKE_MONEY;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendRefreshOfflineShopMoney Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopChangeTitle(const char* title)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_CHANGE_TITLE;
	strcpy(PacketShop.title, title);
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopChangeTitle Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopCheck()
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
		//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_CHECK;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopCheck Packet error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopButton()
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
	//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_BUTTON;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopCheck Packet error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopRemoveLogs()
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
	//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_LOG_REMOVE;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopCheck Packet error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineOpenWithVID(DWORD vid)
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
	//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_OPEN_WITH_VID;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineOpenWithVID Packet error\n");
		return false;
	}
	if (!Send(sizeof(DWORD), &vid))
	{
		Tracef("SendOfflineOpenWithVID Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopChangeDecoration(const char* sign, DWORD vnum, DWORD type)
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
	//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_CHANGE_DECORATION;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopChangeDecoration Packet error\n");
		return false;
	}

	TShopDecoration p;
	snprintf(p.sign, sizeof(p.sign), sign);
	p.vnum = vnum;
	p.type = type;
	if (!Send(sizeof(TShopDecoration), &p))
	{
		Tracef("SendOfflineShopChangeDecoration Packet Error\n");
		return false;
	}

	return SendSequence();
}
bool CPythonNetworkStream::SendOfflineShopAddItemShortcut(BYTE itemWindow, WORD slotIndex, long long itemPrice)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_ADD_ITEM_SHORTCUT;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopAddItemShortcut Packet error\n");
		return false;
	}

	TItemPos pos(itemWindow, slotIndex);
	if (!Send(sizeof(TItemPos), &pos))
	{
		Tracef("SendOfflineShopAddItemShortcut Packet Error\n");
		return false;
	}
	if (!Send(sizeof(long long), &itemPrice))
	{
		Tracef("SendOfflineShopAddItemShortcut Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopAverageItem(DWORD itemIdx)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_AVERAGE_ITEM;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopAverageItem Packet error\n");
		return false;
	}
	if (!Send(sizeof(DWORD), &itemIdx))
	{
		Tracef("SendOfflineShopAverageItem Packet Error\n");
		return false;
	}
	return SendSequence();
}
#endif

//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
