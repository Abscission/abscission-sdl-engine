#include "con_vars.h"

void ConVars::set(std::string key, std::string val) {
	convar_map[key] = val;
}

bool ConVars::b_get(std::string key) {
	return convar_map[key] != "";
}

std::string ConVars::get(std::string key) {
	return convar_map[key];
}

ConVars g_cvars;