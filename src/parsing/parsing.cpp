/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: parsing.cpp                        *
 ********************************************/

#include <iostream>
#include <vector>
#include "parsing.h"

std::vector<std::string> parse(std::string choices, std::string separator) {
    std::vector<std::string> parsed;
    std::string temp = "";

    if (separator.length() != 1) {
        parsed.push_back("Invalid separator. Separators can only be **one character** long.");
    } else {
        for (int i = 0; i < choices.length(); i++) {
            if (choices[i] != separator[0]) {
                temp = temp + choices[i];
            } else {
                parsed.push_back(temp);
                temp = "";
            }
        }
        parsed.push_back(temp); // Push back final element

        // Remove empty elements
        for (int i = 0; i < parsed.size(); i++) {
            if (parsed[i].length() == 0) {
                parsed.erase(parsed.begin() + i);
            }
        }
    }

    return parsed;
}

std::string vectorString(std::vector<std::string> arr) {
    std::string ans = "";
    for (int i = 0; i < arr.size(); i++) {
        ans += (arr[i] + (i != arr.size() - 1 ? "\n" : ""));
    }
    return ans;
}