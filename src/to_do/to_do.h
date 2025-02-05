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
void renameList(std::string username, std::string original_name, std::string new_name, std::string file_prefix);

void newTask(std::string task_name, std::string file_prefix);
bool deleteTask(int priority, std::string file_prefix);
int renameTask(int priority, std::string new_name, std::string file_prefix); // 0 = No priority, 1 = No name change, 2 = OK
bool swapPriorities(int priority1, int priority2, std::string file_prefix);
bool bumpPriority(int task_priority, int new_priority, std::string file_prefix);

std::string allLists(std::string username);
std::string swapListPriorities(int priority1, int priority2, std::string username);
std::string bumpListPriority(int list_priority, int new_priority, std::string username);