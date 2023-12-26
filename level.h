#pragma once 
#include <iostream>
#include <string>
#include <fstream>


struct Entity //TODO: Never Used, should delete
{
	float x, y;

	void LoadLevelFromAFile(const std::string& filename);
};