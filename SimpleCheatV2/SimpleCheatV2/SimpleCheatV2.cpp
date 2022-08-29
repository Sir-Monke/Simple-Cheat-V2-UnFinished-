#include <iostream>
#include <sstream>
#include <windows.h>
#include "stdafx.h"
#include "proc.h"
#include "mem.h"
#include "Vector3.h"
#include "Menu.h"

int main()
{
	float oldHeight = 4.5, newHeight = 6;
	int grenade = 50, speed = 2, newGravity = 1, oldGravity = 0, totalPlayerCount = 0, health = 5000, armor = 100, ammo = 100;
	uintptr_t moduleBase = 0, localPlayerPtr = 0, localEntityPtr = 0, playerOffsets = 0;
	uintptr_t playerHealth = 0, playerAmmo = 0, playerGravity = 0, playerArmor = 0, playerGranade = 0, playerSpeed = 0, playerHeight = 0, playerTeam = 0, entTeam = 0;
	uintptr_t totalPlayers = 0, playerPosX = 0, playerPosY = 0, playerPosZ = 0, entPosX = 0, entPosY = 0, entPosZ = 0, localPlayerPitch = 0, localPlayerYaw = 0, localPlayerRoll = 0, entPitch = 0, entYaw = 0, entRoll = 0;
	bool bKillaura = false, bAmmo = false, bGravity = false, bSpeed = false, bHealth = false, bArmor = false, bGranade = false, bPlayerHeight = false;
	HANDLE hProcess = 0;
	DWORD procId = GetProcId(L"ac_client.exe");
	if (procId)
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
		moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");
		//
		localPlayerPtr = moduleBase + 0x10f4f4;
		localEntityPtr = moduleBase + 0x10f4f8;
		//
		playerHealth = FindDMAAddy(hProcess, localPlayerPtr, { 0xF8 });
		playerAmmo = FindDMAAddy(hProcess, localPlayerPtr, { 0x148 });
		playerGranade = FindDMAAddy(hProcess, localPlayerPtr, { 0x158 });
		playerArmor = FindDMAAddy(hProcess, localPlayerPtr, { 0xFC });
		playerSpeed = FindDMAAddy(hProcess, localPlayerPtr, { 0x80 });
		playerGravity = FindDMAAddy(hProcess, localPlayerPtr, { 0x54 });
		playerHeight = FindDMAAddy(hProcess, localPlayerPtr, { 0x5C });
		playerTeam = FindDMAAddy(hProcess, localPlayerPtr, { 0x32C });
		playerPosX = FindDMAAddy(hProcess, localPlayerPtr, { 0x34 });
		playerPosY = FindDMAAddy(hProcess, localPlayerPtr, { 0x38 });
		playerPosZ = FindDMAAddy(hProcess, localPlayerPtr, { 0x3C });
		localPlayerPitch = FindDMAAddy(hProcess, localPlayerPtr, { 0x44 });
		localPlayerYaw = FindDMAAddy(hProcess, localPlayerPtr, { 0x40 });
		localPlayerRoll = FindDMAAddy(hProcess, localPlayerPtr, { 0x48 });
		//
		entPosX = FindDMAAddy(hProcess, localEntityPtr, { 0x4, 0x4 });
		entPosY = FindDMAAddy(hProcess, localEntityPtr, { 0x4, 0x8 });
		entPosZ = FindDMAAddy(hProcess, localEntityPtr, { 0x4, 0xC });
		entTeam = FindDMAAddy(hProcess, localPlayerPtr, { 0x4, 0x32C });
		//
		totalPlayers = moduleBase + 0x10F500;
		//
		ui::menu();
	}
	else
	{
		std::cout << "Process not found.\n";
		return 0;
	}
	DWORD dExit = 0;
	while (GetExitCodeProcess(hProcess, &dExit) && dExit == STILL_ACTIVE)
	{
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			bHealth = !bHealth; //
			if (bHealth)
			{
				std::cout << "[AlERT] - Health ENABLED\n";
			}
			else
			{
				std::cout << "[AlERT] - Health DISABLED\n";
			}
		}
		if (GetAsyncKeyState(VK_F7) & 1)
		{
			float playerX = 0, playerY = 0, playerZ = 0, playerYaw = 0, playerRoll = 0, playerPitch = 0;
			float entX = 0, entY = 0, entZ = 0, entYaw = 0, entRoll = 0, entPitch = 0;
			int currentPlayerTeam = 0, currentEntTeam = 0;
			bKillaura = !bKillaura;
			if (bKillaura)
			{
				std::cout << "[AlERT] - Killaura ENABLED\n";
				// Team Size
				ReadProcessMemory(hProcess, (BYTE*)totalPlayers, &totalPlayerCount, sizeof(totalPlayerCount), nullptr);
				totalPlayerCount = totalPlayerCount / 2;
				//Ent Pos / View angles
				ReadProcessMemory(hProcess, (BYTE*)entPosX, &entX, sizeof(entX), nullptr);// x
				ReadProcessMemory(hProcess, (BYTE*)entPosY, &entY, sizeof(entY), nullptr);// y
				ReadProcessMemory(hProcess, (BYTE*)entPosZ, &entZ, sizeof(entZ), nullptr);// z
				// Player Pos / View angles
				ReadProcessMemory(hProcess, (BYTE*)playerPosX, &playerX, sizeof(playerX), nullptr);// x
				ReadProcessMemory(hProcess, (BYTE*)playerPosY, &playerY, sizeof(playerY), nullptr);// y
				ReadProcessMemory(hProcess, (BYTE*)playerPosZ, &playerZ, sizeof(playerZ), nullptr);// z
				ReadProcessMemory(hProcess, (BYTE*)localPlayerPitch, &playerPitch, sizeof(playerPitch), nullptr);// Pitch
				ReadProcessMemory(hProcess, (BYTE*)localPlayerRoll, &playerRoll, sizeof(playerRoll), nullptr);// Roll
				ReadProcessMemory(hProcess, (BYTE*)localPlayerYaw, &playerYaw, sizeof(playerYaw), nullptr);// Yaw
				// Player / Ent Current Team 
				ReadProcessMemory(hProcess, (byte*)playerTeam, &currentPlayerTeam, sizeof(currentPlayerTeam), nullptr);
				ReadProcessMemory(hProcess, (byte*)playerTeam, &currentEntTeam, sizeof(currentEntTeam), nullptr);
				if (currentEntTeam != currentPlayerTeam)
				{
					std::cout << "Your on the Same team";
				}
				else
				{
					WriteProcessMemory(hProcess, (BYTE*)playerPosX, &entX, sizeof(entX), nullptr);
					WriteProcessMemory(hProcess, (BYTE*)playerPosY, &entY, sizeof(entY), nullptr);
					WriteProcessMemory(hProcess, (BYTE*)playerPosZ, &entZ, sizeof(entZ), nullptr);

					for (int i = 0; i < (numOfPlayers); i++)
					{
						std::cout << "Big Monke Balls\n";
					}
				}
			}
			else
			{
				std::cout << "[AlERT] - Killaura DISABLED\n";
			}
		}
		if (GetAsyncKeyState(VK_F3) & 1)
		{
			bArmor = !bArmor; //
			if (bArmor)
			{
				std::cout << "[AlERT] - Armor ENABLED\n";
			}
			else
			{
				std::cout << "[AlERT] - Armor DISABLED\n";
			}
		}
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			bAmmo = !bAmmo; //
			if (bAmmo)
			{
				std::cout << "[AlERT] - Ammo ENABLED\n";
			}
			else
			{
				std::cout << "[AlERT] - Ammo DISABLED\n";
			}
		}
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			bHealth = !bHealth; //
			if (bHealth)
			{
				std::cout << "[AlERT] - Health ENABLED\n";
			}
			else
			{
				std::cout << "[AlERT] - Health DISABLED\n";
			}
		}
		if (GetAsyncKeyState(VK_F4) & 1)
		{
			bGranade = !bGranade; //
			if (bGranade)
			{
				std::cout << "[AlERT] - Granade ENABLED\n";
			}
			else
			{
				std::cout << "[AlERT] - Granade DISABLED\n";
			}
		}
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			bGravity = !bGravity; //
			if (bGravity)
			{
				std::cout << "[AlERT] - Gravity ENABLED\n";
			}
			else
			{
				std::cout << "[AlERT] - Gravity DISABLED\n";
			}
			if (!bGravity)
			{
				mem::PatchEx((BYTE*)playerGravity, (BYTE*)&oldGravity, sizeof(oldGravity), hProcess);
			}
		}
		if (GetAsyncKeyState(VK_F5) & 1)
		{
			bSpeed = !bSpeed; //
			if (bSpeed)
			{
				mem::PatchEx((BYTE*)playerSpeed, (BYTE*)&speed, sizeof(speed), hProcess);
				std::cout << "[AlERT] - Speed ENABLED\n";
			}
			else
			{
				std::cout << "[AlERT] - Speed DISABLED\n";
			}
		}
		if (GetKeyState(VK_F8) & 1)
		{
			bPlayerHeight = !bPlayerHeight;
			if (bPlayerHeight)
			{
				std::cout << "[AlERT] - Player Height ENABLED\n";

			}
			else
			{
				std::cout << "[AlERT] - Player Height DISABLED\n";
			}
		}
		if (GetKeyState(VK_F9) & 1)
		{
			return 0;
		}
		//
		if (bGravity)
		{
			mem::PatchEx((BYTE*)playerGravity, (BYTE*)&newGravity, sizeof(newGravity), hProcess);
		}
		if (bHealth)
		{
			mem::PatchEx((BYTE*)playerHealth, (BYTE*)&health, sizeof(health), hProcess);
		}
		if (bAmmo)
		{
			mem::PatchEx((BYTE*)playerAmmo, (BYTE*)&ammo, sizeof(ammo), hProcess);
		}
		if (bArmor)
		{
			mem::PatchEx((BYTE*)playerArmor, (BYTE*)&armor, sizeof(armor), hProcess);
		}
		if (bGranade)
		{
			mem::PatchEx((BYTE*)playerGranade, (BYTE*)&grenade, sizeof(grenade), hProcess);
		}
		Sleep(10);
	}
	std::cout << "Process not found.\n";
	return 0;
}
