// MyBrainWar.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QuanLyChiTieu.h"

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MyProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_QUANLYCHITIEU, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUANLYCHITIEU));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_QUANLYCHITIEU));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_QUANLYCHITIEU);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE | WS_SYSMENU,
		350, 100, 600, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, onCreate);
		HANDLE_MSG(hWnd, WM_PAINT, onPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, onDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, onCommand);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void onPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);

	SaveRect(hWnd);
}

void onDestroy(HWND hWnd)
{
	SaveData();
	PostQuitMessage(0);
}

BOOL onCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	itemCount = 0;
	totalAmount = 0;
	LoadRect(hWnd);

	// Take system's font
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	HFONT bigFont = CreateFont(40, 15, 0, 700, 0, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH, TEXT("Segoe UI"));

	HWND hwnd = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME, 15, 15, 550, 100, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Thêm chi tiêu", WS_CHILD | WS_VISIBLE | SS_CENTER, 30, 10, 70, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Loại chi tiêu:", WS_CHILD | WS_VISIBLE , 40, 40, 80, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Nội dung chi tiêu:", WS_CHILD | WS_VISIBLE , 180, 40, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Số tiền:", WS_CHILD | WS_VISIBLE , 320, 40, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	Type = CreateWindowEx(0, L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_SORT, 40, 60, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(Type, CB_ADDSTRING, 0, LPARAM(L"Ăn uống"));
	SendMessage(Type, CB_ADDSTRING, 0, LPARAM(L"Di chuyển"));
	SendMessage(Type, CB_ADDSTRING, 0, LPARAM(L"Nhà cửa"));
	SendMessage(Type, CB_ADDSTRING, 0, LPARAM(L"Nhu yếu phẩm"));
	SendMessage(Type, CB_ADDSTRING, 0, LPARAM(L"Dịch vụ"));
	SendMessage(Type, CB_ADDSTRING, 0, LPARAM(L"Xe cộ"));
	SendMessage(Type, WM_SETFONT, WPARAM(hFont), TRUE);
	
	Content = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 60, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(Content, WM_SETFONT, WPARAM(hFont), TRUE);

	Amount = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 320, 60, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(Amount, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"BUTTON", L"Thêm", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 460, 58, 80, 24, hWnd, (HMENU)IDB_BUTTON1, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE); 

	hwnd = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME, 15, 140, 550, 250, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Danh sách các chi tiêu", WS_CHILD | WS_VISIBLE | SS_CENTER, 30, 135, 115, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME, 15, 415, 550, 110, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Thống kê chi tiêu", WS_CHILD | WS_VISIBLE | SS_CENTER, 30, 410, 90, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Tổng cộng chi tiêu:", WS_CHILD | WS_VISIBLE, 140, 440, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	Total = CreateWindowEx(0, L"STATIC", L"0", WS_CHILD | WS_VISIBLE | SS_LEFT, 250, 440, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(Total, WM_SETFONT, WPARAM(hFont), TRUE);

	CreateTable(hWnd);
	LoadData();

	return true;
}

void onCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDM_CLEAR:
		ClearData();
		break;
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;

	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	
	case IDB_BUTTON1:
		int size;

		//get type
		size = GetWindowTextLength(Type);
		WCHAR *type = new WCHAR[size + 1];
		GetWindowText(Type, type, size + 1);
		
		//get content
		size = GetWindowTextLength(Content);
		WCHAR *content = new WCHAR[size + 1];
		GetWindowText(Content, content, size + 1);

		//get amount
		size = GetWindowTextLength(Amount);
		WCHAR *amount = new WCHAR[size + 1];
		GetWindowText(Amount, amount, size + 1);

		//Check
		if (wcscmp(content, L"") == 0 || wcscmp(amount, L"") == 0 || wcscmp(type, L"") == 0)
		{
			MessageBox(hWnd,L"Please put info in the box",L"Error",0);
			return;
		}

		TableItem *tableItem= new TableItem(type, content, _wtoi(amount));
		list.push_back(tableItem);
		delete[]content;
		delete[]type;
		delete[]amount;
		AddItem(list[itemCount]);
		
	}
}

void CreateTable(HWND hWnd)
{
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	Table = CreateWindowEx(0, WC_LISTVIEW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LVS_REPORT, 40, 170, 500, 200, hWnd, NULL, hInst, NULL);
	SendMessage(Table, WM_SETFONT, WPARAM(hFont), TRUE);

	LVCOLUMN Col;

	Col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	Col.fmt = LVCFMT_LEFT;

	Col.cx = 110;
	Col.pszText = L"Loại";
	ListView_InsertColumn(Table, 0, &Col);

	Col.fmt = LVCFMT_LEFT;
	Col.cx = 230;
	Col.pszText = L"Nội dung";
	ListView_InsertColumn(Table, 1, &Col);

	Col.cx = 140;
	Col.fmt = LVCFMT_LEFT;
	Col.pszText = L"Số tiền";
	ListView_InsertColumn(Table, 2, &Col);

}

void AddItem(TableItem *tableItem)
{
	LV_ITEM item;
	item.mask = LVIF_TEXT;
	item.iItem = itemCount;

	item.iSubItem = 0;
	item.pszText = tableItem->GetType();
	ListView_InsertItem(Table, &item);

	WCHAR *temp = new WCHAR[BUFFSIZE];
	swprintf(temp, BUFFSIZE,L"%d", tableItem->GetAmount());

	ListView_SetItemText(Table, itemCount, 1, tableItem->GetContent());
	ListView_SetItemText(Table, itemCount, 2, temp);
	itemCount++;
	totalAmount += tableItem->GetAmount();
	ShowTotal();
}

void SaveData()
{
	WCHAR *path = new WCHAR[BUFFSIZE];
	WCHAR *buff = new WCHAR[BUFFSIZE];
	swprintf(buff, BUFFSIZE, L"%d", list.size());

	GetCurrentDirectory(BUFFSIZE, path);
	wcscat_s(path, BUFFSIZE, L"\\data.ini");
	WritePrivateProfileString(L"data", L"count", buff, path);

	for (int i = 0; i < list.size(); i++)
	{
		WCHAR *amount = new WCHAR[BUFFSIZE];
		swprintf(buff, BUFFSIZE, L"%d", i);
		swprintf(amount, BUFFSIZE, L"%d", list[i]->GetAmount());
		WritePrivateProfileString(buff, L"Type", list[i]->GetType(), path);
		WritePrivateProfileString(buff, L"Content", list[i]->GetContent(), path);
		WritePrivateProfileString(buff, L"Amount", amount, path);
	}
}

void LoadData()
{
	WCHAR *path = new WCHAR[BUFFSIZE];
	WCHAR *buff = new WCHAR[BUFFSIZE];
	int count;

	//get path
	GetCurrentDirectory(BUFFSIZE, path);
	wcscat_s(path, BUFFSIZE, L"\\data.ini");

	//get count
	GetPrivateProfileString(L"data", L"count", L"0", buff, BUFFSIZE, path);
	count = _wtoi(buff);

	//get single item and add to list
	for (int i = 0; i < count; i++)
	{
		TableItem *temp;
		WCHAR *amount = new WCHAR[BUFFSIZE];
		WCHAR *type = new WCHAR[BUFFSIZE];
		WCHAR *content = new WCHAR[BUFFSIZE];
		swprintf(buff, BUFFSIZE, L"%d", i);
		GetPrivateProfileString(buff, L"Type", L"Unknown", type, BUFFSIZE, path);
		GetPrivateProfileString(buff, L"Content", L"Unknown", content, BUFFSIZE, path);
		GetPrivateProfileString(buff, L"Amount",L"0", amount, BUFFSIZE, path);
		temp = new TableItem(type, content, _wtoi(amount));
		AddItem(temp);
		list.push_back(temp);
	}
}

void ShowTotal()
{
	WCHAR *buff = new WCHAR[BUFFSIZE];
	swprintf(buff, BUFFSIZE, L"%d", totalAmount);
	SetWindowText(Total, buff);
}

void ClearData()
{
	WCHAR *path = new WCHAR[BUFFSIZE];

	//get path
	GetCurrentDirectory(BUFFSIZE, path);
	wcscat_s(path, BUFFSIZE, L"\\data.ini");

	DeleteFile(path);
	list.clear();
	ListView_DeleteAllItems(Table);
	totalAmount = 0;
	itemCount = 0;
	SetWindowText(Total, L"0");
}