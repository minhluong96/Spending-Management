#include "stdafx.h"
#include "TableItem.h"


TableItem::TableItem(WCHAR *type, WCHAR *content, long amount)
{
	this->type = new WCHAR[BUFFSIZE];
	this->content = new WCHAR[BUFFSIZE];

	wcscpy_s(this->type, BUFFSIZE, type);
	wcscpy_s(this->content, BUFFSIZE, content);
	this->amount = amount;
}


TableItem::~TableItem()
{

}

WCHAR* TableItem::GetType()
{
	return type;
}

WCHAR* TableItem::GetContent()
{
	return content;
}

long TableItem::GetAmount()
{
	return amount;
}
