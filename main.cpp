
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <dedkam2@wp.pl> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#define IDT_TIMER1 2
#define IDT_TIMER2 3
#define LICENSE 4

WNDCLASSEX wc;
HWND hwnd, TEXT, BUTTON, DISPLAY;
MSG msg;
int i;
char textCut[3];
					    
string intToStr(int n)
{
    string tmp;
    if(n < 0)
	{
      	tmp = "-";
      	n = -n;
    }
    if (n > 9) tmp += intToStr(n / 10);
    tmp += n % 10 + 48;
    return tmp;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE:
		{
			TEXT = CreateWindow(
				"EDIT",
				"",
				WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
				0, 150, 200, 20,
				hwnd, NULL, NULL, NULL);
				
			BUTTON = CreateWindow(
				"BUTTON",
				"START",
				WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
				190, 150, 80, 20,
				hwnd, (HMENU) 1, NULL, NULL);
				
				CreateWindow(
				"BUTTON",
				"?",
				WS_VISIBLE | WS_CHILD,
				270, 150, 20, 20,
				hwnd, (HMENU) LICENSE, NULL, NULL);
				
			DISPLAY = CreateWindow(
				"STATIC",
				"SET",
				WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_READONLY,
				5, 5, 280, 140,
				hwnd, NULL, NULL, NULL);
				
			HFONT hFont = CreateFont (140, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
   			SendMessage (DISPLAY, WM_SETFONT, WPARAM (hFont), TRUE);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		
		case WM_COMMAND:
		{
			case WM_TIMER:
				{
					switch (wParam) 
				    { 
				        case IDT_TIMER1: 
				        {
				        	i--;
							string x = intToStr(i);
							SetWindowText(DISPLAY, x.c_str());
							if (i == 0)
							{
								SetTimer(hwnd, IDT_TIMER2, 1000, (TIMERPROC) NULL);
							}
				        	break;
						}
						case IDT_TIMER2:
						{
							system("SHUTDOWN -s -t 1");
							break;
						}
				    } 
				}
				
			switch(LOWORD(wParam))
			{
				case 1:
					{
						GetWindowText(TEXT, &textCut[0], 4);
						i = atoi (textCut);
						EnableWindow(TEXT, FALSE);
						EnableWindow(BUTTON, FALSE);
						SetWindowText(TEXT, "COUNTING...");
						SetTimer(hwnd, IDT_TIMER1, 60000, (TIMERPROC) NULL);
                       	string x = intToStr(i);
						SetWindowText(DISPLAY, x.c_str());
						break;
					}
				case LICENSE:
					{
						MessageBox(hwnd,"\"THE BEER-WARE LICENSE\" (Revision 42):\n<dedkam2@wp.pl> wrote this file. As long as you retain this notice you\ncan do whatever you want with this stuff. If we meet some day, and you\nthink this stuff is worth it, you can buy me a beer in return." ,"LICENSE - BY DAMIAN KREÑSKI", MB_OK);
						break;
					}
			}
			break;
		}

		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc;
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+3);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); 

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"WindowClass","SHUTDOWN V1.0",
		WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WM_TIMER,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		300,
		205,
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
