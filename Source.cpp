#include <windows.h>
#include<stdio.h>
const char g_szClassName[] = "myWindowClass";
typedef struct NOD { NOD* st;
					 NOD* dr;
					 char nume[20];
};
NOD* radacina;
void citire_nume(FILE* fisier,NOD* &radacina)
{
	char nm[100][20];
	fopen("nume.txt", "r");
	int i = 0;
	while (!(feof))
	{
		fgets(nm[i], 20, fisier);
		i++;
	}

}
HWND textfield, button,textbox;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
		{
	case WM_CREATE:
		textfield = CreateWindow("STATIC", "Servicii U.M. ATM", WS_VISIBLE | WS_CHILD, 20, 20, 300, 20, hwnd, NULL, NULL, NULL);
		button = CreateWindow("BUTTON", "Generare Plantoane", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 50, 200, 20, hwnd,NULL, NULL,NULL);
		button = CreateWindow("BUTTON", "Generare Paza", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 80, 200, 20, hwnd, NULL, NULL, NULL);
		textbox = CreateWindow("EDIT", "Introduceti numele studentului", WS_BORDER | WS_CHILD | WS_VISIBLE, 20, 110, 200, 20,hwnd,NULL,NULL,NULL);
		button = CreateWindow("BUTTON", "Verifica!", WS_VISIBLE | WS_CHILD | WS_BORDER, 240,110, 70, 20, hwnd, NULL, NULL, NULL);
		break;
	
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:

		return DefWindowProc(hwnd, msg, wParam, lParam);
		}

		return 0;
	}
}
HWND WINAPI CreateWindowEx(
	_In_     DWORD     dwExStyle,
	_In_opt_ LPCTSTR   lpClassName,
	_In_opt_ LPCTSTR   lpWindowName,
	_In_     DWORD     dwStyle,
	_In_     int       x[30],
	_In_     int       y[30],
	_In_     int       nWidth[10],
	_In_     int       nHeight[10],
	_In_opt_ HWND      hWndParent,
	_In_opt_ HMENU     hMenu,
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ LPVOID    lpParam
	);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		
		WNDCLASSEX wc;
		HWND hwnd;
		MSG Msg;
		//Step 1: Registering the Window Class
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = g_szClassName;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, "Window Registration Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
			return 0;
		}
		// Step 2: Creating the Window
		hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			g_szClassName,
			"The Academy organizer",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 500, 320,
			NULL, NULL, hInstance, NULL);
		if (hwnd == NULL)
		{
			MessageBox(NULL, "Window Creation Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
			return 0;
		}
		ShowWindow(hwnd, nCmdShow);
		UpdateWindow(hwnd);
		// Step 3: The Message Loop
		while (GetMessage(&Msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		return Msg.wParam;
	}

