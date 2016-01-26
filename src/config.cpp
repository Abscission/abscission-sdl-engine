#include "config.h"
#include "console.h"
#include "types.h"
#include <fstream>

void Config::Load(std::string Filename) {
	std::fstream FileStream;
	FileStream.open(Filename, std::fstream::in);

	std::string Line;
	int LineNumb = 0;

	while (std::getline(FileStream, Line)) {
		LineNumb++;
		console.run_command(Line);
	}
	FileStream.close();
}

void Config::Save(std::string Filename) {
	std::ofstream FileStream;
	FileStream.open(Filename, std::fstream::in | std::fstream::out | std::fstream::trunc);

	FileStream.flush();
	FileStream.close();
}

Config::Config(std::string Filename) {
	this->Filen = Filename;
	Load(Filename);
}

void Config::Reload() {
	Load(Filen);
}

void Config::Set(std::string Val) {
	std::ofstream Stream(Filen, std::ios::app);
	Stream << "\n" << Val; 
}