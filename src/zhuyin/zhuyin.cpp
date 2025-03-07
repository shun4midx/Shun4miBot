/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: zhuyin.cpp                         *
 ********************************************/

#include <iostream>
#include <string.h>
#include <unordered_map>
#include <algorithm>
#include "zhuyin.h"
#include "../file_manager/file_manager.h"
#include "../dictionary/dictionary.h"
#include "../parsing/parsing.h"
#include "../zhuyinify/zhuyinify.h"

// ======== MAIN FUNCTIONS ======= //
// Disclaimer: This is so far just a joke thing, please don't take it seriously
std::vector<std::string> zhuyinify(std::string str, std::string file_prefix) {
    std::unordered_map<std::string, std::vector<std::string>> ZHUYIN_JOKE_DICT = parseDict("zhuyin/zhuyin_joke_dict.txt");
    std::unordered_map<std::string, std::vector<std::string>> ZHUYIN_DICT = parseDict("zhuyin/zhuyin_dict.txt");

    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    if (ZHUYIN_JOKE_DICT.find(str) != ZHUYIN_JOKE_DICT.end()) {
        return ZHUYIN_JOKE_DICT[str];
    } else {
        /*
        std::vector<std::string> parsed_txt = parseDictWords(str, ZHUYIN_DICT).first;
        std::vector<std::string> output;
        std::string temp = "";

        for (int i = 0; i < parsed_txt.size(); i++) {
            temp += parsed_txt[i];

            if (i != parsed_txt.size() - 1) {
                temp += "  ";
            }
        }

        output.push_back(temp);

        return output;
        */
       
        // Zhuyinify.h
        std::vector<std::string> output;
        output.push_back(pinyin(str, file_prefix));
        return output;
    }
}

std::string zhuyinifyString(std::string str, std::string file_prefix) {
    return zhuyinify(str, file_prefix)[0];
}

std::string zhuyinDict() {
    return read("zhuyin/zhuyin_custom_dict_list.txt");
}

std::string zhuyinType(std::string input, std::string file_prefix) {
    // Symbol-fy (includes emojis and symbols)
    std::unordered_map<std::string, std::vector<std::string>> SYMBOL_DICT = parseDict("zhuyin/zhuyin_type_symbol_dict.txt");
    SYMBOL_DICT = reverseDict(SYMBOL_DICT);

    std::pair<std::vector<std::string>, std::vector<bool>> symbol_copy =  parseDictWords(input, SYMBOL_DICT);

    // Zhuyin
    std::unordered_map<std::string, std::vector<std::string>> ZHUYIN_TYPE_DICT = parseDict("zhuyin/zhuyin_type_dict.txt");
    ZHUYIN_TYPE_DICT = reverseDict(ZHUYIN_TYPE_DICT);

    std::pair<std::vector<std::string>, std::vector<bool>> parse_copy = symbol_copy;

    int idx = 0;
    for (int i = 0; i < symbol_copy.first.size(); i++) {
        if (!symbol_copy.second[i]) { // Not already parsed
            std::vector<std::string> parse_zhuyin = qwertyToZhuyinVector(symbol_copy.first[i], file_prefix);
            std::string zhuyin_input = "";
            for (int i = 0; i < parse_zhuyin.size(); i++) {
                zhuyin_input += parse_zhuyin[i] + "S"; // "S" will be our separator between words
            }

            std::pair<std::vector<std::string>, std::vector<bool>> parse_dict = parseDictWords(zhuyin_input, ZHUYIN_TYPE_DICT);
            parse_copy.first[idx] = parse_dict.first[0];
            parse_copy.second[idx] = parse_dict.second[0];
            idx++;
            for (int j = 1; j < parse_dict.first.size(); j++) {
                parse_copy.first.insert(idx + parse_copy.first.begin(), parse_dict.first[j]);
                parse_copy.second.insert(idx + parse_copy.second.begin(),  parse_dict.second[j]);
                idx++;
            }
        } else { // Already parsed
            parse_copy.second.insert(idx + parse_copy.second.begin(), true);
            idx++;
        }
    }

    // Final stringing together
    std::string temp = "";

    for (int i = 0; i < parse_copy.first.size(); i++) {
        if (parse_copy.second[i]) { // Changed already
            temp += parse_copy.first[i];
        } else { // Zhuyin Type
            temp += zhuyinTypeDefault(parse_copy.first[i], file_prefix);
        }
    }

    return temp;
}

std::string zhuyinTypePrecise(std::string input, std::string file_prefix) {
    // First convert and parse the Zhuyin
    std::string text_file = "zhuyin/generated_files/" + file_prefix + "zhuyin_precise.txt";
    std::string text_path = filePath(text_file);

    int ret_val = std::system(("tobopomo -b '" + input + "'" + " > " + text_path).c_str()); // Call to convert from input to command
    if (ret_val != 0) { // Error returning
        return "Invalid Input";
    }
    
    std::ifstream in(text_path);
    if (!in) { // Error returning
        return "Invalid Input";
    }

    std::vector<std::string> zhuyin_arr = parseTobopomo(read(text_file));
    write(text_file, "");

    // Secondly get the precise output
    std::string output = "";
    for (int i = 0; i < zhuyin_arr.size(); i++) {
        int ret_val = std::system(("tobopomo -k '" + zhuyin_arr[i] + "' -l 6 > " + text_path).c_str());
        if (ret_val != 0) { // Error returning
            return "Invalid Input";
        }

        std::ifstream in(text_path);
        if (!in) { // Error returning
            return "Invalid Input";
        }

        output += readSingleLine(text_file);

        if (i != zhuyin_arr.size() - 1) {
            output += "\n";
        }
    }

    deleteFile(text_file); // Delete file

    return output;
}

std::string zhuyinTypeDefault(std::string input, std::string file_prefix) {
    // First parse the Zhuyin
    std::string text_file = "zhuyin/generated_files/" + file_prefix + "zhuyin_precise.txt";
    std::string text_path = filePath(text_file);
    std::vector<std::string> zhuyin_arr = parse(input, "S");
    
    int idx = 0;
    while (idx < zhuyin_arr.size()) {
        if (zhuyin_arr[idx] == "S") {
            zhuyin_arr.erase(idx + zhuyin_arr.begin());
        } else {
            idx++;
        }
    }

    // Secondly get the default output
    std::string output = "";
    for (int i = 0; i < zhuyin_arr.size(); i++) {
        int ret_val = std::system(("tobopomo -k '" + zhuyin_arr[i] + "' -l 6 > " + text_path).c_str());
        if (ret_val != 0) { // Error handling
            return "Invalid Input";
        }

        std::ifstream in(text_path);
        if (!in) {
            return "Invalid Input";
        }

        output += parseTobopomo(readSingleLine(text_file))[0];
    }

    deleteFile(text_file); // Delete file

    return output;
}

std::string qwertyToZhuyin(std::string input, std::string file_prefix) {
    std::string text_file = "zhuyin/generated_files/" + file_prefix + "qwerty_to_zhuyin.txt";
    std::string text_path = filePath(text_file);
    int ret_val = std::system(("tobopomo -b '" + input + "'" + " > " + text_path).c_str()); // Call to convert from input to command
    if (ret_val != 0) {
        return "Invalid Input";
    }
    
    std::ifstream in(text_path);
    if (!in) {
        return "Invalid Input";
    }

    std::string output = printBopomo(parseTobopomo(read(text_file)));
    deleteFile(text_file); // Delete file

    return output;
}

std::vector<std::string> qwertyToZhuyinVector(std::string input, std::string file_prefix) {
    std::string text_file = "zhuyin/generated_files/" + file_prefix + "qwerty_to_zhuyin.txt";
    std::string text_path = filePath(text_file);

    std::vector<std::string> ret_error;
    ret_error.push_back("Invalid Input");

    int ret_val = std::system(("tobopomo -b '" + input + "'" + " > " + text_path).c_str()); // Call to convert from input to command
    if (ret_val != 0) {
        return ret_error;
    }

    std::ifstream in(text_path);
    if (!in) {
        return ret_error;
    }

    std::vector<std::string> output = parseTobopomo(read(text_file));
    deleteFile(text_file); // Delete file

    return output;
}

// ======== USEFUL FUNCTIONS ======= //
std::vector<std::string> parseTobopomo(std::string str) {
    // Test Empty
    if (str == "[]" || str.length() == 0) {
        return {};
    }

    // Nonempty
    // Turns str in the form ['', '', ...] into a vector of those terms
    std::vector<std::string> str_arr;
    std::string temp = "";

    int char_idx = 2;
    while (char_idx < str.length()) {
        if (str[char_idx] != '\'' && str[char_idx] != ',' && str[char_idx] != ' ') {
            temp += str[char_idx];
        } else if (str[char_idx] == '\'') {
            if (temp != "") {
                str_arr.push_back(temp);
                temp = "";
            }
        }
        char_idx++;
    }

    for (int i = 0; i < str_arr.size(); i++) {
        if (str_arr[i] == " " || str_arr[i] == "" || str_arr[i] == "\n") {
            str_arr.erase(i + str_arr.begin());
        }
    }

    return str_arr;
}

std::string printBopomo(std::vector<std::string> arr) {
    std::string output = "";

    for (int i = 0; i < arr.size(); i++) {
        output += arr[i];

        if (i != arr.size() - 1) {
            output += "  ";
        }
    }

    return output;
}

std::string printBopomoNoSpace(std::vector<std::string> arr) {
    std::string output = "";

    for (int i = 0; i < arr.size(); i++) {
        output += arr[i];
    }

    return output;
}