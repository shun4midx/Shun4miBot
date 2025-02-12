/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: Header file                   *
 * File: dictionary.h                       *
 ********************************************/

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, std::vector<std::string>> parseDict(std::string file_name, bool in_src = false); // Parses a vector into a dictionary with the ":"
bool fixCaps(std::vector<std::string> arr, std::string str); // Returns if a certain string corresponds to fixed caps
std::vector<std::pair<std::string, std::vector<std::string>>> orderedTerms(std::unordered_map<std::string, std::vector<std::string>> dictionary); // Returns a vector of pairs terms in the dictionary from longest to shortest in order
std::pair<std::vector<std::string>, std::vector<bool>> parseDictWords(std::string str, std::unordered_map<std::string, std::vector<std::string>> dictionary); // Parses a string to isolate words that are in a certain dictionary and already convert them, boolean vector is if said parsed word of the vector is in the dictionary
std::unordered_map<std::string, std::vector<std::string>> reverseDict(std::unordered_map<std::string, std::vector<std::string>> dictionary); // Reverses a dictionary