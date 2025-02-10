/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: format.cpp                         *
 ********************************************/

#include <iostream>
#include "../dictionary/dictionary.h"

std::string formatInput(std::string input) {
    std::unordered_map<std::string, std::vector<std::string>> FORMAT_DICT = parseDict("format/format_dict.txt", true);
    FORMAT_DICT = reverseDict(FORMAT_DICT);

    // CHeck easier parse first
    std::pair<std::vector<std::string>, std::vector<bool>> parse_dict_words = parseDictWords(input, FORMAT_DICT);
    std::vector<std::string> parsed_txt = parse_dict_words.first;
    std::string output = "";

    for (int i = 0; i < parsed_txt.size(); i++) {
        output += parsed_txt[i];
    }

    // Check the like ^{} stuff iin brackets

    return output;
}