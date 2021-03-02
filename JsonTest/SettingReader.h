#pragma once
#include <nlohmann/json.hpp>
#include <fstream>

using nlohmann::json;

class SettingReader
{
public:
	json read(std::string file);
	int write(json j, std::string file);
};

