#pragma once

bool CALLBACK Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{

    if (SUCCEEDED(SF->getRender()->BeginRender()))
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        cMenu.main_menu();
        cMenu.delays_menu();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    {
        SF->getRender()->EndRender();
    }
    return true;
}

HRESULT CALLBACK Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    return true;
}

bool CALLBACK WndProcHandler(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    ImGui_ImplWin32_WndProcHandler(hwd, msg, wParam, lParam);
    return true;
}

void CALLBACK PluginFree()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

bool CALLBACK outcomingData(stRakNetHookParams* params)
{
    if (params->packetId == PacketEnumeration::ID_PLAYER_SYNC && pdata.is_afk) {
        return false;
    };
    return true;
};

void InitCallbacks() {
    SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, Present);
    SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_RESET, Reset);
    SF->getGame()->registerWndProcCallback(SFGame::MEDIUM_CB_PRIORITY, WndProcHandler);
    SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_PACKET, outcomingData);
    SF->getGame()->registerGameDestructorCallback(PluginFree);

}