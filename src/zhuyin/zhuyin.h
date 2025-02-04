/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: Header file                   *
 * File: zhuyin.h                           *
 ********************************************/

#pragma once

#include <iostream>

std::vector<std::string> zhuyinify(std::string str); // Converts str into Zhuyin and if there is any edits required, it's appended to the back of the vector
std::string zhuyinifyString(std::string str); // Returns what the str is converted into Zhuyin
std::string zhuyinDict(); // Returns the entire txt file of the current custom Zhuyin dictionary available entries
std::string zhuyinType(std::string input); // Converts QWERTY input into Traditional Chinese characters
std::string qwertyToZhuyin(std::string input); // Converts QWERTY input into Zhuyin