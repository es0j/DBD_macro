//Dead by daylight macro que aperta espaço.
// by esoj
//
// REFERENCIAS:
//
// keystroke.c - Pauses, then simulates a key press
// and release of the "A" key.
//
// Written by Ted Burke - last updated 17-4-2012
//
// To compile with MinGW:
//
//      gcc -o keystroke.exe keystroke.c
//
// To run the program:
//
//      keystroke.exe
//
// ...then switch to e.g. a Notepad window and wait
// 5 seconds for the A key to be magically pressed.
//

// Because the SendInput function is only supported in
// Windows 2000 and later, WINVER needs to be set as
// follows so that SendInput gets defined when windows.h
// is included below.
#define WINVER 0x0500
#include <windows.h>
#include <iostream>
using namespace std;

bool rodando=0;
//checa se o outro botao lateral do mouse foi pressionado
bool checar()
{
	if (GetAsyncKeyState(VK_XBUTTON1) & 0x0001 != 0) 
	{
		return true;
	}
	else
		return false;
}
int pressKey()
{
	//referências https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-sendinput
	
	// This structure will be used to create the keyboard
	// input event.
	INPUT ip;
	bool sair=0;

	while (1)
	{

		if (checar())
		{
			Beep(200, 200);
			sair = true;
		}
		// Set up a generic keyboard event.
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0; // hardware scan code for key
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;

		// Press the "space" key
		ip.ki.wVk = 0x20; // virtual-key code for the "space" key
		
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(80);
		             
		if (checar())
		{
			Beep(200, 200);
			sair = true;
		}

		// Release the "SPACE" key
		ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(80);

		if (sair)
		{
			break;
		}

	}
	return 0;                 
}
void Stealth()
{
	//poe o processo em segundo plano. evita que a janela do console apareça
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}
int main()    
{
	Stealth();
	while (1)
	{
		// confere se o botão da lateral do mouse esta pressionado
		if (GetAsyncKeyState(VK_XBUTTON2) & 0x0001 != 0) 
		{           
			cout << "inciaidno !!" << endl;               
			Beep(440, 200); //emite um alerta sonoro
			pressKey();
			
		}
		Sleep(60); //evita que o processador gaste muitos recursos com este programa            
	}
	
	return 0;      
}                
