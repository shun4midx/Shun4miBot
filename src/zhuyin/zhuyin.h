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
std::string zhuyinType(std::string input, std::string file_prefix); // Converts QWERTY input into Traditional Chinese characters
std::string zhuyinTypePrecise(std::string input, std::string file_prefix); // Outputs max top 10 likely characters for each bopomo syllable typed
std::string zhuyinTypeDefault(std::string input, std::string file_prefix); // Strings up the default characters for Zhuyin
std::string qwertyToZhuyin(std::string input, std::string file_prefix); // Converts QWERTY input into Zhuyin
std::string qwertyToZhuyinNoSpace(std::string input, std::string file_prefix); // Converts QWERTY input into Zhuyin with no space

std::vector<std::string> parseTobopomo(std::string str); // Converts tobopomo.js outputs into something usable as a vector
std::string printBopomo(std::vector<std::string> zhuyin_arr); // Returns a given parsed zhuyin vector as a string
std::string printBopomoNoSpace(std::vector<std::string> zhuyin_arr); // Returns a given parsed zhuyin vector as a string with no space