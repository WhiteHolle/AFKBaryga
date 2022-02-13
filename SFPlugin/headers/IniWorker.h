#pragma once
LPCSTR filename = "SAMPFUNCS\\afkbaryga.ini";

template<typename T>
std::string line_to_int(T begin, T end)
{
	std::stringstream ss;
	bool first = true;
	for (; begin != end; begin++)
	{
		if (!first)
			ss << " ";
		ss << *begin;
		first = false;
	}
	return ss.str();
}

std::string int_to_char(int number)
{

	std::stringstream ss;
	ss << " ";
	ss << number;
	return ss.str();
}

bool FileIsExist(LPCSTR filename)
{
	bool isExist = false;
	std::ifstream iff(filename);

	if (iff.is_open())
		isExist = true;

	iff.close();
	return isExist;
}

void InitIni() {
	if (!FileIsExist(filename))
	{
		SF->getSAMP()->getChat()->AddChatMessage(D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF), "Файл конфигураций не найден. Применяем стандартные настройки");
		WritePrivateProfileStringA("settings", "delays", "", filename);
	}
	else {
		char buf[256];
		GetPrivateProfileStringA("settings", "delays", NULL, buf, sizeof(buf), filename);
		char* tok = strtok(buf, " ");
		while (tok) {
			pdata.delays.push_back(atoi(tok));
			tok = strtok(NULL, " ");
		}
		GetPrivateProfileStringA("settings", "no_afk_delay", "10", buf, sizeof(buf), filename);
		pdata.no_afk_delay = atoi(buf);
		GetPrivateProfileStringA("settings", "beer_health", "70", buf, sizeof(buf), filename);
		pdata.beer_health = atoi(buf);
	}
}

void SaveData(LPCSTR AppName, LPCSTR key, LPCSTR data) {
	WritePrivateProfileStringA(AppName, key, data, filename);
}