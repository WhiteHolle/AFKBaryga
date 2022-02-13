#pragma once

void CALLBACK open_menu(std::string param) {
	cMenu.main_window_active = !cMenu.main_window_active;
	cMenu.is_cursore = !cMenu.is_cursore;
}