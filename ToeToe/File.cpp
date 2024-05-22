#include "File.h"
#include<fstream>
#include<cstdio>

void File::writeFile(const std::string& fileName, const std::string& str)
{
	std::fstream file(fileName, std::ios::in | std::ios::out);

	// check file exist
	if (!file.is_open())
	{
		file.open(fileName, std::ios::out);
	}
	else
	{
		file.close();
		file.open(fileName, std::ios::out | std::ios::app);
	}
	file << str << std::endl;
	file.close();
}

void File::deleteFile(const std::string& fileName)
{
	std::remove(fileName.c_str());
}

void File::readFile(const std::string& fileName, std::vector<std::string>& stringArr)
{
	stringArr.clear();

	// check file exist
	std::fstream file(fileName, std::ios::in | std::ios::out);
	if (!file.is_open())
	{
	}
	else
	{
		file.close();
		file.open(fileName, std::ios::in);
		std::string line;
		while (!file.eof())
		{
			std::getline(file, line);
			stringArr.push_back(line);
		}
	}	
	file.close();
}
