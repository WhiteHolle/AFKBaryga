#pragma once

class Menu {
public:
	bool is_cursore = false;
	bool main_window_active = false;
	bool delays_window_active = false;
	IDirect3DTexture9* menu_image;

	void main_menu() {

		if (this->main_window_active)
		{
			ImGui::SetNextWindowSize({ 300, 160 });
			ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f }, ImGuiCond_Once, { 0.5f, 0.5f });
			ImGui::Begin(u8"##AFKMENU", &this->main_window_active, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
			{
				if (this->menu_image == nullptr)
					D3DXCreateTextureFromFileInMemoryEx(SF->getRender()->getD3DDevice(), &byteLogo, sizeof(byteLogo), 150, 53, D3DX_DEFAULT, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &this->menu_image);
				ImGui::SetCursorPosX(150 - 150 / 2);
				ImGui::Image(this->menu_image, ImVec2(150, 53));
				ImGui::BeginChild("##Settings", { 284, 160 - 53 - 8 * 3 }, true);
				{
					if (ImGui::Checkbox(u8"Эмуляция бездействия", &pdata.plugin_status)) {
						if (pdata.plugin_status == false) {
							pdata.is_afk = false;
							delay = -1;
						}
					}
					ImGui::SameLine(202);
					if (ImGui::Button(u8"Настройки##Range", { 75, 0 })) {
						this->delays_window_active = !this->delays_window_active;
					}
					ImGui::Checkbox(u8"Защита от подбрасываний", &pdata.save_mode);
					ImGui::Checkbox(u8"Авто регенерация ХП", &pdata.auto_hill);
					ImGui::SameLine();
					ImGui::PushItemWidth(30);
					ImGui::InputInt("##beer_health", &pdata.beer_health, NULL, NULL, ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll);
					ImGui::PopItemWidth();
				}

				ImGui::EndChild();
			}
			ImGui::End();
		}
	}

	void delays_menu() {
		if (this->delays_window_active) {
			ImGui::SetNextWindowSize({ 245, 360 });
			ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f }, ImGuiCond_Once, { 0.5f, 0.5f });
			ImGui::Begin(u8"Настройка промежутков##DELAYSMENU", &this->delays_window_active, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);
			{
				if (ImGui::Button(u8"Добавить промежуток")) {
					pdata.delays.push_back(0);
				}
				ImGui::SameLine();
				if (ImGui::Button(u8"Сохранить")) { 
					SaveData("settings", "delays", line_to_int(pdata.delays.begin(), pdata.delays.end()).c_str());
					SaveData("settings", "no_afk_delay", int_to_char(pdata.no_afk_delay).c_str());
					SaveData("settings", "beer_health", int_to_char(pdata.beer_health).c_str());
				}
				ImGui::PushItemWidth(30);
				ImGui::InputInt("##no_afk_delay", &pdata.no_afk_delay, NULL, NULL, ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll);
				ImGui::PopItemWidth();
				ImGui::SameLine();
				ImGui::Text(u8"Время простоя не в афк");
				ImGui::BeginChild("##DELAYSETTINGS", {229, 325 - 8 * 6}, true); 
				{
					for (size_t i = 0; i < pdata.delays.size(); i++) {
						char buf[256];
						sprintf_s(buf, "##Line %d", i);
						ImGui::PushItemWidth(160);
						ImGui::InputInt(buf, &pdata.delays.at(i), NULL, NULL, ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll);
						ImGui::PopItemWidth();
						ImGui::SameLine();
						sprintf_s(buf, "-##Delete %d", i);
						if (ImGui::Button(buf, {20, 20})) {
							pdata.delays.erase(pdata.delays.begin() + i);
						}
					}
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}
	}

	void cursor_fix() {
		if (this->is_cursore == true) {
			if (!SF->getSAMP()->getMisc()->iCursorMode)
				SF->getSAMP()->getMisc()->ToggleCursor(true);
		}
		if (this->delays_window_active == false && this->main_window_active == false && this->is_cursore == true) {
			if (SF->getSAMP()->getMisc()->iCursorMode)
				SF->getSAMP()->getMisc()->ToggleCursor(false);
			this->is_cursore = false;
		}
		if ((this->delays_window_active || this->main_window_active) && SF->getGame()->isKeyPressed(VK_ESCAPE)) {
			if (SF->getSAMP()->getMisc()->iCursorMode)
				SF->getSAMP()->getMisc()->ToggleCursor(false);
			this->is_cursore = false;
			this->delays_window_active = false;
			this->main_window_active = false;
		}

	}

	void Menu::CMenu() {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdanab.ttf", 13.1f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		ImGui_ImplWin32_Init(GetActiveWindow());
		ImGui_ImplDX9_Init(SF->getRender()->getD3DDevice());

		this->Theme();
	}

	void Theme() {
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		style->Alpha = 1.0f;
		style->WindowPadding = { 8, 8 };
		style->WindowMinSize = { 32, 32 };
		style->WindowRounding = 3.0f;
		style->PopupRounding = 3.0f;
		style->WindowTitleAlign = { 0.5f, 0.5f };

		style->FramePadding = { 4, 3 };
		style->FrameRounding = 3.3f;
		style->ChildRounding = 5.0f;
		style->ItemSpacing = { 8, 4 };
		style->TouchExtraPadding = { 0, 0 };
		style->IndentSpacing = 21.0f;
		style->ColumnsMinSpacing = 0.0f;
		style->ScrollbarSize = 6.0f;
		style->ScrollbarRounding = 0.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.3f;
		style->ButtonTextAlign = { 0.5f, 0.5f };
		style->DisplayWindowPadding = { 22, 22 };
		style->DisplaySafeAreaPadding = { 4, 4 };
		style->AntiAliasedLines = true;
		style->AntiAliasedFill = true;
		style->CurveTessellationTol = 1.f;
		colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.2f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.1f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
		colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
		colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
	}
} cMenu;