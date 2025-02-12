/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: tic_tac_toe.cpp                    *
 ********************************************/

#include <iostream>
#include <string.h>
#include "tic_tac_toe.h"
#include "../file_manager/file_manager.h"

// ======== FILES ======== //
std::string playerFile(std::string file_prefix) {
    return "tic_tac_toe/" + file_prefix + "player.txt";
}

std::string playerOFile(std::string file_prefix) {
    return "tic_tac_toe/" + file_prefix + "player_o.txt";
}

std::string playerXFile(std::string file_prefix) {
    return "tic_tac_toe/" + file_prefix + "player_x.txt";
}

std::string currPlayerFile(char curr_player, std::string file_prefix) {
    if (curr_player == 'X') {
        return playerXFile(file_prefix);
    } else if (curr_player == 'O') {
        return playerOFile(file_prefix);
    } else {
        std::cout << "curr_player: " << curr_player << std::endl;
        return "Invalid";
    }
}

std::string gridFile(std::string file_prefix) {
    return "tic_tac_toe/" + file_prefix + "grid.txt";
}

// ======== GRID ======== //
void writeGrid(std::vector<std::vector<char>> grid_arr, std::string file_prefix) {
    std::string separator = "|";
    std::string grid_txt = grid_arr[0][0] + separator + grid_arr[0][1] + separator + grid_arr[0][2] + "\n" + 
                           "-+-+-\n" +
                           grid_arr[1][0] + separator + grid_arr[1][1] + separator + grid_arr[1][2] + "\n" + 
                           "-+-+-\n" +
                           grid_arr[2][0] + separator + grid_arr[2][1] + separator + grid_arr[2][2];
    write(gridFile(file_prefix), grid_txt);
}

std::vector<std::vector<char>> readGrid(std::string file_prefix) {
    std::string grid_txt = read(gridFile(file_prefix));

    std::vector<std::vector<char>> grid_arr;
    std::vector<char> grid_arr0;
    std::vector<char> grid_arr1;
    std::vector<char> grid_arr2;

    grid_arr0.push_back(grid_txt[0]);
    grid_arr0.push_back(grid_txt[2]);
    grid_arr0.push_back(grid_txt[4]);

    grid_arr1.push_back(grid_txt[12]);
    grid_arr1.push_back(grid_txt[14]);
    grid_arr1.push_back(grid_txt[16]);

    grid_arr2.push_back(grid_txt[24]);
    grid_arr2.push_back(grid_txt[26]);
    grid_arr2.push_back(grid_txt[28]);

    grid_arr.push_back(grid_arr0);
    grid_arr.push_back(grid_arr1);
    grid_arr.push_back(grid_arr2);

    return grid_arr;
}

// ======== CURRENT PLAYER ======== //
char currPlayer(std::string file_prefix) {
    return read(playerFile(file_prefix))[0];
}

void changePlayer(std::string file_prefix) {
    if (currPlayer(file_prefix) == 'X' || currPlayer(file_prefix) == ' ') {
        write(playerFile(file_prefix), "O");
    } else if (currPlayer(file_prefix) == 'O') {
        write(playerFile(file_prefix), "X");
    }
}

// ========= MAIN FUNCTIONS ======== //
std::string ticTacToe(int square, std::string file_prefix) {
    // ======== SET UP ======== //
    if (!checkFile(playerFile(file_prefix))) {
        write(playerFile(file_prefix), "O");
        write(gridFile(file_prefix), " | | \n-+-+-\n | | \n-+-+-\n | | ");
    }

    // ======== VARIABLES ======== //
    bool end_game = false;
    char curr_player = currPlayer(file_prefix);
    std::vector<std::vector<char>> grid_arr = readGrid(file_prefix);

    // std::cout << "grid_arr: " << grid_arr[0][0] << " " << grid_arr[0][1] << " " << grid_arr[0][2] << " " << grid_arr[1][0] << " " << grid_arr[1][1] << " " << grid_arr[1][2] << " " << grid_arr[2][0] << " " << grid_arr[2][1] << " " << grid_arr[2][2] << " " << std::endl;

    // ======== LOG USER INPUT ======= //
    int X = (square - 1) / 3;
    int Y = (square - 1) % 3;
    
    // Check invalid input
    if (grid_arr[X][Y] != ' ') {
        return "Invalid square, this square is already taken, choose another square.";
    } else {
        grid_arr[X][Y] = curr_player;
        writeGrid(grid_arr, file_prefix);
        changePlayer(file_prefix);
    }

    // ======== CHECK WIN ======== //
    // Columns and Rows
    for (int i = 0; i < 3; i++) {
        char begin_row = grid_arr[i][0];
        char begin_col = grid_arr[0][i];
        
        // Check row
        if (begin_row != ' ' && begin_row == grid_arr[i][1] && begin_row == grid_arr[i][2]) {
            end_game = true;
        }

        // Check col
        if (begin_col != ' ' && begin_col == grid_arr[1][i] && begin_col == grid_arr[2][i]) {
            end_game = true;
        }
    }

    // Diagonals
    if (grid_arr[0][0] != ' ' && grid_arr[0][0] == grid_arr[1][1] && grid_arr[1][1] == grid_arr[2][2]) {
        end_game = true;
    }

    if (grid_arr[0][2] != ' ' && grid_arr[0][2] == grid_arr[1][1] && grid_arr[1][1] == grid_arr[2][0]) {
        end_game = true;
    }

    if (end_game) {
        std::string win_statement;
        win_statement += "Player ";
        win_statement += curr_player;
        win_statement += " won!\n\n" + read(gridFile(file_prefix));
        write(gridFile(file_prefix), win_statement);
    }

    // Draw
    bool is_draw = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid_arr[i][j] == ' ') {
                is_draw = false;
            }
        }
    }

    if (is_draw) {
        end_game = true;
        write(gridFile(file_prefix), "It's a draw!\n\n" + read(gridFile(file_prefix)));
    }

    // ======== CONCLUSION ======== //
    // Return answer
    std::string grid_txt = "```\n" + read(gridFile(file_prefix)) + "\n```";

    // Delete grid when it's game over
    if (end_game) {
        deleteFile(playerFile(file_prefix));
        deleteFile(gridFile(file_prefix));
    }

    return grid_txt;
}

std::string coopTicTacToe(int square, std::string file_prefix, std::string curr_user, std::string other_user) {
    // ======== SET UP ======== //
    if (!checkFile(playerFile(file_prefix))) {
        write(playerFile(file_prefix), "O");
        write(playerOFile(file_prefix), curr_user);
        write(playerXFile(file_prefix), other_user);
        write(gridFile(file_prefix), " | | \n-+-+-\n | | \n-+-+-\n | | ");
    }

    // ======== VARIABLES ======== //
    bool end_game = false;
    char curr_player = currPlayer(file_prefix);
    std::vector<std::vector<char>> grid_arr = readGrid(file_prefix);

    // std::cout << "grid_arr: " << grid_arr[0][0] << " " << grid_arr[0][1] << " " << grid_arr[0][2] << " " << grid_arr[1][0] << " " << grid_arr[1][1] << " " << grid_arr[1][2] << " " << grid_arr[2][0] << " " << grid_arr[2][1] << " " << grid_arr[2][2] << " " << std::endl;

    // ======== LOG USER INPUT ======= //
    int X = (square - 1) / 3;
    int Y = (square - 1) % 3;
    
    // Check invalid input
    if (read(currPlayerFile(curr_player, file_prefix)) != curr_user) {
        return "It's not your turn yet!";
    } else if (grid_arr[X][Y] != ' ') {
        return "Invalid square, this square is already taken, choose another square.";
    }  else {
        grid_arr[X][Y] = curr_player;
        writeGrid(grid_arr, file_prefix);
        changePlayer(file_prefix);
    }

    // ======== CHECK WIN ======== //
    // Columns and Rows
    for (int i = 0; i < 3; i++) {
        char begin_row = grid_arr[i][0];
        char begin_col = grid_arr[0][i];
        
        // Check row
        if (begin_row != ' ' && begin_row == grid_arr[i][1] && begin_row == grid_arr[i][2]) {
            end_game = true;
        }

        // Check col
        if (begin_col != ' ' && begin_col == grid_arr[1][i] && begin_col == grid_arr[2][i]) {
            end_game = true;
        }
    }

    // Diagonals
    if (grid_arr[0][0] != ' ' && grid_arr[0][0] == grid_arr[1][1] && grid_arr[1][1] == grid_arr[2][2]) {
        end_game = true;
    }

    if (grid_arr[0][2] != ' ' && grid_arr[0][2] == grid_arr[1][1] && grid_arr[1][1] == grid_arr[2][0]) {
        end_game = true;
    }

    if (end_game) {
        std::string win_statement;
        win_statement += "Player ";
        win_statement += curr_player;
        win_statement += " won!\n\n" + read(gridFile(file_prefix));
        write(gridFile(file_prefix), win_statement);
    }

    // Draw
    bool is_draw = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid_arr[i][j] == ' ') {
                is_draw = false;
            }
        }
    }

    if (is_draw) {
        end_game = true;
        write(gridFile(file_prefix), "It's a draw!\n\n" + read(gridFile(file_prefix)));
    }

    // ======== CONCLUSION ======== //
    // Return answer
    std::string grid_txt = "```\n" + read(gridFile(file_prefix)) + "\n```";

    // Delete grid when it's game over
    if (end_game) {
        quitCoopGame(file_prefix);
    }

    return grid_txt;
}

bool quitGame(std::string file_prefix) {
    bool successfully_quit = false;

    if (checkFile(playerFile(file_prefix))) {
        successfully_quit = true;
        deleteFile(playerFile(file_prefix));
    }

    if (checkFile(gridFile(file_prefix))) {
        successfully_quit = true;
        deleteFile(gridFile(file_prefix));
    }

    return successfully_quit;
}

bool quitCoopGame(std::string file_prefix) {
    bool successfully_quit = false;

    if (checkFile(playerFile(file_prefix))) {
        successfully_quit = true;
        deleteFile(playerFile(file_prefix));
    }
    
    if (checkFile(playerOFile(file_prefix))) {
        successfully_quit = true;
        deleteFile(playerOFile(file_prefix));
    }

    if (checkFile(playerXFile(file_prefix))) {
        successfully_quit = true;
        deleteFile(playerXFile(file_prefix));
    }

    if (checkFile(gridFile(file_prefix))) {
        successfully_quit = true;
        deleteFile(gridFile(file_prefix));
    }

    return successfully_quit;
}