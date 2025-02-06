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
#include "../file_manager/file_manager.h"

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
	std::system(("/usr/local/bin/python3 " + filePath("japanese/japanese.py", true)).c_str());
	std::string cutlet_phrase = read("japanese/generated_files/" + file_prefix + "py_to_cpp.txt", true);

	// Delete files
	deleteFile("japanese/generated_files/" + file_prefix + "cpp_to_py.txt", true);
	deleteFile("japanese/generated_files/" + file_prefix + "py_to_cpp.txt", true);

	// Return answer
	return cutlet_phrase;
}

std::string toRomaji(std::string phrase) {
	return "";
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