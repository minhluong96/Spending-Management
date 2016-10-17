#pragma once

#include "resource.h"
#include <windowsX.h>
#include <winuser.h>
#include <commctrl.h>
#include <ctime>
#include "Settings.h"
#include "TableItem.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#define MAX_LOADSTRING 100
#define BUFFSIZE 260

void onCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
void onPaint(HWND hWnd);
void onDestroy(HWND hWnd);
BOOL onCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void CreateTable(HWND hWnd);
void AddItem(TableItem *tableItem);
void SaveData();
void LoadData();
void ShowTotal();
void ClearData();

HWND Type, Content, Amount, Table, Total;
int itemCount;
long totalAmount;
vector<TableItem*> list;

//Global variables
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

