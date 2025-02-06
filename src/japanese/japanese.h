/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: Header file                   *
 * File: japanese.h                         *
 ********************************************/

#pragma once
#include <iostream>

// JP to Romaji
std::string cppCutlet(std::string phrase, std::string file_prefix); // Calls the cutlet function in Python with the user prefix
std::string formatCutlet(std::string phrase); // Formats cutlet output correctly according to pronunciation
std::string toRomaji(std::string phrase, std::string file_prefix); // Converts input to romaji, not taking punctuation into consideration yet
std::string jpToRomaji(std::string phrase); // Converts an entire phrase into romaji (whilst keeping the custom_dict.txt in mind)

// My Shortcuts
std::string shortcutToJp(std::string shortcut); // Given a shortcut, determine the JP it corresponds to

// Parsing and auto conversion