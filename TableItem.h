#pragma once
#define BUFFSIZE 260

class TableItem
{
	WCHAR *type;
	WCHAR *content;
	long amount;
public:
	TableItem(WCHAR *type, WCHAR *content, long amount);
	WCHAR* GetType();
	WCHAR* GetContent();
	long GetAmount();
	~TableItem();
};

