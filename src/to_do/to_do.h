/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: Header file                   *
 * File: to_do.h                            *
 ********************************************/

#pragma once

#include <iostream>

std::string listPath(std::string file_prefix);
std::string allListsPath(std::string username);
std::vector<std::string> parseList(std::string file_prefix);
std::vector<std::string> parseAllLists(std::string file_prefix);
std::string numberify(std::vector<std::string> arr);

bool newList(std::string username, std::string list_name, std::string file_prefix);
void deleteList(std::string username, std::string list_name, std::string file_prefix);
void newTask(std::string task_name, std::string file_prefix);
bool deleteTask(int priority, std::string file_prefix);
bool swapPriorities(int priority1, int priority2, std::string file_prefix);
bool bumpPriority(int task_priority, int new_priority, std::string file_prefix);
std::string allLists(std::string username);