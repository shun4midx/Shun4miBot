/********************************************
 * Copyright (c) 2025 Shun/翔海 (@shun4midx) *
 * Project: Shun4miBot                      *
 * File Type: C++ file                      *
 * File: main.cpp                           *
 ********************************************/

#include <iostream>
#include <format>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <dpp/dpp.h>
#include <dpp/message.h>
#include <dpp/user.h>
#include <dpp/cluster.h>
#include "parsing/parsing.h"
#include "spinner/spinner.h"
#include "shuffle/shuffle.h"
#include "file_manager/file_manager.h"
#include "japanese/japanese.h"
#include "tic_tac_toe/tic_tac_toe.h"
#include "zhuyin/zhuyin.h"
#include "to_do/to_do.h"
#include "dictionary/dictionary.h"
#include "zhuyinify/zhuyinify.h"
#include "format/format.h"

int main() {
    std::srand(unsigned(time(NULL)));

    dpp::cluster bot(read("bot_token.txt"), dpp::i_default_intents | dpp::i_message_content);

    // Main Program
    bot.on_log(dpp::utility::cout_logger());
    
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        // ======== SHUN TRIVIA ======= //
        if (event.command.get_command_name() == "shun_names") {
            event.reply("Shun\n翔海\nShun/翔海\nしゅう\nしゅん\nShun4mi");
        } else if (event.command.get_command_name() == "shun_projects") {
            event.reply("Shun4MIDI Music Tool (shun4midi_en, shun4midi_jp)\nShun4miBot\nPossible Shun4MIDI bot too");
        } else if (event.command.get_command_name() == "shun_pronouns") {
            event.reply("He/Him, or whatever that equivalent is in another language, except for Japanese.\n\nIn Japanese, Shun uses *boku* instead of *ore* in casual contexts but uses ボク instead of 僕 or ぼく due to personal reasons, so please quote him with ボク when using Japanese! If it's not allowed out of formality of a text, please modify his quote to say 自分 instead.\n\nFor example, when Shun refers to the Yorushika song 'That's why I gave up on Music' in a personal context relating to himself, he usually would write だからボクは音楽を辞めた instead, but if that's not allowed in a text due to formality, he would reference the song but modify it to match his personal context by saying だから自分は音楽をやめった!");
        }

        // ======== Shun4miBot QUIRKS ======= //
        if (event.command.get_command_name() == "best_programming_language") {
            event.reply("C++!");
        } else if (event.command.get_command_name() == "is_cpp_good") {
            event.reply("Yes!");
        } else if (event.command.get_command_name() == "is_shun_good") {
            event.reply("Yes! *(i was forced to say that, no hes not, im held hostage by him, im scared, pls let me free)*");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            event.edit_original_response(dpp::message("Yes! Of course! :D"));
        } else if (event.command.get_command_name() == "do_i_speak_japanese") {
            event.reply("ええ、ボクは日本語を話すよ！");
        } else if (event.command.get_command_name() == "do_i_speak_mandarin") {
            event.reply("ㄨㄛˇ ㄅㄨˊ ㄏㄨㄟˋ ㄕㄨㄛ ㄓㄨㄥ ㄨㄣˊ（ㄎㄨ ㄎㄨ\n*沒有啦 開玩笑啦 我會啦 只是很爛而已* :clown:");
        } else if (event.command.get_command_name() == "leetcode_stone_game_ans") {
            event.reply("```\nbool stoneGame(vector<int>& piles) {\n    return true;\n}\n```");
        } else if (event.command.get_command_name() == "this_is_fine") {
            event.reply("<:this_is_fine:1336212781673742408>");
        }

        // ======== PROGRAMMING AID ======== //
        if (event.command.get_command_name() == "c_includes") {
            event.reply("#include <stdio.h>\n#include <stdlib.h>\n#include <stdbool.h>\n#include <string.h>\n#include <math.h>");
        } else if (event.command.get_command_name() == "cpp_includes") {
            event.reply("#include <iostream>\n#include <vector>\n#include <string>\n#include <cmath>");
        } 

        // ======== USER INTERACTIONS ======== //
        if (event.command.get_command_name() == "say_hi") {
            // Figure out the discriminator if applicable
            std::string full_username = "";
            std::string discriminator_str = "";
            if (event.command.usr.discriminator != (uint16_t)(0)) {
                discriminator_str = std::to_string(event.command.usr.discriminator);
                while (discriminator_str.length() < 4) {
                    discriminator_str = "0" + discriminator_str;
                }
                full_username = event.command.usr.username + "#" + discriminator_str; // Format full username
            } else {
                full_username = "@" + event.command.usr.username; // Add @ to username
            }

            event.reply("Hey there, **" + event.command.usr.global_name + " (" + full_username + ")**" + "!");
        } else if (event.command.get_command_name() == "say") {
            std::string quote = std::get<std::string>(event.get_parameter("quote"));
            std::string this_is_fine_emoji = "<:this_is_fine:1336212781673742408>";
            std::string this_is_fine = ":this_is_fine:";
            if (quote.find(this_is_fine) != std::string::npos) {
                quote.replace(quote.find(this_is_fine), this_is_fine.length(), this_is_fine_emoji);
            }
            event.reply(quote);
        }

        // ======== SPINNER ======== //
        if (event.command.get_command_name() == "spin" || event.command.get_command_name() == "spin_alt" || event.command.get_command_name() == "spin_separator") {
            std::string choices = std::get<std::string>(event.get_parameter("choices"));
            std::string parsed_choice, winner;
            if (event.command.get_command_name() == "spin") {
                parsed_choice = vectorString(parse(choices, " "));
                winner = spin(choices, " ");
            } else if (event.command.get_command_name() == "spin_alt") {
                parsed_choice = vectorString(parse(choices, "|"));
                winner = spin(choices, "|");
            } else if (event.command.get_command_name() == "spin_separator") {
                std::string separator = std::get<std::string>(event.get_parameter("separator"));
                parsed_choice = vectorString(parse(choices, separator));
                winner = spin(choices, separator);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            // Spin menu
            dpp::embed choice_menu = dpp::embed()
                .set_color(dpp::colors::sage_green)
                .set_title("It's Shun4miWheel Time!\nSpinning in Progress...")
                .set_author(event.command.usr.global_name, "https://youtu.be/dQw4w9WgXcQ", event.command.usr.get_avatar_url(0, dpp::image_type::i_png, true))
                .add_field(
                    "Spinned from...",
                    parsed_choice
                );
            dpp::message choice_message(event.command.channel_id, choice_menu);
            event.reply(choice_message);
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));

            // Choice
            dpp::embed final_choice = dpp::embed()
                .set_color(dpp::colors::cyan)
                .set_title("It's Shun4miWheel Time!")
                .set_author(event.command.usr.global_name, "https://youtu.be/dQw4w9WgXcQ", event.command.usr.get_avatar_url(0, dpp::image_type::i_png, true))
                .add_field(
                    "Spinned from...",
                    parsed_choice
                )
                .add_field(
                    (winner != "Invalid separator. Separators can only be **one character** long." ? ":tada: Winner: " + winner + " :tada:" : ""),
                    "",
                    false
                );
            dpp::message final_message(event.command.channel_id, final_choice);
            event.edit_original_response(final_message);
        } else if (event.command.get_command_name() == "shuffle" || event.command.get_command_name() == "shuffle_alt" || event.command.get_command_name() == "shuffle_separator") {
        // ======== SHUFFLE ======== //
            std::string list = std::get<std::string>(event.get_parameter("list"));
            std::string parsed_list, shuffled_list;
            if (event.command.get_command_name() == "shuffle") {
                parsed_list = vectorString(parse(list, " "));
                shuffled_list = vectorString(shuffleList(list, " "));
            } else if (event.command.get_command_name() == "shuffle_alt") {
                parsed_list = vectorString(parse(list, "|"));
                shuffled_list = vectorString(shuffleList(list, "|"));
            } else if (event.command.get_command_name() == "shuffle_separator") {
                std::string separator = std::get<std::string>(event.get_parameter("separator"));
                parsed_list = vectorString(parse(list, separator));
                shuffled_list = vectorString(shuffleList(list, separator));
            }

            // Shuffled list
            dpp::embed final_choice = dpp::embed()
                .set_color(dpp::colors::cyan)
                .set_title("It's Shun4miShuffle Time!")
                .set_author(event.command.usr.global_name, "https://youtu.be/dQw4w9WgXcQ", event.command.usr.get_avatar_url(0, dpp::image_type::i_png, true))
                .add_field(
                    "Original List:",
                    parsed_list
                )
                .add_field(
                    (shuffled_list != "Invalid separator. Separators can only be **one character** long." ? "Shuffled List:" : shuffled_list),
                    (shuffled_list != "Invalid separator. Separators can only be **one character** long." ? shuffled_list : ""),
                    false
                );
            dpp::message final_message(event.command.channel_id, final_choice);
            event.reply(final_message);
        }

        // ======== KAOMOJIS ======== // (For Lily, only need separate folder for text files since I'm lazy to edit)
        if (event.command.get_command_name() == "kaomoji_list") {
            event.reply("```\n" + read("kaomojis/" + std::get<std::string>(event.get_parameter("mood")) + "_kaomojis.txt", true) + "```");
        }

        // ======== MATH ======== // (Random number, recall theorems, etc)
        std::vector<std::string> math_operators = {"add", "subtract", "minus", "multiply", "divide", "int_divide", "modulus", "power", "factorial", "log", "random_int"};
        if (std::find(math_operators.begin(), math_operators.end(), event.command.get_command_name()) != math_operators.end()) {
            std::string curr_operator = event.command.get_command_name();
            std::string first_number_str = "first_number";
            std::string second_number_str = "second_number";

            if (curr_operator == "power") {
                first_number_str = "base";
                second_number_str = "exponent";
            } else if (curr_operator == "random_int") {
                first_number_str = "lower_bound";
                second_number_str = "upper_bound";
            }
            
            double first_num = (curr_operator != "factorial" ? std::stod(std::get<std::string>(event.get_parameter(first_number_str))) : std::stod(std::get<std::string>(event.get_parameter("number"))));
            double second_num = (curr_operator != "factorial" ? std::stod(std::get<std::string>(event.get_parameter(second_number_str))) : -1.0);
            bool valid = true;

            // Check validity (Division by 0, integer stuff, negative ranges for powers and logs etc)
            if ((curr_operator == "divide" || curr_operator == "int_divide" || curr_operator == "modulus" || curr_operator == "log") && second_num == 0) {
                // Division by 0
                event.reply("Invalid input");
                valid = false;
            } else if (curr_operator == "int_divide" || curr_operator == "modulus" || curr_operator == "factorial") {
                // Integer restrictions
                bool first_int = (abs(first_num - (int)(first_num)) <= 0.000000001);
                bool second_int = (abs(second_num - (int)(second_num)) <= 0.000000001);

                if (!first_int || !second_int) {
                    event.reply("Invalid input");
                    valid = false;
                }
            } else if (curr_operator == "power") {
                // Negative ranges for powers
                bool second_int = (abs(second_num - (int)(second_num)) <= 0.000000001);

                if (first_num < 0 && !second_int) {
                    event.reply("Invalid input");
                    valid = false;
                }
            } else if (curr_operator == "log") {
                // Negative ranges for logs and base 1 ranges (Base is first_num)
                if (first_num < 0 || second_num < 0 || first_num == 1) {
                    event.reply("Invalid input");
                    valid = false;
                }
            } else if (curr_operator == "random_int") {
                bool first_int = (abs(first_num - (int)(first_num)) <= 0.000000001);
                bool second_int = (abs(second_num - (int)(second_num)) <= 0.000000001);
                
                if (first_num > second_num) {
                    event.reply("Lower bound should be smaller than or equal to the upper bound");
                    valid = false;
                } else if (curr_operator == "random_int" && (!first_int || !second_int)) {
                    event.reply("Inputs should be integers.");
                    valid = false;
                } else if (first_num == second_num) {
                    event.reply(std::to_string((int)(first_num)));
                    valid = false;
                }
            }
            
            // Run the actual operation
            if (valid) {
                // Operator
                double ans;
                if (curr_operator == "add") { ans = first_num + second_num; }
                else if (curr_operator == "subtract" || curr_operator == "minus") { ans = first_num - second_num; }
                else if (curr_operator == "multiply") { ans = first_num * second_num; }
                else if (curr_operator == "divide") { ans = first_num / second_num; }
                else if (curr_operator == "int_divide") { ans = (double)((int)(first_num / second_num)); }
                else if (curr_operator == "modulus") { ans = (double)((int)(first_num) % (int)(second_num)); }
                else if (curr_operator == "power") { ans = std::pow(first_num, second_num); }
                else if (curr_operator == "factorial") {
                    ans = 1.0;
                    while (first_num > 0) {
                        ans *= first_num;
                        first_num--;
                    }
                }
                else if (curr_operator == "log") { ans = std::log(second_num)/std::log(first_num); }
                else if (curr_operator == "random_int") {
                    int random = std::rand();
                    int diff = second_num - first_num;
                    ans = (random % diff + diff) % diff + first_num;
                }

                // Remove trailing zeroes
                std::string ans_str = std::to_string(ans);
                ans_str.erase(ans_str.find_last_not_of('0') + 1, std::string::npos);
                ans_str.erase(ans_str.find_last_not_of('.') + 1, std::string::npos);
                
                if (ans_str[ans_str.length() - 1] == '.') { ans_str.erase(ans_str.begin() + ans_str.length() - 1); } // Convert 123. to 123

                event.reply(ans_str);
            }
        }

        // ======== TIC TAC TOE ========= //
        if (event.command.get_command_name() == "tic_tac_toe") {
            std::string square = std::get<std::string>(event.get_parameter("square"));
            std::vector<std::string> valid_squares = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

            if (std::find(valid_squares.begin(), valid_squares.end(), square) != valid_squares.end()) {
                event.reply(ticTacToe(std::stoi(square), event.command.usr.username + "_"));
            } else {
                event.reply("Please choose a valid square from 1 to 9");
            }
        } else if (event.command.get_command_name() == "quit_tic_tac_toe") {
            if (quitGame(event.command.usr.username + "_")) {
                event.reply("You successfully quit your Tic Tac Toe game!");
            } else {
                event.reply("You don't have a Tic Tac Toe game in the first place, did you mean to make a new one with the command '/tic_tac_toe' instead?");
            }
        } else if (event.command.get_command_name() == "coop_tic_tac_toe") {
            std::string square = std::get<std::string>(event.get_parameter("square"));
            std::vector<std::string> valid_squares = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

            if (std::find(valid_squares.begin(), valid_squares.end(), square) == valid_squares.end()) { // Can't find
                event.reply("Please choose a valid square from 1 to 9");
            } else {
                uint64_t curr_user = event.command.usr.id;

                std::string other_user_str = std::get<std::string>(event.get_parameter("user"));
                other_user_str = other_user_str.substr(2, other_user_str.length() - 3);

                uint64_t other_user;
                std::istringstream temp(other_user_str);
                temp >> other_user;

                if (curr_user < other_user) {
                    event.reply(coopTicTacToe(std::stoi(square), std::to_string(curr_user) + "_" + std::to_string(other_user) + "_", std::to_string(curr_user), std::to_string(other_user)));
                } else if (curr_user > other_user) {
                    event.reply(coopTicTacToe(std::stoi(square), std::to_string(other_user) + "_" + std::to_string(curr_user) + "_", std::to_string(curr_user), std::to_string(other_user)));
                } else if (curr_user == other_user) {
                    event.reply("You can't create a multiplayer game with yourself, did you mean to use the command '/tic_tac_toe' instead?");
                }
            }
        } else if (event.command.get_command_name() == "quit_coop_tic_tac_toe") {
            uint64_t curr_user = event.command.usr.id;

            std::string other_user_str = std::get<std::string>(event.get_parameter("user"));
            other_user_str = other_user_str.substr(2, other_user_str.length() - 3);

            uint64_t other_user;
            std::istringstream temp(other_user_str);
            temp >> other_user;

            std::string game_prefix;

            if (curr_user < other_user) {
                game_prefix = std::to_string(curr_user) + "_" + std::to_string(other_user) + "_";
            } else if (curr_user > other_user) {
                game_prefix = std::to_string(other_user) + "_" + std::to_string(curr_user) + "_";
            } else if (curr_user == other_user) {
                event.reply("You can't create a multiplayer game with yourself, did you mean to use the command '/quit_tic_tac_toe' instead?");
            }

            if (quitCoopGame(game_prefix)) {
                event.reply("You successfully quit your Tic-Tac-Toe game!");
            } else {
                event.reply("You two don't share a Tic-Tac-Toe game in the first place, did you mean to make a new one with the command '/coop_tic_tac_toe' instead?");
            }
        }

        // ======== ZHUYIN ======== // (I will actually make this a serious thing later, but this is for fun)
        if (event.command.get_command_name() == "zhuyin" && checkInstance("zhuyin_alpha_auths.txt", event.command.usr.username)) {
            std::string term = std::get<std::string>(event.get_parameter("term"));
            event.reply("Hmm, Shun4miBot is thinking...");

            std::vector<std::string> zhuyinify_arr = zhuyinify(term, event.command.usr.username + "_");

            while (zhuyinify_arr.size() != 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                event.edit_original_response(dpp::message(zhuyinify_arr[0]));
                zhuyinify_arr.erase(zhuyinify_arr.begin());
            }
        } else if (event.command.get_command_name() == "zhuyin_dictionary") {
            event.reply(zhuyinDict());
        } else if (event.command.get_command_name() == "zhuyin_type") {
            std::string input = std::get<std::string>(event.get_parameter("input"));
            char last_char = input[input.length() - 1];
            if (last_char != '3'  && last_char != '4' && last_char != '6' && last_char != '7') { // Last tone is a first tone
                input += ' ';
            }
            event.reply("Hmm, Shun4miBot is thinking...");
            event.edit_original_response(dpp::message(zhuyinType(input, event.command.usr.username + "_")));
        } else if (event.command.get_command_name() == "zhuyin_type_precise") {
            std::string input = std::get<std::string>(event.get_parameter("input"));
            char last_char = input[input.length() - 1];
            if (last_char != '3'  && last_char != '4' && last_char != '6' && last_char != '7') { // Last tone is a first tone
                input += ' ';
            }
            event.reply("Hmm, Shun4miBot is thinking...");
            event.edit_original_response(dpp::message(zhuyinTypePrecise(input, event.command.usr.username + "_")));
        } else if (event.command.get_command_name() == "zhuyin_type_default") {
            std::string input = std::get<std::string>(event.get_parameter("input"));
            char last_char = input[input.length() - 1];
            if (last_char != '3'  && last_char != '4' && last_char != '6' && last_char != '7') { // Last tone is a first tone
                input += ' ';
            }
            event.reply("Hmm, Shun4miBot is thinking...");
            event.edit_original_response(dpp::message(zhuyinTypeDefault(input, event.command.usr.username + "_")));
        } else if (event.command.get_command_name() == "qwerty_to_zhuyin") {
            std::string input = std::get<std::string>(event.get_parameter("input"));
            char last_char = input[input.length() - 1];
            if (last_char != '3'  && last_char != '4' && last_char != '6' && last_char != '7') { // Last tone is a first tone
                input += ' ';
            }
            event.reply("Hmm, Shun4miBot is thinking...");
            event.edit_original_response(dpp::message(qwertyToZhuyin(input, event.command.usr.username + "_")));
        }

        // ======== JAPANESE SUPPORT ======== //

        // ======== TO DO LIST ======== //
        if (event.command.get_command_name() == "new_list") {
            std::string list_name = std::get<std::string>(event.get_parameter("list_name"));
            std::string file_prefix = event.command.usr.username + "_" + list_name + "_";
            if (checkFile("to_do/generated_files/" + file_prefix + "list.txt")) {
                event.reply("You already have this list, did you meant to create a new list?");
            } else {
                newList(event.command.usr.username, list_name, file_prefix);
                event.reply("New list \"" + list_name + "\" has been created!");
            }
        } else if (event.command.get_command_name() == "delete_list") {
            std::string list_name = std::get<std::string>(event.get_parameter("list_name"));
            std::string file_prefix = event.command.usr.username + "_" + list_name + "_";
            if (!checkFile("to_do/generated_files/" + file_prefix + "list.txt")) {
                event.reply("You don't have this list, did you meant to create a new list?");
            } else {
                deleteList(event.command.usr.username, list_name, file_prefix);
                event.reply("The list \"" + list_name + "\" has been deleted!");
            }
        } else if (event.command.get_command_name() == "new_task") {
            std::string list_name = std::get<std::string>(event.get_parameter("list_name"));
            std::string task_name = std::get<std::string>(event.get_parameter("task_name"));
            std::string file_prefix = event.command.usr.username + "_" + list_name + "_";
            if (!checkFile("to_do/generated_files/" + file_prefix + "list.txt")) {
                event.reply("You don't have this list, did you meant to create a new list?");
            } else {
                newTask(task_name, file_prefix);
                std::string content = "Your new task has been created, here is your updated list for \"" + list_name + "\"!\n```\n" + numberify(readVector(listPath(file_prefix)));
                    if (content.length() <= 1991) {
                        event.reply(content + "```\n");
                    } else {
                        std::string str1 = content.substr(0, 1991);
                        std::string str2 = content.substr(1991);

                        event.reply(str1 + "\n```");
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                        while (str2.length() > 1991) {
                            str1 = str2.substr(0, 1991);
                            str2 = str2.substr(1991);
                            event.reply("```\n" + str1 + "\n```");
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        }

                        event.reply("```\n" + str2 + "\n```");
                    }
            }
        } else if (event.command.get_command_name() == "delete_task") {
            std::string list_name = std::get<std::string>(event.get_parameter("list_name"));
            int task_priority = std::stoi(std::get<std::string>(event.get_parameter("task_priority")));
            std::string file_prefix = event.command.usr.username + "_" + list_name + "_";
            if (!checkFile("to_do/generated_files/" + file_prefix + "list.txt")) {
                event.reply("You don't have this list, did you meant to create a new list?");
            } else {
                if (deleteTask(task_priority, file_prefix)) {
                    std::string content = "Your task has been deleted, here is your updated list for \"" + list_name + "\"!\n```\n" + numberify(readVector(listPath(file_prefix)));
                    
                    if (content.length() <= 1991) {
                        event.reply(content + "\n```");
                    } else {
                        std::string str1 = content.substr(0, 1991);
                        std::string str2 = content.substr(1991);

                        event.reply(str1 + "\n```");
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                        while (str2.length() > 1991) {
                            str1 = str2.substr(0, 1991);
                            str2 = str2.substr(1991);
                            event.reply("```\n" + str1 + "\n```");
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        }

                        event.reply("```\n" + str2 + "\n```");
                    }
                } else {
                    event.reply("Your input is invalid.");
                }
            }
        } else if (event.command.get_command_name() == "swap_priorities") {
            std::string list_name = std::get<std::string>(event.get_parameter("list_name"));
            int task_priority1 = std::stoi(std::get<std::string>(event.get_parameter("task_priority1")));
            int task_priority2 = std::stoi(std::get<std::string>(event.get_parameter("task_priority2")));
            std::string file_prefix = event.command.usr.username + "_" + list_name + "_";
            if (!checkFile("to_do/generated_files/" + file_prefix + "list.txt")) {
                event.reply("You don't have this list, did you meant to create a new list?");
            } else {
                if (task_priority1 == task_priority2) {
                    event.reply("? Did you have a typo with task priorities?");
                } else if (swapPriorities(task_priority1, task_priority2, file_prefix)) {
                    std::string content = "Your tasks' priorities have been swapped, here is your updated list for \"" + list_name + "\"!\n```\n" + numberify(readVector(listPath(file_prefix)));

                    if (content.length() <= 1991) {
                        event.reply(content + "\n```");
                    } else {
                        std::string str1 = content.substr(0, 1991);
                        std::string str2 = content.substr(1991);

                        event.reply(str1 + "\n```");
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                        while (str2.length() > 1991) {
                            str1 = str2.substr(0, 1991);
                            str2 = str2.substr(1991);
                            event.reply("```\n" + str1 + "\n```");
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        }

                        event.reply("```\n" + str2 + "\n```");
                    }
                } else {
                    event.reply("Your input is invalid.");
                }
            }
        } else if (event.command.get_command_name() == "bump_prioritiy") {
            std::string list_name = std::get<std::string>(event.get_parameter("list_name"));
            int task_priority = std::stoi(std::get<std::string>(event.get_parameter("task_priority")));
            int new_priority = std::stoi(std::get<std::string>(event.get_parameter("new_priority")));
            std::string file_prefix = event.command.usr.username + "_" + list_name + "_";
            if (!checkFile("to_do/generated_files/" + file_prefix + "list.txt")) {
                event.reply("You don't have this list, did you meant to create a new list?");
            } else {
                if (task_priority == new_priority) {
                    event.reply("? Did you have a typo with task priorities?");
                } else if (bumpPriority(task_priority, new_priority, file_prefix)) {
                    std::string content = "Your task's priority have been bumped, here is your updated list for \"" + list_name + "\"!\n```\n" + numberify(readVector(listPath(file_prefix)));

                    if (content.length() <= 1991) {
                        event.reply(content + "\n```");
                    } else {
                        std::string str1 = content.substr(0, 1991);
                        std::string str2 = content.substr(1991);

                        event.reply(str1 + "\n```");
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                        while (str2.length() > 1991) {
                            str1 = str2.substr(0, 1991);
                            str2 = str2.substr(1991);
                            event.reply("```\n" + str1 + "\n```");
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        }

                        event.reply("```\n" + str2 + "\n```");
                    }
                } else {
                    event.reply("Your input is invalid.");
                }
            }
        } else if (event.command.get_command_name() == "all_lists") {
            std::string content = allLists(event.command.usr.username);

            if (content.length() <= 1991) {
                event.reply(content);
            } else {
                std::string str1 = content.substr(0, 1991);
                std::string str2 = content.substr(1991);

                event.reply(str1 + "\n```");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                while (str2.length() > 1991) {
                    str1 = str2.substr(0, 1991);
                    str2 = str2.substr(1991);
                    event.reply("```\n" + str1 + "\n```");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                event.reply("```\n" + str2);
            }
        } else if (event.command.get_command_name() == "view_list") {
            std::string list_name = std::get<std::string>(event.get_parameter("list_name"));
            std::string file_prefix = event.command.usr.username + "_" + list_name + "_";
            if (checkFile("to_do/generated_files/" + file_prefix + "list.txt")) {
                std::string content = "Here is your list for \"" + list_name + "\"!\n```\n" + numberify(readVector(listPath(file_prefix)));

                if (content.length() <= 1991) {
                    event.reply(content + "\n```");
                } else {
                    std::string str1 = content.substr(0, 1991);
                    std::string str2 = content.substr(1991);

                    event.reply(str1 + "\n```");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                    while (str2.length() > 1991) {
                        str1 = str2.substr(0, 1991);
                        str2 = str2.substr(1991);
                        event.reply("```\n" + str1 + "\n```");
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    }

                    event.reply("```\n" + str2 + "\n```");
                }
            } else {
                event.reply("You don't have this list, did you meant to create a new list?");
            }
        } else if (event.command.get_command_name() == "rename_list") {
            std::string original_name = std::get<std::string>(event.get_parameter("original_name"));
            std::string new_name = std::get<std::string>(event.get_parameter("new_name"));
            std::string file_prefix = event.command.usr.username + "_" + original_name + "_";
            if (!checkFile("to_do/generated_files/" + file_prefix + "list.txt")) {
                event.reply("You don't have this list, did you meant to create a new list?");
            } else {
                renameList(event.command.usr.username, original_name, new_name, file_prefix);
                event.reply("The list \"" + original_name + "\" has been renamed to \"" + new_name + "\"!");
            }
        } else if (event.command.get_command_name() == "rename_task") {
            std::string list_name = std::get<std::string>(event.get_parameter("list_name"));
            std::string new_name = std::get<std::string>(event.get_parameter("new_name"));
            int task_priority = std::stoi(std::get<std::string>(event.get_parameter("task_priority")));
            std::string file_prefix = event.command.usr.username + "_" + list_name + "_";
            if (!checkFile("to_do/generated_files/" + file_prefix + "list.txt")) {
                event.reply("You don't have this list, did you meant to create a new list?");
            } else {
                int success = renameTask(task_priority, new_name, file_prefix);
                if (success == 2) {
                    std::string content = "Your task has been renamed, here is your updated list for \"" + list_name + "\"!\n```\n" + numberify(readVector(listPath(file_prefix)));

                    if (content.length() <= 1991) {
                        event.reply(content + "\n```");
                    } else {
                        std::string str1 = content.substr(0, 1991);
                        std::string str2 = content.substr(1991);

                        event.reply(str1 + "\n```");
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                        while (str2.length() > 1991) {
                            str1 = str2.substr(0, 1991);
                            str2 = str2.substr(1991);
                            event.reply("```\n" + str1 + "\n```");
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        }

                        event.reply("```\n" + str2 + "\n```");
                    }
                } else if (success == 1) {
                    event.reply("? Why are you renaming something with the same name as before?");
                } else if (success == 0) {
                    event.reply("Said task priority does not exist.");
                }
            }
        } else if (event.command.get_command_name() == "swap_list_priorities") {
            int list_priority1 = std::stoi(std::get<std::string>(event.get_parameter("list_priority1")));
            int list_priority2 = std::stoi(std::get<std::string>(event.get_parameter("list_priority2")));
            std::string content = swapListPriorities(list_priority1, list_priority2, event.command.usr.username);

            if (content.length() <= 1991) {
                event.reply(content);
            } else {
                std::string str1 = content.substr(0, 1991);
                std::string str2 = content.substr(1991);

                event.reply(str1 + "\n```");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                while (str2.length() > 1991) {
                    str1 = str2.substr(0, 1991);
                    str2 = str2.substr(1991);
                    event.reply("```\n" + str1 + "\n```");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                event.reply("```\n" + str2);
            }
        } else if (event.command.get_command_name() == "bump_list_priority") {
            int list_priority = std::stoi(std::get<std::string>(event.get_parameter("list_priority")));
            int new_priority = std::stoi(std::get<std::string>(event.get_parameter("new_priority")));
            std::string content = bumpListPriority(list_priority, new_priority, event.command.usr.username);

            if (content.length() <= 1991) {
                event.reply(content);
            } else {
                std::string str1 = content.substr(0, 1991);
                std::string str2 = content.substr(1991);

                event.reply(str1 + "\n```");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                while (str2.length() > 1991) {
                    str1 = str2.substr(0, 1991);
                    str2 = str2.substr(1991);
                    event.reply("```\n" + str1 + "\n```");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                event.reply("```\n" + str2);
            }
        }
        
        // ======== SPOTIFY LINKS ======== //
        if (event.command.get_command_name() == "spotify_playlist" && checkInstance("spotify_shortcut_auths.txt", event.command.usr.username)) {
            std::string playlist = std::get<std::string>(event.get_parameter("playlist"));
            std::transform(playlist.begin(), playlist.end(), playlist.begin(), ::tolower);
            std::unordered_map<std::string, std::vector<std::string>> parsed_dict = parseDict("spotify/playlist_dict.txt");

            if (parsed_dict.find(playlist) != parsed_dict.end()) { // Found the playlist
                event.reply(parsed_dict[playlist][0]);
            } else {
                event.reply("This shortcut doesn't exist"); 
            }
        }

        // ======== EMOJI KITCHEN ======= // (When I'm on my computer for example, I want to access Emoji Kitchen too)
        if (event.command.get_command_name() == "emoji_kitchen") {
            std::string shortcut = std::get<std::string>(event.get_parameter("shortcut"));
            std::transform(shortcut.begin(), shortcut.end(), shortcut.begin(), ::tolower);
            std::unordered_map<std::string, std::vector<std::string>> parsed_dict = parseDict("emoji_kitchen/shortcut_dict.txt", true);
            parsed_dict = reverseDict(parsed_dict);

            if (parsed_dict.find(shortcut) != parsed_dict.end()) { // Found the shortcut
                std::string file_name = parsed_dict[shortcut][0];
                dpp::message message(event.command.channel_id, "");
                message.add_file(file_name, dpp::utility::read_file(filePath("emoji_kitchen/images/" + file_name, true)));
                event.reply(message);
            } else {
                event.reply("This shortcut doesn't exist"); 
            }
        }

        // ======== FORMAT TEXT ======== // (Subscripts, Superscripts, Greek symbols, Math symbols, just made for copy and pasting ease, could be considered a mini text parser)
        if (event.command.get_command_name() == "format") {
            std::string input = std::get<std::string>(event.get_parameter("input"));
            event.reply(formatInput(input));
        }

        // ======== Shun4MIDI ======== //
    });

    // ========= LISTENING ======== //
    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        // Carry on only if it's not from the bot itself
        if (event.msg.author.format_username() != read("bot_username.txt")) {
            std::string message = event.msg.content;

            // ======== Shun4miBotSays (My function only) ======= //
            if (message.find("/bot_say") == 0 && checkInstance("bot_say_auths.txt", event.msg.author.username)) { // Begins with /spin
                std::string command = "/bot_say";
                std::string quote = message.substr(command.length() + 1, message.length() - command.length());
                bot.message_delete(event.msg.id, event.msg.channel_id);

                // This is fine
                std::string this_is_fine_emoji = "<:this_is_fine:1336212781673742408>";
                std::string this_is_fine = ":this_is_fine:";
                if (quote.find(this_is_fine) != std::string::npos) {
                    quote.replace(quote.find(this_is_fine), this_is_fine.length(), this_is_fine_emoji);
                }

                event.send(quote);
            }

            // ======== SPIN ======== //
            if (message.find("/spin") == 0) { // Begins with /spin
                std::string command = "/spin";
                std::string choices = message.substr(command.length() + 1, message.length() - command.length());

                std::string parsed_choice, winner;
                parsed_choice = vectorString(parse(choices, "\n"));
                winner = spin(choices, "\n");

                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                // Spin menu
                dpp::embed choice_menu = dpp::embed()
                    .set_color(dpp::colors::sage_green)
                    .set_title("It's Shun4miWheel Time!\nSpinning in Progress...")
                    .set_author(event.msg.author.global_name, "https://youtu.be/dQw4w9WgXcQ", event.msg.author.get_avatar_url(0, dpp::image_type::i_png, true))
                    .add_field(
                        "Spinned from...",
                        parsed_choice
                    );
                dpp::message choice_message(event.msg.channel_id, choice_menu);
                event.reply(choice_message);
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));

                // Choice
                dpp::embed final_choice = dpp::embed()
                    .set_color(dpp::colors::cyan)
                    .set_title("It's Shun4miWheel Time!")
                    .set_author(event.msg.author.global_name, "https://youtu.be/dQw4w9WgXcQ", event.msg.author.get_avatar_url(0, dpp::image_type::i_png, true))
                    .add_field(
                        "Spinned from...",
                        parsed_choice
                    )
                    .add_field(
                        (winner != "Invalid separator. Separators can only be **one character** long." ? ":tada: Winner: " + winner + " :tada:" : ""),
                        "",
                        false
                    );
                dpp::message final_message(event.msg.channel_id, final_choice);
                event.reply(final_message);
            }

            // ======== SHUFFLE ======== //
            if (message.find("/shuffle") == 0) { // Begins with /shuffle
                std::string command = "/shuffle";
                std::string list = message.substr(command.length() + 1, message.length() - command.length());
                event.reply(vectorString(shuffleList(list, "\n")));
            }

            // ======== CUTLET ======== //
            if (message.find("/cutlet") == 0 && checkInstance("cutlet_auths.txt", event.msg.author.username)) { // Begins with /cutlet
                std::string command = "/cutlet";
                std::string quote = message.substr(command.length() + 1, message.length() - command.length());
                event.reply(cppCutlet(quote, event.msg.author.username + "_" + std::to_string(event.msg.sent) + "_"));
            } else if (message.find("/to_romaji") == 0 && checkInstance("cutlet_auths.txt", event.msg.author.username)) { // Begins with /to_romaji (This is unpunctuated)
                std::string command = "/to_romaji";
                std::string quote = message.substr(command.length() + 1, message.length() - command.length());
                event.reply(toRomaji(quote, event.msg.author.username + "_" + std::to_string(event.msg.sent) + "_"));
            } else if (message.find("/format_cutlet") == 0 && checkInstance("cutlet_auths.txt", event.msg.author.username)) { // Begins with /format_cutlet
                std::string command = "/format_cutlet";
                std::string quote = message.substr(command.length() + 1, message.length() - command.length());
                event.reply(formatCutlet(quote));
            } else if (message.find("/jp_shortcut") == 0 && checkInstance("jp_shortcut_auths.txt", event.msg.author.username)) { // Begins with /jp_shortcut
                std::string command = "/jp_shortcut";
                std::string quote = message.substr(command.length() + 1, message.length() - command.length());
                event.reply(shortcutToJp(quote));
            } else if (message.find("/reset_cutlet") == 0 && checkInstance("cutlet_auths.txt", event.msg.author.username)) { // Begins with /cutlet
                write("japanese/generated_files/edited_prefixes.txt", "", true);
                event.reply("Cutlet has been reset!");
            }

            // ======== EMOJI KITCHEN ======= //
            if (message.find("/emoji_kitchen_shortcuts") == 0) {
                std::string command = "/emoji_kitchen_shortcuts";
                std::string quote = message.substr(command.length() + 1, message.length() - command.length());
                event.reply("```\n" + read("emoji_kitchen/shortcut_dict.txt", true) + "\n```");
            }

            // ======== MISC PHOTOS ======== //
            if (message == "/dulc_files" && checkInstance("misc_auths.txt", event.msg.author.username)) {
                event.reply(read("misc/misc_files.txt"));
            } else if (message.find("/dulc") == 0 && checkInstance("misc_auths.txt", event.msg.author.username)) {
                std::string command = "/dulc";
                std::string quote = message.substr(command.length() + 1, message.length() - command.length());
                std::transform(quote.begin(), quote.end(), quote.begin(), ::tolower);
                
                if (checkInstance("misc/misc_files.txt", quote)) {
                    std::string file_name;

                    // Code exception file
                    if (checkInstance("misc/misc_gif_exceptions.txt", quote)) {
                        file_name = quote + ".gif";
                    } else {
                        file_name = quote + ".png";
                    }

                    dpp::message message(event.msg.channel_id, "");
                    message.add_file(file_name, dpp::utility::read_file(filePath("misc/images/" + file_name)));
                    event.reply(message);
                } else {
                    event.reply("Said file doesn't exist");
                }
            }

            // ======== SPOTIFY ======== //    
            // We want "/spotify_new and /spotify_undo" and also /spotify_view
            if (checkInstance("spotify_edit_auths.txt", event.msg.author.username)) {
                if (message.find("/spotify_new") == 0 || message.find("/spotify_add") == 0) {
                    std::string command = "/spotify_new";
                    std::string shortcut = message.substr(command.length() + 1, message.length() - command.length());
                    std::vector<std::string> parsed_shortcut = parse(shortcut, "\n");

                    std::string formated_shortcut = parsed_shortcut[0] + ": " + parsed_shortcut[1];
                    write("spotify/playlist_dict.txt", read("spotify/playlist_dict.txt") + "\n" + formated_shortcut);

                    event.reply("New Spotify shortcut added!");
                } else if (message.find("/spotify_undo") == 0) {
                    std::vector<std::string> all_shortcuts = parse(read("spotify/playlist_dict.txt"), "\n");
                    all_shortcuts.pop_back();
                    write("spotify/playlist_dict.txt", vectorString(all_shortcuts));
                    event.reply("Previous Spotify shortcut undone!");
                } else if (message.find("/spotify_view") == 0) {
                    std::string content = read("spotify/playlist_dict.txt");
                    
                    if (content.length() <= 1991) {
                        event.send("```\n" + content + "\n```");
                    } else {
                        std::string str1 = content.substr(0, 1991);
                        std::string str2 = content.substr(1991);

                        event.send("```\n" + str1 + "\n```");
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                        while (str2.length() > 1991) {
                            str1 = str2.substr(0, 1991);
                            str2 = str2.substr(1991);
                            event.send("```\n" + str1 + "\n```");
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        }

                        event.send("```\n" + str2 + "\n```");
                    }
                }
            }

            // ======== PLURAL KIT THING FOR MY ACCOUNTS ======== //

            // ======== Shun4mi(Bot), "Shut up you lil shit" ======== //
            std::string og_message = message;
            std::transform(message.begin(), message.end(), message.begin(), ::tolower);
            if (message.find("shun for midex") != std::string::npos) {
                bot.message_add_reaction(event.msg.id, event.msg.channel_id, "🤡");
                event.reply("Fuck you");
            } else if (message.find("shun4mibot") != std::string::npos || ((message.find("my bot") != std::string::npos || message.find("my discord bot") != std::string::npos) && event.msg.author.username == "shun4midx")) {
                event.reply("Omg me mention! I love Shun4mis :D :ocean::ocean:", true);
            } else if (message.find("shun4mi") != std::string::npos || message.find("shunami") != std::string::npos || message.find("tsunami") != std::string::npos || message.find("tsun4mi") != std::string::npos) {
                event.reply("I love Shun4mis! :ocean::ocean:", true);
            } else if (message.find("shut up you lil shit") != std::string::npos || message.find("shut up, you lil shit") != std::string::npos) {
                dpp::message msg(event.msg.channel_id, "*help mi shun is abusing mi :sob::sob:*");
                msg.set_reference(event.msg.id);

                bot.message_create(msg, [&bot](const dpp::confirmation_callback_t& callback) {
                    if (callback.is_error()) return;

                    dpp::message sent_msg = std::get<dpp::message>(callback.value);

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    sent_msg.set_content(":(");
                    bot.message_edit(sent_msg);
                });
            }

            // ======= THIS IS FINE ======= //
            std::string this_is_fine_emoji = "<:this_is_fine:1336212781673742408>";
            std::string this_is_fine = ":this_is_fine:";
            std::string this_is_fine_dpp_emoji = "this_is_fine:1336212781673742408";

            if (message.find("this is fine") != std::string::npos && message.find("/bot_say") != 0) {
                bot.message_add_reaction(event.msg.id, event.msg.channel_id, this_is_fine_dpp_emoji);
                event.reply("This is fine <:this_is_fine:1336212781673742408>", true);

                dpp::message msg(event.msg.channel_id, "I'm not being abused by Shun at all <:this_is_fine:1336212781673742408>");
                bot.message_create(msg, [&bot](const dpp::confirmation_callback_t& callback) {
                    if (callback.is_error()) return;

                    dpp::message sent_msg = std::get<dpp::message>(callback.value);

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    bot.message_delete(sent_msg.id, sent_msg.channel_id);
                });
            }
            
            if (og_message.find(":this_is_fine:") != std::string::npos && message.find("/bot_say") != 0) {
                og_message.replace(og_message.find(":this_is_fine:"), this_is_fine.length(), this_is_fine_emoji);
                bot.message_add_reaction(event.msg.id, event.msg.channel_id, this_is_fine_dpp_emoji);
                event.reply(og_message, true);
            }

            if (message.find("meme") != std::string::npos && message.find("antimeme") == std::string::npos) { // Find meme without "antimeme"
                bot.message_add_reaction(event.msg.id, event.msg.channel_id, ":antimeme:1339228807193694209");
                event.reply("Antimeme <:antimeme:1339228807193694209>");
            } else if (message.find("antimeme") != std::string::npos) {
                bot.message_add_reaction(event.msg.id, event.msg.channel_id, this_is_fine_dpp_emoji);
                event.reply("Meme <:this_is_fine:1336212781673742408>");
            }

            // ========= SAVE ME ======== //
            if (message == "/save_me") {
                bot.message_delete(event.msg.id, event.msg.channel_id);
                event.send("<:saveme:1336983390267768863>");
            }
        }
    });

    // ======== INIT PART OF THE CODE ======== //
    bot.on_ready([&bot](const dpp::ready_t& event) {
        // Bot status
        bot.set_presence(dpp::presence(dpp::ps_idle, dpp::at_game, "Abst Alg at 3 am because of Shun's Algebra addiction"));

        if (dpp::run_once<struct register_bot_commands>()) {
            /*
            // ======= SHUN TRIVIA ======== //
            bot.global_command_create(dpp::slashcommand("shun_names", "Outputs all forms of Shun's names", bot.me.id));
            bot.global_command_create(dpp::slashcommand("shun_projects", "Outputs all forms of Shun's current projects", bot.me.id));
            bot.global_command_create(dpp::slashcommand("shun_pronouns", "What are Shun's pronouns?", bot.me.id));
            
            // ======== Shun4miBot QUIRKS ======= //
            bot.global_command_create(dpp::slashcommand("best_programming_language", "What is the best programming language?", bot.me.id));
            bot.global_command_create(dpp::slashcommand("is_cpp_good", "Is C++ good?", bot.me.id));
            bot.global_command_create(dpp::slashcommand("is_shun_good", "Is Shun good?", bot.me.id));
            bot.global_command_create(dpp::slashcommand("do_i_speak_japanese", "Do I speak Japanese?", bot.me.id));
            bot.global_command_create(dpp::slashcommand("do_i_speak_mandarin", "Do I speak Mandarin?", bot.me.id));
            bot.global_command_create(dpp::slashcommand("leetcode_stone_game_ans", "Returns the answer to LeetCode Question 877, i.e. 'Stone Game'", bot.me.id));
            bot.global_command_create(dpp::slashcommand("this_is_fine", "This is fine", bot.me.id));

            // ======= PROGRAMMING AID ======= //
            bot.global_command_create(dpp::slashcommand("c_includes", "What Shun includes in the beginning of a C program", bot.me.id));
            bot.global_command_create(dpp::slashcommand("cpp_includes", "What Shun includes in the beginning of a C++ program", bot.me.id));

            // ======== USER INTERACTIONS ======== //
            bot.global_command_create(dpp::slashcommand("say_hi", "Says hi to the user who calls the command", bot.me.id));
            bot.global_command_create(dpp::slashcommand("say", "The Shun4miBot would say whatever the user wants it to say as indicated", bot.me.id).add_option(dpp::command_option(dpp::co_string, "quote", "What you want me to say", true)));

            // ======== SPINNER ======== //
            // Default is separating by spaces, the other version is separating by |
            bot.global_command_create(dpp::slashcommand("spin", "Spins amongst choices separated by a space bar", bot.me.id).add_option(dpp::command_option(dpp::co_string, "choices", "Choices to spin from", true)));
            bot.global_command_create(dpp::slashcommand("spin_alt", "Spins amongst choices separated by a | symbol", bot.me.id).add_option(dpp::command_option(dpp::co_string, "choices", "Choices to spin from", true)));
            bot.global_command_create(dpp::slashcommand("spin_separator", "Spins amongst choices separated by a specified separator that is one character long", bot.me.id).add_option(dpp::command_option(dpp::co_string, "separator", "Separator between each choice", true)).add_option(dpp::command_option(dpp::co_string, "choices", "Choices to spin from", true)));

            // ======== SHUFFLE ======== //
            bot.global_command_create(dpp::slashcommand("shuffle", "Shuffles amongst choices separated by a space bar", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list", "List to shuffle", true)));
            bot.global_command_create(dpp::slashcommand("shuffle_alt", "Shuffles amongst choices separated by a | symbol", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list", "List to shuffle", true)));
            bot.global_command_create(dpp::slashcommand("shuffle_separator", "Shuffles amongst choices separated by a specified separator that is one character long", bot.me.id).add_option(dpp::command_option(dpp::co_string, "separator", "Separator between each choice", true)).add_option(dpp::command_option(dpp::co_string, "list", "List to shuffle", true)));

            // ======== KAOMOJIS ======== // (Outputs multiple kaomojis to copy and paste from depending on a certain mood)
            bot.global_command_create(dpp::slashcommand("kaomoji_list", "Lists out a bunch of kaomojis depending on the mood chosen by the user", bot.me.id).add_option(dpp::command_option(dpp::co_string, "mood", "Mood of kaomojis to list", true).set_auto_complete(true)));

            // ======== MATH ======== // (Include some theorems when needed later in the future)
            bot.global_command_create(dpp::slashcommand("add", "Adds two numbers together", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number to add", true)).add_option(dpp::command_option(dpp::co_string, "second_number", "Second number to add", true)));
            bot.global_command_create(dpp::slashcommand("subtract", "Subtracts two numbers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number in the subtraction equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second number in the subtraction equation", true))));
            bot.global_command_create(dpp::slashcommand("minus", "Subtracts two numbers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number in the subtraction equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second number in the subtraction equation", true))));
            bot.global_command_create(dpp::slashcommand("multiply", "Multiplies two numbers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number in the multiplication equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second number in the multiplication equation", true))));
            bot.global_command_create(dpp::slashcommand("divide", "Divides two numbers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number in the division equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second number in the division equation", true))));
            bot.global_command_create(dpp::slashcommand("int_divide", "Integer divides two integers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First integer in the integer division equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second integer in the integer division equation", true))));
            bot.global_command_create(dpp::slashcommand("modulus", "Finds the modulus of two integers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First integer in the integer modulus equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second integer in the integer modulus equation", true))));
            bot.global_command_create(dpp::slashcommand("power", "Finds the power of one number to the other number", bot.me.id).add_option(dpp::command_option(dpp::co_string, "base", "Base of the expression", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "exponent", "Exponent of the expression", true))));
            bot.global_command_create(dpp::slashcommand("factorial", "Finds the factorial of an integer", bot.me.id).add_option(dpp::command_option(dpp::co_string, "number", "Number to be factorial'ed", true)));
            bot.global_command_create(dpp::slashcommand("log", "Finds the log base one number to the other number", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "Base of the expression", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Ohter number of the expression", true))));
            bot.global_command_create(dpp::slashcommand("random_int", "Generates a random number between two integers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "lower_bound", "Lower bound", true)).add_option(dpp::command_option(dpp::co_string, "upper_bound", "Upper bound", true)));

            // ======== TIC TAC TOE ======== //
            bot.global_command_create(dpp::slashcommand("tic_tac_toe", "Use me to play Tic Tac Toe with another person irl", bot.me.id).add_option(dpp::command_option(dpp::co_string, "square", "The square you choose, counting from 1 to 9 from the top left corner", true)));
            bot.global_command_create(dpp::slashcommand("quit_tic_tac_toe", "Quit your Tic Tac Toe game", bot.me.id));
            bot.global_command_create(dpp::slashcommand("coop_tic_tac_toe", "Create a new Tic Tac Toe game with a person in this server", bot.me.id).add_option(dpp::command_option(dpp::co_string, "user", "@The user you want to play with", true)).add_option(dpp::command_option(dpp::co_string, "square", "The square you choose, counting from 1 to 9 from the top left corner", true)));
            bot.global_command_create(dpp::slashcommand("quit_coop_tic_tac_toe", "Quit your Coop Tic Tac Toe game", bot.me.id).add_option(dpp::command_option(dpp::co_string, "user", "@The user you want to play with", true)));
            
            // ======== ZHUYIN ======== // (I will actually make this a serious thing later, but this is for fun)
            bot.global_command_create(dpp::slashcommand("zhuyin", "[CURRENTLY IS A JOKE FUNCTION WITH A LIMITED DICTIONARY] Converts the input into Zhuyin", bot.me.id).add_option(dpp::command_option(dpp::co_string, "term", "The term to be converted into Zhuyin", true)));
            bot.global_command_create(dpp::slashcommand("zhuyin_dictionary", "[CURRENTLY IS A JOKE FUNCTION WITH A LIMITED DICTIONARY] Outputs term inputs that Shun's custom Zhuyin dictionary list supports", bot.me.id));
            bot.global_command_create(dpp::slashcommand("zhuyin_type", "Type on your QWERTY keyboard like it is a Zhuyin one to get Traditional Chinese characters", bot.me.id).add_option(dpp::command_option(dpp::co_string, "input",  "Remember to confirm your input by pressing Enter!", true)));
            bot.global_command_create(dpp::slashcommand("zhuyin_type_precise", "Type on your QWERTY keyboard like Zhuyin to get the most likely characters (max 6) for each sound", bot.me.id).add_option(dpp::command_option(dpp::co_string, "input",  "Remember to confirm your input by pressing Enter!", true)));
            bot.global_command_create(dpp::slashcommand("zhuyin_type_default", "Type on your QWERTY keyboard like Zhuyin to get the most likely characters (max 6) for each sound", bot.me.id).add_option(dpp::command_option(dpp::co_string, "input",  "Remember to confirm your input by pressing Enter!", true)));
            bot.global_command_create(dpp::slashcommand("qwerty_to_zhuyin", "Type on your QWERTY keyboard like it is a Zhuyin keyboard and press Enter to get your Zhuyin", bot.me.id).add_option(dpp::command_option(dpp::co_string, "input", "Remember to confirm your input by pressing Enter!", true)));
            
            // ======== JAPANESE SUPPORT ======== // (Mainly like converting words I know from English to Japanese but of course it could be romaji to kanji)

            // ======== TO DO LIST ======== // (Displayed in order 1, 2, 3, ... on the side to indicate which task)
            bot.global_command_create(dpp::slashcommand("new_list", "Creates a new to-do list", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_name", "Name of said To-Do List", true)));
            bot.global_command_create(dpp::slashcommand("delete_list", "Deletes a to-do list", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_name", "Name of said To-Do List", true)));
            bot.global_command_create(dpp::slashcommand("new_task", "Creates a new task in a to-do list", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_name", "Name of said To-Do List", true)).add_option(dpp::command_option(dpp::co_string, "task_name", "Name of said task", true)));
            bot.global_command_create(dpp::slashcommand("delete_task", "Delets a task in a to-do list", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_name", "Name of said To-Do List", true)).add_option(dpp::command_option(dpp::co_string, "task_priority", "Priority of said task", true)));
            bot.global_command_create(dpp::slashcommand("swap_priorities", "Swaps two priorities in a to-do list", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_name", "Name of said To-Do List", true)).add_option(dpp::command_option(dpp::co_string, "task_priority1", "Priority of one task", true)).add_option(dpp::command_option(dpp::co_string, "task_priority2", "Priority of another task", true)));
            bot.global_command_create(dpp::slashcommand("bump_prioritiy", "Makes a task in a to-do list have a new priority", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_name", "Name of said To-Do List", true)).add_option(dpp::command_option(dpp::co_string, "task_priority", "Priority of said task", true)).add_option(dpp::command_option(dpp::co_string, "new_priority", "New priority you want this task to have", true)));
            bot.global_command_create(dpp::slashcommand("all_lists", "Lists out all names of to-do lists said user has", bot.me.id));
            bot.global_command_create(dpp::slashcommand("view_list", "Views an existing new to-do list", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_name", "Name of said To-Do List", true)));
            bot.global_command_create(dpp::slashcommand("rename_list", "Renames a list", bot.me.id).add_option(dpp::command_option(dpp::co_string, "original_name", "Original name of said To-Do List", true)).add_option(dpp::command_option(dpp::co_string, "new_name", "New name of said To-Do List", true)));
            bot.global_command_create(dpp::slashcommand("rename_task", "Renames a task", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_name", "Name of said To-Do List", true)).add_option(dpp::command_option(dpp::co_string, "task_priority", "Task priority in said To-Do List", true)).add_option(dpp::command_option(dpp::co_string, "new_name", "New name you want this task to have", true)));
            bot.global_command_create(dpp::slashcommand("swap_list_priorities", "Swaps two priorities in all lists", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_priority1", "Priority of one list", true)).add_option(dpp::command_option(dpp::co_string, "list_priority2", "Priority of another list", true)));
            bot.global_command_create(dpp::slashcommand("bump_list_priority", "Makes a list a new priority", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list_priority", "Priority of said list", true)).add_option(dpp::command_option(dpp::co_string, "new_priority", "New priority you want this list to have", true)));

            // ======== SPOTIFY LINKS ======== //
            bot.global_command_create(dpp::slashcommand("spotify_playlist", "Supports Shun's shortcuts for Spotify playlists", bot.me.id).add_option(dpp::command_option(dpp::co_string, "playlist", "Shortcut for said playlist", true)));

            // ======== EMOJI KITCHEN ======= // (When I'm on my computer for example, I want to access Emoji Kitchen too)
            bot.global_command_create(dpp::slashcommand("emoji_kitchen", "Supports Shun's shortcuts for Emoji Kitchen stickers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "shortcut", "Shortcut for said sticker", true)));

            // ======== FORMAT TEXT ======== // (Subscripts, Superscripts, Greek symbols, Math symbols, just made for copy and pasting ease, could be considered a mini text parser)
            bot.global_command_create(dpp::slashcommand("format", "Converts the input into a copy and paste-able text with math symbols", bot.me.id).add_option(dpp::command_option(dpp::co_string, "input", "The input to be converted", true)));

            // ======== Shun4MIDI ======== //
            */
        }
    });

    // ======== AUTOCOMPLETE ======= //
    bot.on_autocomplete([&bot](const dpp::autocomplete_t & event) {
        for (auto & opt : event.options) {
            if (opt.focused) {
                std::string uservalue = std::get<std::string>(opt.value);
                bot.interaction_response_create(event.command.id, event.command.token, dpp::interaction_response(dpp::ir_autocomplete_reply)
                    .add_autocomplete_choice(dpp::command_option_choice("Angry", std::string("angry")))
                    .add_autocomplete_choice(dpp::command_option_choice("Sad", std::string("sad")))
                    .add_autocomplete_choice(dpp::command_option_choice("Happy", std::string("happy")))
                    .add_autocomplete_choice(dpp::command_option_choice("Hug", std::string("hug")))
                    .add_autocomplete_choice(dpp::command_option_choice("Blush", std::string("blush")))
                    .add_autocomplete_choice(dpp::command_option_choice("Shy", std::string("shy")))
                );
                break;
            }
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}