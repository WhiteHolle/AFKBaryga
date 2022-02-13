#pragma once

struct data {
	std::vector<int> delays;
	int beer_health = 70;
	int no_afk_delay = 10;
	bool plugin_status = false;
	bool is_afk = false;
	bool save_mode = false;
	bool auto_hill = false;
} pdata;