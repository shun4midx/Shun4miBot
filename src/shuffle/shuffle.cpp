/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: shuffle.cpp                        *
 ********************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include "shuffle.h"
#include "../parsing/parsing.h"

std::vector<std::string> shuffleList(std::string& list, std::string separator) {
    std::vector<std::string> parsed_arr = parse(list, separator);
    std::vector<std::string> ans;
    
    while (parsed_arr.size() > 0) {
        int random = std::rand();
        int idx = (random % parsed_arr.size() + parsed_arr.size()) % parsed_arr.size();
        ans.push_back(parsed_arr[idx]);
        parsed_arr.erase(parsed_arr.begin() + idx);
    }
    
    return ans;
}