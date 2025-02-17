/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: japanese.cpp                       *
 ********************************************/

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include "../file_manager/file_manager.h"
#include "../dictionary/dictionary.h"

#define MAX_BUFFER 5000000

// ======== DICTIONARY ======== //
// JP to EN punctuation
std::unordered_map<std::string, std::string> PUNCTUATION = {
	{ "。", "." },
	{ "、", "," },
	{ "，", "," },
	{ "：", ":" },
	{ "；", ";" },
	{ "？", "?" },
	{ "！", "!" },
	{ "「", "\"" },
	{ "」", "\"" },
	{ "『", "'" },
	{ "』", "'" },
	{ "｜", "|" },
	{ "（", "(" },
	{ "）", ")" },
	{ "〜", "~" }
};

// ======== FUNCTIONS ======== //

// ======== EXCLUSIVES ======== //
std::string cppCutlet(std::string phrase, std::string file_prefix) {
	// Write file_prefix
	std::string temp_prefix = read("japanese/generated_files/edited_prefixes.txt");
	write("japanese/generated_files/edited_prefixes.txt", temp_prefix + (temp_prefix == "" ? "" : "\n") + file_prefix, true);
	
	// Write cutlet in cpp_to_py.txt
	write("japanese/generated_files/" + file_prefix + "cpp_to_py.txt", phrase, true);

	// Call cutlet
	std::system((read("python_path/japanese.txt") + filePath("japanese/japanese.py", true)).c_str());
	std::string cutlet_phrase = read("japanese/generated_files/" + file_prefix + "py_to_cpp.txt", true);

	// Delete files
	deleteFile("japanese/generated_files/" + file_prefix + "cpp_to_py.txt", true);
	deleteFile("japanese/generated_files/" + file_prefix + "py_to_cpp.txt", true);

	// Convert answer with the accented letters to regular letters
	std::unordered_map<std::string, std::vector<std::string>> ROMAJI_DICT = parseDict("japanese/romaji_dict.txt");
	std::vector<std::string> output_arr = parseDictWords(cutlet_phrase, ROMAJI_DICT).first;
	std::string output = "";
	for (std::string phrase : output_arr) {
		output += phrase;
	}

	// Return answer
	// return cutlet_phrase;
	return output;
}

std::string toRomaji(std::string phrase, std::string file_prefix) {
    std::unordered_map<std::string, std::vector<std::string>> JAPANESE_DICT = parseDict("japanese/jp_custom_dict.txt");

    if (JAPANESE_DICT.find(phrase) != JAPANESE_DICT.end()) {
        return JAPANESE_DICT[phrase][0];
    } else {
		std::pair<std::vector<std::string>, std::vector<bool>> parse_dict_words = parseDictWords(phrase, JAPANESE_DICT);
        std::vector<std::string> parsed_txt = parse_dict_words.first;
        std::string temp = "";

        for (int i = 0; i < parsed_txt.size(); i++) {
            if (parse_dict_words.second[i]) { // Changed already
                parsed_txt[i].erase(std::remove(parsed_txt[i].begin(), parsed_txt[i].end(), '|'), parsed_txt[i].end());
				temp += parsed_txt[i];
            } else { // Cutlet it
                temp += cppCutlet(parsed_txt[i], file_prefix);
            }

            if (i != parsed_txt.size() - 1) {
                temp += " ";
            }
        }

        return temp;
    }
}

std::string formatCutlet(std::string phrase) {
	return "";
}

std::string shortcutToJp(std::string shortcut) {
	return "";
}

// ======== GENERAL PUBLIC ======== //
std::string jpToRomaji(std::string phrase) {
	return "";
}