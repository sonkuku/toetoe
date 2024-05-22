#pragma once
#include<string>
#include<vector>

class File
{
public:
	static void writeFile(const std::string& fileName, const std::string& str); // write strings to file
	static void deleteFile(const std::string& fileName); // delete file
	static void readFile(const std::string& fileName, std::vector<std::string>& stringArr); // read strings from file
};

