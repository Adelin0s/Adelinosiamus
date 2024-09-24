#include "StdAfx.h"
#include "SymTable.h"

using namespace std;

CSymTable::CSymTable(int aTok, string aStr) : dVal(0), token(aTok), strlex(aStr)
{
}

CSymTable::~CSymTable()
{
}
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
