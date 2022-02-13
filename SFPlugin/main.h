#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <random>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

#include "SAMPFUNCS_API.h"
#include "game_api.h"

#pragma comment (lib, "d3dx9.lib")

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include "headers/plugin_data.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
SAMPFUNCS* SF = new SAMPFUNCS();

#include "headers/IniWorker.h"
#include "headers/textures.h"
#include "headers/work_funcs.h"
#include "headers/Menu.h"

#include "headers/Callbacks.h"
#include "headers/commands_func.h"

