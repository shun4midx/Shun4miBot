/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: Header file                   *
 * File: file_manager.h                     *
 ********************************************/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

// Normal Locations
std::string filePath(std::string file_name, bool in_src = false); // Returns file path given file_name and in_src
std::string read(std::string file_name, bool in_src = false); // Reads a txt file and returns it, inSrc is if it is in /src
std::vector<std::string> readVector(std::string file_name, bool in_src = false); // Reads a txt file and returns it as a vector
bool checkInstance(std::string file_name, std::string instance, bool in_src = false); // Checks for if there's a line containing instance