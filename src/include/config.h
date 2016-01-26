#pragma once

#include <string>
#include <map>

class Config {
private:
	std::string Filen;
	std::map<std::string, std::string> Configs;
	void Load(std::string Filename);
	void Save(std::string Filename);

public:
	Config(std::string Filename);
	void Reload();
	void Set(std::string Val);

};