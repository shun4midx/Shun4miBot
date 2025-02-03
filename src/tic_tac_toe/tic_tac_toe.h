/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: Header file                   *
 * File: tic_tac_toe.h                      *
 ********************************************/

#pragma once

std::string ticTacToe(int location, std::string file_prefix); // Returns the grid after choosing a location
std::string coopTicTacToe(int location, std::string file_prefix, std::string curr_user, std::string other_user); // Returns the coop grid after choosing a location
std::vector<std::vector<char>> readGrid(std::string file_prefix); // Returns the grid in a vector
bool quitGame(std::string file_prefix); // Quits a Tic Tac Toe game
bool quitCoopGame(std::string file_prefix); // Quits a Coop Tic Tac Toe game