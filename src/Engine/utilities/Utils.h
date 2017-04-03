#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace engine {

	inline std::string read_file(std::string filename)
	{
		std::ifstream file(filename.c_str());
		std::string result;

		if (file.is_open())
		{
			while (!file.eof())
			{
				std::string line;
				std::getline(file, line);
				result += line + '\n';
			}
			file.close();
		}
		else
			std::cout << "Could not open file: " << filename << std::endl;

		return result;
	}

}