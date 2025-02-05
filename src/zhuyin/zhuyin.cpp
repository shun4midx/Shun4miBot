/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: zhuyin.cpp                         *
 ********************************************/

#include <iostream>
#include <string.h>
#include <unordered_map>
#include "zhuyin.h"
#include "../file_manager/file_manager.h"

// ======== MAIN FUNCTIONS ======= //
// Disclaimer: This is so far just a joke thing, please don't take it seriously
std::vector<std::string> zhuyinify(std::string str) {
    std::unordered_map<std::string, std::vector<std::string>> ZHUYIN_DICT = {
        {"shun", {"ㄒㄧㄤˊ  ㄏㄞˇ（或者日文的話就更像是ㄕㄨ"}},
        {"翔海", {"ㄒㄧㄤˊ  ㄏㄞˇ（或者日文的話就更像是ㄕㄨ"}},
        {"閉嘴", {"ㄅㄧˋ  ㄗㄨㄟˇ"}},
        {"幹你娘", {"ㄍㄢˋ  ㄋㄧ  ㄋㄧㄤˊ"}},
        {"瘋子", {"ㄈㄥ  ㄗˇ（欸 你在說翔海嗎 :joy::joy:"}},
        {"crazy", {"ㄎㄧㄤ"}},
        {"crazy shun", {"ㄎㄧㄤ  ㄎㄧㄤ  ㄟ˙  ㄒㄧㄤˊ  ㄏㄞˇ"}},
        {"crazy duck", {"ㄎㄧㄤ  ㄎㄧㄤ  ㄟ˙  ㄧㄚ  ㄗˇ"}},
        {"啥小", {"ㄕㄚ  ㄒㄧㄠˇ（或是 ㄙㄢ ㄒㄧㄠˇ"}},
        {"沙小", {"ㄕㄚ  ㄒㄧㄠˇ（或是 ㄙㄢ ㄒㄧㄠˇ"}},
        {"三小", {"ㄕㄚ  ㄒㄧㄠˇ（或是 ㄙㄢ ㄒㄧㄠˇ"}},
        {"尛", {"ㄙㄢ ㄒㄧㄠˇ（欸 其實你知道這個字正確的讀音是唸 ㄇㄛˊ 嗎"}},
        {"怪我只敢喜歡資工", {"ㄍㄨㄞˋ  ㄨㄛˇ  ㄓˇ  ㄍㄢˇ  ㄒㄧˇ  ㄏㄨㄢ  ㄗ  ㄍㄨㄥ（這個翔海還他媽把**我**的頭貼 設成他Spotify非中文版的「怪我只敢喜歡資工」播放清單的圖呢 :skull::skull:"}},
        {"演算法", {"ㄧㄢˇ  ㄙㄨㄢˋ  ㄈㄚˇ（聽說翔海不會這個 期末考還因為他眼睛的慢性病情嚴重發作 半瞎+頭暈想嘔吐地去考 :clown::clown:"}},
        {"algo", {"ㄧㄢˇ  ㄙㄨㄢˋ  ㄈㄚˇ（聽說翔海不會這個 期末考還因為他眼睛的慢性病情嚴重發作 半瞎+頭暈想嘔吐地去考 :clown::clown:"}},
        {"algorithm", {"ㄧㄢˇ  ㄙㄨㄢˋ  ㄈㄚˇ（聽說翔海不會這個 期末考還因為他眼睛的慢性病情嚴重發作 半瞎+頭暈想嘔吐地去考 :clown::clown:"}},
        {"眼算法", {"ㄧㄢˇ  ㄙㄨㄢˋ  ㄈㄚˇ（聽說翔海真不會眼算 可能他需要一些 不會突然期末考慢性病情嚴重發作的眼睛呢 :face_with_hand_over_mouth:"}},
        {"algebra", {"ㄉㄞˋ  ㄕㄨˋ（聽說翔海超不會這個 但被這個什麼:kangaroo::kangaroo:中毒了 :clown:"}},
        {"代數", {"ㄉㄞˋ  ㄕㄨˋ（聽說翔海超不會這個 但被這個什麼:kangaroo::kangaroo:中毒了 :clown:"}},
        {"analysis", {"ㄈㄣ  ㄒㄧ（這翔海不會 :clown:"}},
        {"分析", {"ㄈㄣ  ㄒㄧ（這翔海不會 :clown:"}},
        {"save me", {"ㄐㄧㄡˋ  ㄐㄧㄡˋ  ㄨㄛˇ*（不 我講真的 救救我啊 翔海對我很壞 :sob::sob:*", "ㄐㄧㄡˋ  ㄐㄧㄡˋ  ㄨㄛˇ"}},
        {"救救我", {"ㄐㄧㄡˋ  ㄐㄧㄡˋ  ㄨㄛˇ*（不 我講真的 救救我啊 翔海對我很壞 :sob::sob:*", "ㄐㄧㄡˋ  ㄐㄧㄡˋ  ㄨㄛˇ"}},
        {"救命", {"ㄐㄧㄡˋ  ㄇㄧㄥˋ*（不 我講真的 救救我啊 翔海對我很壞 :sob::sob:*", "ㄐㄧㄡˋ  ㄇㄧㄥˋ"}}
    };

    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    if (ZHUYIN_DICT.find(str) != ZHUYIN_DICT.end()) {
        return ZHUYIN_DICT[str];
    } else {
        return {"Sorry, Shun's custom library for Zhuyin doesn't have this word yet. As of right now, this Zhuyin function is still just a joke for these few words only, but Shun will develop a genuine Zhuyin support tool in the future."};
    }
}

std::string zhuyinifyString(std::string str) {
    return zhuyinify(str)[0];
}

std::string zhuyinDict() {
    return read("zhuyin/zhuyin_custom_dict_list.txt");
}

std::string zhuyinType(std::string input, std::string file_prefix) {
    if (input == "vu;6c93") {
        return "翔海";
    } else if (input == "du; ") {
        return "ㄎㄧㄤ";
    } else if (input == "u03nj04z83") {
        return "演算法";
    } else if (input == "ru.4ru.4ji3") {
        return "救救我";
    } else if (input == "ru.4au/4") {
        return "救命";
    } else {
        return "Sorry, Shun hasn't added this word to the dictionary yet";
    }
}

std::string zhuyinTypePrecise(std::string input, std::string file_prefix) {
    // First convert and parse the Zhuyin
    std::string text_file = "zhuyin/generated_files/" + file_prefix + "zhuyin_precise.txt";
    std::string text_path = filePath(text_file);
    std::system(("tobopomo -b '" + input + "'" + " > " + text_path).c_str()); // Call to convert from input to command
    std::ifstream in(text_path);

    std::vector<std::string> zhuyin_arr = parseTobopomo(read(text_file));
    for (std::string str : zhuyin_arr) {
        std::cout << str << std::endl;
    }
    write(text_file, "");

    // Secondly get the precise output
    std::string output = "";
    for (int i = 0; i < zhuyin_arr.size(); i++) {
        std::system(("tobopomo -k '" + zhuyin_arr[i] + "' -l 6 > " + text_path).c_str());
        std::ifstream in(text_path);

        output += readSingleLine(text_file);

        if (i != zhuyin_arr.size() - 1) {
            output += "\n";
        }
    }

    deleteFile(text_file); // Delete file

    return output;
}

std::string qwertyToZhuyin(std::string input, std::string file_prefix) {
    std::string text_file = "zhuyin/generated_files/" + file_prefix + "qwerty_to_zhuyin.txt";
    std::string text_path = filePath(text_file);
    std::system(("tobopomo -b '" + input + "'" + " > " + text_path).c_str()); // Call to convert from input to command
    std::ifstream in(text_path);

    std::string output = printBopomo(parseTobopomo(read(text_file)));
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