/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: Header file                   *
 * File: zhuyinify.h                        *
 ********************************************/

#pragma once

#include <iostream>

std::string pinyin(std::string text, std::string file_prefix); // Returns the direct output
std::string basePinyinToZhuyin(std::string text, std::string file_prefix); // Returns from text's base pinyin (non dict words) to Zhuyin
std::string zhuyinifyChars(std::string text, std::string file_prefix); // Returns Zhuyin from base words