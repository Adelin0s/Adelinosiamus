#pragma once

typedef std::pair<DWORD, std::string> CRCPair;

void ProcessScanner_Destroy();
bool ProcessScanner_Create();
void ProcessScanner_ReleaseQuitEvent();

bool ProcessScanner_PopProcessQueue(std::vector<CRCPair>* pkVct_crcPair);
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
