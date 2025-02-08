/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: zhuyinify.cpp                      *
 ********************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
#include "zhuyinify.h"
#include "../file_manager/file_manager.h"

std::string pinyin(std::string text, std::string file_prefix) {
    // Write file_prefix
    std::string temp_prefix = read("zhuyinify/generated_files/edited_prefixes.txt");
    write("zhuyinify/generated_files/edited_prefixes.txt", temp_prefix + (temp_prefix == "" ? "" : "\n") + file_prefix, true);
    
    // Write info in cpp_to_py.txt
    write("zhuyinify/generated_files/" + file_prefix + "cpp_to_py.txt", text, true);

    // Call translate
    std::system(("/usr/local/bin/python3 " + filePath("zhuyinify/zhuyinify.py", true)).c_str());
    std::string output = read("zhuyinify/generated_files/" + file_prefix + "py_to_cpp.txt", true);

    // Delete files
    deleteFile("zhuyinify/generated_files/" + file_prefix + "cpp_to_py.txt", true);
    deleteFile("zhuyinify/generated_files/" + file_prefix + "py_to_cpp.txt", true);

    // Return answer
    return output;
}