#include "stdafx.h"

#include <iostream>
#include <vector>
#include <Windows.h>

#include "proc.h"
#include "mem.h"
#include "ascii.h"

bool bHealth = false, bArmor = false, bRadO2 = false, bAmmo = false, bSword = false;
bool bHammer = false, bGrenades = false, bFlame = false, bDash = false, bPunch = false;

void Menu()
{
	std::cout << "HOTKEY = FUNCTIONS = STATUS\n";
	std::cout << "===========================\n";
	std::cout << "NUM0 = Infinite Health = " << bHealth << "\n";
	std::cout << "NUM1 = Infinite Armor = " << bArmor << "\n";
	std::cout << "NUM2 = Infinite Rad/O2 = " << bRadO2 << "\n";
	std::cout << "NUM3 = Infinite Ammo/Chainsaw = " << bAmmo << "\n";
	std::cout << "NUM4 = Infinite Sword = " << bSword << "\n";
	std::cout << "NUM5 = Infinite Hammer = " << bHammer << "\n";
	std::cout << "NUM6 = Infinite Grenades = " << bGrenades << "\n";
	std::cout << "NUM7 = Infinite Flame Belch = " << bFlame << "\n";
	std::cout << "NUM8 = Infinite Dash = " << bDash << "\n";
	std::cout << "NUM9 = Infinite Blood Punch = " << bPunch << "\n\n";
	std::cout << "INSERT = EXIT TRAINER\n";
}

int main()
{
	
	HANDLE hProcess = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "DOOMEternal Trainer v.1.0\n";
	SetConsoleTextAttribute(hConsole, 12);
	uintptr_t moduleBase = 0, playerPtr = 0, healthAddr = 0, armorAddr = 0;
	const float maxHealth = 999, maxArmor = 999;
	DWORD procId = GetProcId(L"DOOMEternalx64vk.exe");

	if (procId)
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
		moduleBase = GetModuleBaseAddress(procId, L"DOOMEternalx64vk.exe");
		GetAsciiArt();
		SetConsoleTextAttribute(hConsole, 10);
		GetAsciiArtSubTitle();
		getchar();
		ClearScreen();
		Menu();
	}

	else
	{
		std::cout << "DOOMEternal process not found, press enter to exit\n";
		getchar();
		return(0);
	}

	DWORD dwExit = 0;

	while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE)
	{

		playerPtr = moduleBase + 0x06B854A0;
		healthAddr = FindDMAAddy(hProcess, playerPtr, { 0x00,0x20,0x9C });
		armorAddr = FindDMAAddy(hProcess, playerPtr, { 0x00,0x20,0x14C });

		if (GetAsyncKeyState(VK_NUMPAD0) & 1)
		{
			bHealth = !bHealth;
			
			ClearScreen();
			Menu();
		}
		if (bHealth)
		{
			mem::PatchEx((BYTE*)healthAddr, (BYTE*)&maxHealth, sizeof(maxHealth), hProcess);
		}

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			bArmor = !bArmor;
			
			ClearScreen();
			Menu();
		}
		if (bArmor)
		{
			mem::PatchEx((BYTE*)armorAddr, (BYTE*)&maxArmor, sizeof(maxArmor), hProcess);
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			bRadO2 = !bRadO2;
			if (bRadO2)
			{
				mem::NopEx((BYTE*)(moduleBase + 0x18E450A), 5, hProcess);
				mem::NopEx((BYTE*)(moduleBase + 0x1545AD6), 8, hProcess);
				mem::NopEx((BYTE*)(moduleBase + 0x1545956), 8, hProcess);
				ClearScreen();
				Menu();
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x18E450A), (BYTE*)"\xF3\x0F\x11\x4B\x08", 5, hProcess);
				mem::PatchEx((BYTE*)(moduleBase + 0x1545AD6), (BYTE*)"\xF3\x0F\x11\x9A\xD0\x04\x00\x00", 8, hProcess);
				mem::PatchEx((BYTE*)(moduleBase + 0x1545956), (BYTE*)"\xF3\x0F\x11\x9A\xB8\x06\x00\x00", 8, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			bAmmo = !bAmmo;
			if (bAmmo)
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x1CF7BA1), (BYTE*)"\x01\x7B\x40", 3, hProcess);
				ClearScreen();
				Menu();
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x1CF7BA1), (BYTE*)"\x89\x7B\x40", 3, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			bSword = !bSword;
			if (bSword)
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x18E4740), (BYTE*)"\xF3\x0F\x58\x4B\x08", 5, hProcess);
				ClearScreen();
				Menu();
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x18E4740), (BYTE*)"\xF3\x0F\x11\x4B\x08", 5, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			bHammer = !bHammer;
			if (bHammer)
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x1CEC009), (BYTE*)"\x44\x01\xA8\x04\x6A\x02\x00", 7, hProcess);
				ClearScreen();
				Menu();
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x1CEC009), (BYTE*)"\x44\x89\xA8\x04\x6A\x02\x00", 7, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD6) & 1)
		{
			bGrenades = !bGrenades;
			if (bGrenades)
			{
				mem::PatchEx((BYTE*)(moduleBase + 0xA3644C4), (BYTE*)"\xFF\x04\xC7", 3, hProcess);
				ClearScreen();
				Menu();
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0xA3644C4), (BYTE*)"\xFF\x0C\xC7", 3, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD7) & 1)
		{
			bFlame = !bFlame;
			if (bFlame)
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x1C9127A7), (BYTE*)"\xFF\x87\xA0\x6F\x00\x00", 6, hProcess);
				ClearScreen();
				Menu();
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x1C9127A7), (BYTE*)"\xFF\x8F\xA0\x6F\x00\x00", 6, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD8) & 1)
		{
			bDash = !bDash;
			if (bDash)
			{
				mem::NopEx((BYTE*)(moduleBase + 0x18E449B), 5, hProcess);
				ClearScreen();
				Menu();
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x18E449B), (BYTE*)"\xF3\x0F\x11\x4F\x08", 5, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD9) & 1)
		{
			bPunch = !bPunch;
			if (bPunch)
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x1CAC794), (BYTE*)"\xEB\x14", 2, hProcess);
				ClearScreen();
				Menu();
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x1CAC794), (BYTE*)"\x75\x14", 2, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			return(0);
		}

		Sleep(100);

	}

	ClearScreen();
	std::cout << "DOOMEternal process not found, press enter to exit\n";
	getchar();
	return(0);

}