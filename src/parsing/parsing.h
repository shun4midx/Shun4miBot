/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: Header file                   *
 * File: parsing.h                          *
 ********************************************/

#pragma once

#include <vector>
#include <string>

std::vector<std::string> parse(std::string& choices, std::string separator);
std::string vectorString(std::vector<std::string> arr);