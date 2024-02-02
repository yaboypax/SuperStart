#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

#include <Mmdeviceapi.h>
#include <Functiondiscoverykeys_devpkey.h>

#include "IO.h"
#include "resource.h"

HWND inputCombo, outputCombo;
static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("SuperStart");
HINSTANCE hInst;

IOManager ioManager;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)

{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Windows Desktop Guided Tour"), NULL);
		return 1;
	}

	hInst = hInstance;

	// The parameters to CreateWindowEx explained:
	// WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 200,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
	{
		MessageBox(NULL, _T("Call to CreateWindowEx failed!"), _T("Windows Desktop Guided Tour"), NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
	{
		IMMDeviceEnumerator* pEnumerator = NULL;
		const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
		const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

		HRESULT hr = CoInitialize(NULL);
		if (FAILED(hr)) {
			// Handle error
		}

		
		hr = CoCreateInstance(
			CLSID_MMDeviceEnumerator, NULL,
			CLSCTX_ALL, IID_IMMDeviceEnumerator,
			(void**)&pEnumerator);

		if (FAILED(hr)) {
			// Handle error
		}

		IMMDeviceCollection* pCollection = NULL;
		hr = pEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pCollection);
		if (FAILED(hr)) {
			// Handle error
		}

		UINT count;
		pCollection->GetCount(&count);
		std::vector<std::wstring> deviceNames;
		for (UINT i = 0; i < count; ++i) {
			IMMDevice* pDevice = NULL;
			hr = pCollection->Item(i, &pDevice);
			if (SUCCEEDED(hr)) {
				IPropertyStore* pProps = NULL;
				hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
				if (SUCCEEDED(hr)) {
					PROPVARIANT varName;
					PropVariantInit(&varName);
					hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
					if (SUCCEEDED(hr)) {
						deviceNames.push_back(varName.pwszVal);
						PropVariantClear(&varName);
					}
					pProps->Release();
				}
				pDevice->Release();
			}
		}
		pCollection->Release();
		pEnumerator->Release();
		CoUninitialize();

		inputCombo = CreateWindowA("COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_HASSTRINGS, 
									20, 10, 300, inputOptions.size() * 30, hWnd, (HMENU)1000, hInst, NULL);

		outputCombo = CreateWindowA("COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_HASSTRINGS,
									20, 60, 300, outputOptions.size() * 30, hWnd, (HMENU)1001, hInst, NULL);

		if (inputCombo == NULL || outputCombo == NULL)
		{
			DWORD dwError = GetLastError();
		}

		for (const auto& input : inputOptions) {
			SendMessageA(inputCombo, CB_ADDSTRING, 0, (LPARAM)input.c_str());
		}

		for (const auto& output : outputOptions) {
			SendMessageA(outputCombo, CB_ADDSTRING, 0, (LPARAM)output.c_str());
		}


		CreateWindowA( "BUTTON", "Launch!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						350, 10, 100, 30, hWnd, (HMENU)1002, hInst, NULL);

		CreateWindowA("BUTTON", "Kill!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						350, 60, 100, 30, hWnd, (HMENU)1003, hInst, NULL);

		ioManager.read();

		break;

	} break;
	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == 1000)
		{
			int selectedIndex = SendMessage(inputCombo, CB_GETCURSEL, 0, 0);
			int length = SendMessage(inputCombo, CB_GETLBTEXTLEN, (WPARAM)selectedIndex, 0);

			std::wstring selectedString;
			if (length != CB_ERR) {
				selectedString.resize(length+1);
				SendMessage(inputCombo, CB_GETLBTEXT, (WPARAM)selectedIndex, (LPARAM)selectedString.data());
			}
			std::string narrowString(selectedString.begin(), selectedString.end());
			ioManager.addInput(narrowString);
			break;
		}

		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == 1001)
		{
			int selectedIndex = SendMessage(outputCombo, CB_GETCURSEL, 0, 0);
			int length = SendMessage(outputCombo, CB_GETLBTEXTLEN, (WPARAM)selectedIndex, 0);

			std::wstring selectedString;
			if (length != CB_ERR) {
				selectedString.resize(length+1);
				SendMessage(outputCombo, CB_GETLBTEXT, (WPARAM)selectedIndex, (LPARAM)selectedString.data());
			}
			std::string narrowString(selectedString.begin(), selectedString.end());
			ioManager.addOutput(narrowString);
			break;
		}

		if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == 1002)
		{
			ioManager.write();
			std::system("sclang SuperStart.scd");
		}

		if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == 1003)
		{
			std::system("sclang Kill.scd");
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}