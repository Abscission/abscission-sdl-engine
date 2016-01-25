#pragma once

#include <string>
#include <map>

class ConVars {
private:
	std::map<std::string, std::string> convar_map;
public:
	void set(std::string key, std::string val);

	bool b_get(std::string key);
	std::string get(std::string key);
};

extern ConVars g_cvars;