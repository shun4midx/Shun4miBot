/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: spinner.cpp                        *
 ********************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include "spinner.h"
#include "../parsing/parsing.h"

std::string spin(std::string& choices, std::string separator) {
    std::vector<std::string> parsed_arr = parse(choices, separator);
    int random = std::rand();
    int idx = (random % parsed_arr.size() + parsed_arr.size()) % parsed_arr.size();
    return parsed_arr[idx];
}