#include "SettingReader.h"
#include <iostream>

json SettingReader::read(std::string file)
{
	try {
		std::fstream f(file, std::fstream::in);
		json j = json::parse(f, NULL, NULL, true);
		return j;
	}
	catch (json::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	return json();
}
int SettingReader::write(json j, std::string file)
{
	try {
		std::fstream f(file, std::fstream::out);
		//json j = json::parse(f, NULL, NULL, true);
		f << j.dump(4, ' ');
		return 1;
	}
	catch (json::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}