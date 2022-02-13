#include "main.h"

void __stdcall mainloop()
{
	static bool initialized = false;
	if (!initialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			InitIni();
			InitCallbacks();
			cMenu.CMenu();
			initialized = true;
			SF->getSAMP()->registerChatCommand("afk_b", open_menu);
		}
	}
	else {
		save_mode();
		auto_hill();
		AFK_Emulation();
		cMenu.cursor_fix();
	}
		
}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
		SF->initPlugin(mainloop, hModule);
	return TRUE;
}
