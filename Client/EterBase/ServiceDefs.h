#ifndef _EL_SERVICEDEFS_H_
#define _EL_SERVICEDEFS_H_

#define _IMPROVED_PACKET_ENCRYPTION_
//#define __PERFORMANCE_CHECK__

enum EEterPackKeySet
{
	COMPRESS_EIX = 1,
	COMPRESS_EPK = 2,
	COMPRESS_ITEM = 3,
	COMPRESS_MOB = 4,

	COMPRESS_BRICK_SIZE = 4,
	COMPRESS_BIRCK_LEN = 10,
	COMPRESS_KEY_SIZE = COMPRESS_BIRCK_LEN + COMPRESS_BRICK_SIZE + 2,
};

static const char* s_strEIX = ".idx"; // EterPack Index
static const char* s_strEPK = ".data"; // EterPack

static std::string s_strEterPackSecurityKey[COMPRESS_BRICK_SIZE] = {
	std::string(AY_OBFUSCATE("1739360480")),
	std::string(AY_OBFUSCATE("1820016931")),
	std::string(AY_OBFUSCATE("823354584")),
	std::string(AY_OBFUSCATE("539638100"))
};

static std::string s_strEterPackKey[COMPRESS_BRICK_SIZE] = {
	std::string(AY_OBFUSCATE("1217543448")),
	std::string(AY_OBFUSCATE("730298414")),
	std::string(AY_OBFUSCATE("979037318")),
	std::string(AY_OBFUSCATE("1096970918"))
};

static std::string s_strItemProtoKey[COMPRESS_BRICK_SIZE] = {
	std::string(AY_OBFUSCATE("173217")),
	std::string(AY_OBFUSCATE("72619434")),
	std::string(AY_OBFUSCATE("408587239")),
	std::string(AY_OBFUSCATE("27973291"))
};

static std::string s_strMobProtoKey[COMPRESS_BRICK_SIZE] = {
	std::string(AY_OBFUSCATE("4813894")),
	std::string(AY_OBFUSCATE("18955")),
	std::string(AY_OBFUSCATE("552631")),
	std::string(AY_OBFUSCATE("6822045"))
};

#endif //_EL_SERVICEDEFS_H_
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
