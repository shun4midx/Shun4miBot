/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: to_do.cpp                          *
 ********************************************/

#include <iostream>
#include <vector>
#include "to_do.h"
#include "../file_manager/file_manager.h"
#include "../parsing/parsing.h"

std::string listPath(std::string file_prefix) {
    return "to_do/generated_files/" + file_prefix + "list.txt";
}

std::string allListsPath(std::string username) {
    return "to_do/generated_files/" + username + "_all_lists.txt";
}

std::vector<std::string> parseList(std::string file_prefix) {
    return readVector(listPath(file_prefix));
}

std::vector<std::string> parseAllLists(std::string username) {
    return readVector(allListsPath(username));
}

std::string numberify(std::vector<std::string> arr) {
    std::string output = "";

    for (int i = 0; i < arr.size(); i++) {
        if (i < 9 && arr.size() >= 10) {
            output += std::to_string(i + 1) + ".  ";
        } else {
            output += std::to_string(i + 1) + ". ";
        }

        output += arr[i];

        if (i != arr.size() - 1) {
            output += "\n";
        }
    }

    return output;
}

bool newList(std::string username, std::string list_name, std::string file_prefix) {
    if (checkFile(listPath(file_prefix))) {
        return false;
    } else {
        write(listPath(file_prefix), "");
        if (checkFile(allListsPath(username))) {
            write(allListsPath(username), read(allListsPath(username)) + "\n" + list_name);
        } else {
            write(allListsPath(username), list_name);
        }
        return true;
    }
}

void deleteList(std::string username, std::string list_name, std::string file_prefix) {
    // Delete file
    deleteFile(listPath(file_prefix));
    
    // Delete file from lists' memory
    std::vector<std::string> all_lists = parseAllLists(username);
    for (int i = 0; i < all_lists.size(); i++) {
        if (all_lists[i] == list_name) {
            all_lists.erase(i + all_lists.begin());
            break;
        }
    }
    write(allListsPath(username), vectorString(all_lists));
}

void renameList(std::string username, std::string original_name, std::string new_name, std::string file_prefix) {
    std::string new_file_prefix = username + "_" + new_name + "_";
    // Rename from lists' memory
    std::vector<std::string> all_lists = parseAllLists(username);
    for (int i = 0; i < all_lists.size(); i++) {
        if (all_lists[i] == original_name) {
            all_lists[i] = new_name;
            break;
        }
    }
    write(allListsPath(username), vectorString(all_lists));

    // Rename the actual file
    write(listPath(new_file_prefix), read(listPath(file_prefix)));
    deleteFile(listPath(file_prefix));
}

void newTask(std::string task_name, std::string file_prefix) {
    std::vector<std::string> tasks = readVector(listPath(file_prefix));
    tasks.push_back(task_name);
    write(listPath(file_prefix), vectorString(tasks));
}

bool deleteTask(int priority, std::string file_prefix) {
    std::vector<std::string> tasks = readVector(listPath(file_prefix));

    // Check tasks to see if there is said task
    if (tasks.size() < priority || priority < 1) {
        return false;
    }

    // Delete list from lists' memory
    tasks.erase(priority - 1 + tasks.begin());

    write(listPath(file_prefix), vectorString(tasks));
    return true;
}

// 0 = No priority, 1 = No name change, 2 = OK
int renameTask(int priority, std::string new_name, std::string file_prefix) {
    std::vector<std::string> tasks = readVector(listPath(file_prefix));

    // Check priority validity
    if (tasks.size() < priority || priority < 1) {
        return 0;
    } else if (tasks[priority - 1] == new_name) {
        return 1;
    } else {
        tasks[priority - 1] = new_name;
        write(listPath(file_prefix), vectorString(tasks)); // Rewrite content
        return 2;
    }
}

bool swapPriorities(int priority1, int priority2, std::string file_prefix) {
    std::vector<std::string> tasks = readVector(listPath(file_prefix));

    // Check priority validity
    if (tasks.size() < std::max(priority1, priority2) || std::min(priority1, priority2) < 1) {
        return false;
    }

    // Swap proirities
    std::string task1 = tasks[priority1 - 1];
    std::string task2 = tasks[priority2 - 1];
    tasks[priority1 - 1] = task2;
    tasks[priority2 - 1] = task1;

    write(listPath(file_prefix), vectorString(tasks));
    return true;
}

bool bumpPriority(int task_priority, int new_priority, std::string file_prefix) {
    std::vector<std::string> tasks = readVector(listPath(file_prefix));

    // Check priority validity
    if (tasks.size() < std::max(task_priority, new_priority) || std::min(task_priority, new_priority) < 1) {
        return false;
    }

    // Bump priority
    std::string task = tasks[task_priority - 1];
    tasks.erase(task_priority - 1 + tasks.begin());
    tasks.insert(new_priority - 1 + tasks.begin(), task);

    write(listPath(file_prefix), vectorString(tasks));
    return true;
}

std::string allLists(std::string username) {
    if (checkFile(allListsPath(username))) {
        return (read(allListsPath(username)) == "" ? "None" : "```\n" + read(allListsPath(username)) + "```\n");
    } else {
        return "None";
    }
}