#include <windows.h>
#include<stdio.h>
#include <Commdlg.h>
#include <tchar.h>
#include"codc.h"
#pragma once
const char g_szClassName[] = "myWindowClass";

#define IDM_FILE_NEW 1
#define IDM_FILE_OPEN 2
#define IDM_FILE_QUIT 3
void AddMenus(HWND hwnd);
void creare_arbore(char *f);
/*
struct jsw_node
{
	char data[20];
	int level;
	struct jsw_node *st, *dr;
};

struct jsw_node *nil;

*/
/*void citire_nume(FILE* fisier,jsw_node* &radacina)
{
	char nm[100][20];
	fopen("nume.txt", "r");
	int i = 0;
	while (!(feof))
	{
		fgets(nm[i], 20, fisier);
		i++;
	}


}*/
HWND textfield, button,textbox;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
		{
	case WM_CREATE:
		textfield = CreateWindow("STATIC", "Servicii U.M. ATM", WS_VISIBLE | WS_CHILD  , 20, 20, 300, 20, hwnd, NULL, NULL, NULL);
		button = CreateWindow("BUTTON", "Generare Plantoane", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 50, 200, 20, hwnd,NULL, NULL,NULL);
		button = CreateWindow("BUTTON", "Generare Paza", WS_VISIBLE | WS_CHILD | WS_BORDER , 20, 80, 200, 20, hwnd, NULL, NULL, NULL);
		textbox = CreateWindow("EDIT", "Introduceti numele studentului", WS_BORDER | WS_CHILD | WS_VISIBLE, 20, 110, 200, 20,hwnd,NULL,NULL,NULL);
		button = CreateWindow("BUTTON", "Verifica!", WS_VISIBLE | WS_CHILD | WS_BORDER, 240,110, 70, 20, hwnd, (HMENU) 1, NULL, NULL);
		AddMenus(hwnd);
		
		break;
	
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1:
			::MessageBeep(MB_ICONERROR);
			::MessageBox(hwnd, "Studentul nu a fost gasit!", "Rezultatul cautarii", MB_OK);
			break;

		case IDM_FILE_OPEN:
		{
							  OPENFILENAME ofn;
							  char szFileName[MAX_PATH] = "";
							  ZeroMemory(&ofn, sizeof(ofn));
							  ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
							  ofn.hwndOwner = hwnd;
							  ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
							  ofn.lpstrFile = szFileName;
							  ofn.nMaxFile = MAX_PATH;
							  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
							  ofn.lpstrDefExt = "txt";
							  if (GetOpenFileName(&ofn))
							  {
								  creare_arbore(szFileName);
							  }
		}

		case IDM_FILE_QUIT:

			SendMessage(hwnd, WM_CLOSE, 0, 0);
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

void AddMenus(HWND hwnd) {

	HMENU hMenubar;
	HMENU hMenu;

	hMenubar = CreateMenu();
	hMenu = CreateMenu();

	AppendMenuW(hMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
	AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Quit");

	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");
	SetMenu(hwnd, hMenubar);
}
HWND hwnd;

/*
// mai jos creez arborele 
struct jsw_node *split(struct jsw_node *root)
{
	if (root == NULL)
		return root;
	else
	if (root->dr == NULL)
		return root;
	else
	if (root->dr->dr == NULL)
		return root;
	if (root->dr->dr->level == root->level && root->level != 0)
	{
		struct jsw_node *save = root;
		root = root->dr;
		save->dr = root->st;
		root->st = save;
		++root->level;
		root->dr = split(root->dr);
	}
}
struct jsw_node *skew(struct jsw_node *root)
{
	if (root == NULL)
		return NULL;
	if ((root->level != 0) && (root->st != NULL))
	{
		if (root->st->level == root->level)
		{
			struct jsw_node *save = root;

			root = root->st;
			save->st = root->dr;
			root->dr = save;
		}

		root->dr = skew(root->dr);
	}

	return root;
}
struct jsw_node *make_node(char data[20], int level)
{
	struct jsw_node *rn = (jsw_node*)calloc(1, sizeof *rn);

	if (rn == NULL)
	{
		return NULL;
	}
	strcpy(rn->data, data);
	rn->level = level;
	rn->st = rn->dr = nil;

	return rn;
}
struct jsw_node *jsw_insert(struct jsw_node *root, char  data[20])
{
	if (root == nil)
	{
		return make_node(data, 1);
	}
	else
	{
		//modifica
		if (strcmp(data, root->data)<0)
		{
			root->st = jsw_insert(root->st, data);
			root = skew(root);
			root = split(root);
		}
		else
		{
			root->dr = jsw_insert(root->dr, data);
			root = skew(root);
			root = split(root);
		}
	}

	return root;
}*/
jsw_node* rad;

void creare_arbore(char *f)
{
	char nume[30];
	FILE* pf;
	pf = fopen(f, "r");
	while (!(feof(pf)))
	{
		fgets(nume, 20, pf);
		rad = jsw_insert(rad, nume);
		//MessageBox(hwnd, nume, "Student", MB_OK);
	}
}

