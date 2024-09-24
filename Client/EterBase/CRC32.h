#ifndef __INC_CRC32_H__
#define __INC_CRC32_H__

#include <windows.h>

DWORD GetCRC32(const char* buffer, size_t count);

DWORD GetCaseCRC32(const char* buf, size_t len);
DWORD GetHFILECRC32(HANDLE hFile);
DWORD GetFileCRC32(const char* c_szFileName);
DWORD GetFileSize(const char* c_szFileName);

#endif
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
