#pragma once
time_t start_seconds = -1, real_time = -1, beer_start = -1;
int delay = -1;
void auto_hill() {
	
	if (pdata.is_afk == false && pdata.auto_hill && delay != -1 && real_time >= 11 + beer_start) {
		if (PEDSELF->GetHealth() <= pdata.beer_health) {
			SF->getSAMP()->getPlayers()->pLocalPlayer->Say("/beer");
			beer_start = time(NULL);
		}
	}
}

void save_mode() {
	if (pdata.save_mode && PEDSELF->GetCurrentWeaponSlot() != 0) {
		PEDSELF->SetCurrentWeaponSlot(eWeaponSlot::WEAPONSLOT_TYPE_UNARMED);
	}
}

void start_emulation() {
	if (pdata.delays.size() == 0)
		return
	srand(time(0));
	start_seconds = time(NULL);
	delay = pdata.delays[rand() % (pdata.delays.size())];
	SF->getSAMP()->getChat()->AddChatMessage(0xFFFFFFFF, "Выбрано рандомное время: %d", delay);
	pdata.is_afk = true;
}

void AFK_Emulation() {
	real_time = time(NULL);
	if (pdata.plugin_status && pdata.is_afk == false && delay == -1)
		start_emulation();
	else if (pdata.plugin_status && pdata.is_afk == false) {
		if (pdata.auto_hill == true) {
			if (PEDSELF->GetHealth() >= pdata.beer_health && real_time >= start_seconds + delay + pdata.no_afk_delay)
				start_emulation();
		}
		if (pdata.auto_hill == false) {
			if (real_time >= start_seconds + delay + pdata.no_afk_delay)
				start_emulation();
		}
	}
	else if (pdata.plugin_status && pdata.is_afk) {

		if (real_time >= start_seconds + delay) {
			pdata.is_afk = false;
			SF->getSAMP()->getChat()->AddChatMessage(0xFFFFFFFF, "Вы вышли из афк");
		}
	}
}