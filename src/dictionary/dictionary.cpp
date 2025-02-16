/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: dictionary.cpp                     *
 ********************************************/

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "dictionary.h"
#include "../file_manager/file_manager.h"
#include "../parsing/parsing.h"

std::unordered_map<std::string, std::vector<std::string>> parseDict(std::string file_name, bool in_src) {
    std::vector<std::string> text_arr = readVector(file_name, in_src);

    std::unordered_map<std::string, std::vector<std::string>> dictionary;

    std::string term = ""; // Actual term
    std::string temp = ""; // Temp to store
    bool got_term = false;

    // Iterate for every element in text_arr
    for (int i = 0; i < text_arr.size(); i++) {
        std::string curr_line = text_arr[i];

        std::vector<std::string> term_arr;
        
        // Get vector and term parse
        for (int j = 0; j < curr_line.length(); j++) {
            if (!got_term) { // Still getting term
                if (curr_line[j] != ':') {
                    term += curr_line[j];
                } else {
                    got_term = true;
                    j++; // Skip space too
                }
            } else { // Got term
                if (j == curr_line.length() - 1 || curr_line[j] != ',' || curr_line[j + 1] != ' ') { // Still same term
                    temp += curr_line[j];
                } else {
                    term_arr.push_back(temp); // Push back new term
                    temp = ""; // Reset temp
                    j++; // Skip next space
                }
            }

        }
        
        term_arr.push_back(temp); // Push back last thing

        // Remove "" or " " in vector
        int idx = 0;
        while (idx < term_arr.size()) {
            if (term_arr[idx] == "" || term_arr[idx] == " ") {
                term_arr.erase(idx + term_arr.begin()); // Don't increment idx after because you just shifted by 1 less idx
            } else {
                idx++;
            }
        }

        // Add element
        dictionary[term] = term_arr;

        // Reset
        term = "";
        temp = "";
        got_term = false;
    }

    return dictionary;
}

bool fixCaps(std::string str, std::unordered_map<std::string, std::vector<std::string>> dictionary) {
    if (dictionary.size() == 0) {
        return false;
    } else if (dictionary.find(str) != dictionary.end()) {
        return (dictionary[str][(dictionary[str]).size() - 1] == "fix_caps");
    } else {
        return false;
    }
}

std::vector<std::pair<std::string, std::vector<std::string>>> orderedTerms(std::unordered_map<std::string, std::vector<std::string>> dictionary) {
    // Add all to a vector
    std::vector<std::pair<std::string, std::vector<std::string>>> ordered_terms(dictionary.begin(), dictionary.end());

    // Sort by length of term
    std::sort(ordered_terms.begin(), ordered_terms.end(), [](const auto &term1, const auto &term2) { return term1.first.length() > term2.first.length(); });

    // Return
    return ordered_terms;
}

std::pair<std::vector<std::string>, std::vector<bool>> parseDictWords(std::string str, std::unordered_map<std::string, std::vector<std::string>> dictionary) {
    // Iterate for every term in the dictionary in order
    std::vector<std::pair<std::string, std::vector<std::string>>> ordered_terms = orderedTerms(dictionary);

    std::vector<std::string> parsed_str;
    std::vector<bool> replaced;
    parsed_str.push_back(str);
    replaced.push_back(false);

    for (int i = 0; i < ordered_terms.size(); i++) {
        // Scan and see if it is found in str, if so we iterate until it is str
        std::string curr_term = ordered_terms[i].first;

        int idx = 0;
        while(idx < parsed_str.size()) {
            if (parsed_str[idx].find(curr_term) == std::string::npos || replaced[idx] == true) { // Can't find it or it's already parsed
                idx++; // Skip since there's no point in parsing
            } else {
                if (parsed_str[idx].length() < curr_term.length()) {
                    idx++; // Skip since there is no point in finding
                } else {
                    // Find and splice
                    int find_idx = parsed_str[idx].find(curr_term);
                    std::string substr1 = parsed_str[idx].substr(0, find_idx);
                    std::string substr2 = parsed_str[idx].substr(find_idx, curr_term.length());
                    substr2 = dictionary[curr_term][0]; // Replace with the first one by default
                    std::string substr3 = parsed_str[idx].substr(find_idx + curr_term.length());

                    parsed_str[idx] = substr1;
                    parsed_str.insert(idx + 1 + parsed_str.begin(), substr2);
                    parsed_str.insert(idx + 2 + parsed_str.begin(), substr3);

                    replaced[idx] = false;
                    replaced.insert(idx + 1 + replaced.begin(), true);
                    replaced.insert(idx + 2 + replaced.begin(), false);
                    idx++;
                }
            }
        }

        // Remove empty or space only from vectors
        idx = 0;
        while (idx < parsed_str.size()) {
            if (parsed_str[idx] == "" || parsed_str[idx] == " ") {
                parsed_str.erase(idx + parsed_str.begin());
                replaced.erase(idx + replaced.begin());
            } else {
                idx++;
            }
        }
    }

    // Add to output
    std::pair<std::vector<std::string>, std::vector<bool>> output;
    output.first = parsed_str;
    output.second = replaced;

    // Return
    return output;
}

std::unordered_map<std::string, std::vector<std::string>> reverseDict(std::unordered_map<std::string, std::vector<std::string>> dictionary) {
    // Iterate for every term in the dictionary in order
    std::vector<std::pair<std::string, std::vector<std::string>>> ordered_terms = orderedTerms(dictionary);

    std::unordered_map<std::string, std::vector<std::string>> inverse_dictionary;

    for (int i = 0; i < ordered_terms.size(); i++) {
        for (int j = 0; j < ordered_terms[i].second.size(); j++) {
            if (ordered_terms[i].second[j] != "fix_caps") { // Skip fix_caps
                if (inverse_dictionary.find(ordered_terms[i].first) != inverse_dictionary.end()) { // This term already has an entry
                    inverse_dictionary[ordered_terms[i].second[j]].push_back(ordered_terms[i].first);
                } else { // Create new entry
                    std::vector<std::string> arr;
                    arr.push_back(ordered_terms[i].first);
                    inverse_dictionary[ordered_terms[i].second[j]] = arr;
                }
            }
        }
    }

    return inverse_dictionary;
}