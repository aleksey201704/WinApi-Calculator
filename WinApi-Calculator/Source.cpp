#define _CRT_SECURE_NO_WARNINNGS
#pragma warning(suppress : 4996)
#include<Windows.h>
#include<cstdio>
#include"resource.h"


CONST CHAR g_szClassName[] = "MyWindowsClass";
CONST CHAR g_szWindowTitle[] = "My First Window";

CONST INT g_SCREEN_HEIGHT = 25;
CONST INT g_iBtnSize = 50; // Size Button
CONST INT g_interval = 10; // Size in pixel
CONST INT g_START_X = 10;
CONST INT g_START_Y = 10;

CONST INT G_SIZE = 256;
CHAR sz_Summand[G_SIZE] = {};
CHAR sz_Addend[G_SIZE] = {};
BOOL G_PLUS;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
INT SUMMA(BOOL G_PLUS, CHAR sz_Summand[G_SIZE], CHAR sz_Append[G_SIZE]);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpCmdLine, int nCmdShow)
{
	// Регистрация класса окна
	WNDCLASSEX wc; // wc - Window Class
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc; // Имя функции - указатель на функцию
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInstance,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = NULL;
	wc.lpszClassName =  g_szClassName;
	

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Class NULL", "Error", MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	// Создание окна
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CXSCREEN);
	int window_width = g_START_X * 3 + (g_iBtnSize + g_interval) * 5 + g_interval;
	int window_height = g_START_Y * 5 + g_SCREEN_HEIGHT + (g_iBtnSize + g_interval) * 4 + g_interval * 3;
	int start_x = screen_width * .125;
	int start_y = screen_height * .125;


	HWND hwnd = CreateWindowEx
	(
		NULL,	//exStyle
		g_szClassName,
		g_szWindowTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU /*| WS_THICKFRAME*/ | WS_MINIMIZEBOX,// | WS_MAXIMIZEBOX,
		//WS_OVERLAPPEDWINDOW,	//Главное окно, у которого есть строка заголовка, 
		//кнопки управления окном, может изменяться по размерам....
		start_x, start_y,	//Положение окна на экране
		window_width, window_height,	//Размер окна
		NULL,	//Parent Window
		NULL,	//ID ресурса меню, если окно главное (OVERLAPPED),
				//или ID этого окна, если окно дочернее
		hInstance,
		NULL
	);

	if (hwnd == NULL) {
		MessageBox(NULL, "NO CreatWindow", "Error", MB_OK | MB_ICONINFORMATION);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow); // Задает режим отображения окна
	UpdateWindow(hwnd); // Рисует окно
	// Запуск цикла сообщений
	MSG	msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (WPARAM)msg.wParam;

}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_CREATE:
	{ 
		CreateWindowEx
		(
			0, "Edit", "",
			WS_BORDER | WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY,
			g_START_X, g_START_Y,
			(g_iBtnSize + g_interval) * 4 - g_interval, g_SCREEN_HEIGHT,
			hwnd, (HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);

		
		// Построение кнопок

		INT digit;
		digit = 1;
		CHAR sz_digit[]="0";
		

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = '0' + (CHAR)digit;
				CreateWindowEx
				(
					0, "Button",sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					g_START_X + (g_iBtnSize + g_interval) * j,
					g_START_Y + g_SCREEN_HEIGHT + g_interval + (g_iBtnSize + g_interval) * (2 - i),
					g_iBtnSize, g_iBtnSize,
					hwnd, (HMENU)(IDC_BUTTON_0 + digit),
					GetModuleHandle(NULL), NULL
				);
				digit++;
			}
		}

		CreateWindowEx
		(
			0,"Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_START_X + g_iBtnSize * 2 + g_interval * 2,
			g_START_Y + g_SCREEN_HEIGHT + (g_iBtnSize + g_interval) * 3+g_interval,
			g_iBtnSize,g_iBtnSize,
			hwnd, (HMENU) (IDC_BUTTON_POINT),
			GetModuleHandle(NULL),NULL
		);

		CreateWindowEx
		(
			0, "Button","0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_START_X ,
			g_START_Y + g_SCREEN_HEIGHT + (g_iBtnSize + g_interval) * 3 + g_interval,
			g_iBtnSize*2+g_interval, g_iBtnSize,
			hwnd, (HMENU)(IDC_BUTTON_0),
			GetModuleHandle(NULL), NULL
		);

		CreateWindowEx
		(
			0, "Button", "+",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_START_X + g_iBtnSize * 3 + g_interval * 3,
			g_START_Y + g_SCREEN_HEIGHT + g_interval,
			g_iBtnSize, g_iBtnSize,
			hwnd, (HMENU)(IDC_BUTTON_PLUS),
			GetModuleHandle(NULL), NULL
		);

		CreateWindowEx
		(
			0,"Button","-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_START_X + g_iBtnSize*3+g_interval*3,
			g_START_Y + g_SCREEN_HEIGHT + g_iBtnSize+g_interval*2,
			g_iBtnSize,g_iBtnSize,
			hwnd,(HMENU) (IDC_BUTTON_MINUS),
			GetModuleHandle(NULL),NULL
		);
		
		CreateWindowEx
		(
			0,"Button","=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_START_X + g_iBtnSize*3 + g_interval*3,
			g_START_Y+ g_SCREEN_HEIGHT+g_iBtnSize*2+g_interval*3,
			g_iBtnSize,g_iBtnSize*2+g_interval,
			hwnd,(HMENU) (IDC_BUTTON_EQUAL),
			GetModuleHandle(NULL),NULL
		);



	} // Область применения
		break;
	case WM_COMMAND:
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		
		SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
		
		CHAR sz_digit[2] = {};
    	
		if (strlen(sz_buffer) == 15) break; // Ограничываем количество символов на Edit
		
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			
			
			if (G_PLUS)
			{	
				memset(sz_buffer,NULL,SIZE); // Почистил буфер
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
				G_PLUS = FALSE;

			}
			
			
			sz_digit[0] = LOWORD(wParam) - 952;
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);

			//if (G_PLUS) strcpy(sz_Addend, sz_buffer); // Второе значение для сложения
			
		}

		if (LOWORD(wParam) == IDC_BUTTON_POINT) // Нажатие точки
		{
			if (strchr(sz_buffer, '.'))break;
			strcat(sz_buffer, ".");
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}

		if(LOWORD(wParam)==IDC_BUTTON_PLUS) // нажатие знака плюс
		{
			G_PLUS = TRUE;

			if (strlen(sz_Summand) > 0)
			{
				strcpy(sz_Addend, sz_buffer);
				INT n,a,b;
				CHAR s[256] = {};
				a = (INT)sz_Addend;
				b = (INT)sz_Summand;
				n = a + b;
				(CHAR)n;
				if (n>0) MessageBox(hwnd,n, "sd", MB_OK);

				break;
			}
			if (strlen(sz_buffer)==0) break; // Проверяем на количество символов
			if (strchr(sz_buffer, '+'))break;
			
			if(strlen(sz_Summand) == 0) strcat(sz_buffer, "+");
			strcpy(sz_Summand, sz_buffer);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);

		}

		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)  // Нажатие знака равно
		{	
			//strcat(sz_buffer, "=");
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
			
			//MessageBox(hwnd, sz_Summand, "Summand", MB_OK);
		}
	}
	break;
	//case WM_CLOSE: DestroyWindow(hwnd);
	case WM_DESTROY:
		PostQuitMessage(0); // Закрытие окна
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);

	
	}
	return FALSE;
}

INT SUMMA(BOOL G_PLUS, CHAR sz_Summand[G_SIZE], CHAR sz_Append[G_SIZE])
{
	if (G_PLUS)
	{

	}
	return 0;
}

