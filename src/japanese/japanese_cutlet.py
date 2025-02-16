############################################
# Copyright (c) 2025 Shun/翔海 (@shun4midx) #
# Project: Shun4miBot                      #
# File Type: Python file                   #
# File: japanese_cutlet.py                 #
############################################

#!/usr/local/bin python3
# -*- coding: utf-8 -*-
import os
import cutlet
katsu = cutlet.Cutlet()
katsu.use_foreign_spelling = False

def getUser():
    edited_prefixes_file = open(os.path.join(os.path.dirname(__file__), "generated_files/edited_prefixes.txt"), "r")
    usernames = edited_prefixes_file.read()
    usernames_arr = usernames.split("\n")
    return usernames_arr[0]

def completeUser():
    # Remove user from new list
    edited_prefixes_file = open(os.path.join(os.path.dirname(__file__), "generated_files/edited_prefixes.txt"), "r")
    usernames = edited_prefixes_file.read()
    usernames_arr = usernames.split("\n")
    usernames_arr.pop(0)

    # Rewrite file using new list
    edited_prefixes_file = open(os.path.join(os.path.dirname(__file__), "generated_files/edited_prefixes.txt"), "w")
    if len(usernames_arr) == 0:
        edited_prefixes_file.write("")
    else:
        new_usernames = ""
        for idx in range (0, len(usernames_arr)):
            if idx != 0:
                new_usernames += "\n"

            new_usernames += usernames_arr[idx]

        edited_prefixes_file.write(new_usernames)

if __name__ == "__main__": 
    cpp_to_py_file = open(os.path.join(os.path.dirname(__file__), "generated_files/" + getUser() + "cpp_to_py.txt"), "r")
    test = katsu.romaji(cpp_to_py_file.read())

    py_to_cpp_file = open(os.path.join(os.path.dirname(__file__), "generated_files/" + getUser() + "py_to_cpp.txt"), "w")
    py_to_cpp_file.write(test)
    py_to_cpp_file.close()

    cpp_to_py_file.close()

    completeUser() # Remember to remove the username when complete