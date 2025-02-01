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

int main() {
    std::srand(unsigned(time(NULL)));
    // Read BOT_TOKEN
    std::string bot_token_path = (std::filesystem::path(__FILE__).parent_path().parent_path().parent_path()/"bot_token.txt").string();
    std::ifstream bot_token_file(bot_token_path);
    std::string BOT_TOKEN;
    getline(bot_token_file, BOT_TOKEN);
    bot_token_file.close();

    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);
 
    // Main Program
    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        // ======== SHUN TRIVIA ======= //
        if (event.command.get_command_name() == "shun_names") {
            event.reply("Shun\n翔海\nShun/翔海\nしゅう\nしゅん\nShun4mi");
        }

        if (event.command.get_command_name() == "shun_projects") {
            event.reply("Shun4MIDI Music Tool (shun4midi_en, shun4midi_jp)\nShun4miBot\nPossible Shun4MIDI bot too");
        }

        // ======== Shun4miBot QUIRKS ======= //
        if (event.command.get_command_name() == "best_programming_language") {
            event.reply("C++!");
        } 

        if (event.command.get_command_name() == "is_cpp_good") {
            event.reply("Yes!");
        } 

        if (event.command.get_command_name() == "is_shun_good") {
            event.reply("Yes! *(i was forced to say that, no hes not, im held hostage by him, im scared, pls let me free)*");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            event.edit_original_response(dpp::message("Yes! Of course! :D"));
        }

        if (event.command.get_command_name() == "do_i_speak_japanese") {
            event.reply("ええ、ボクは日本語を話すよ！");
        } 

        if (event.command.get_command_name() == "do_i_speak_mandarin") {
            event.reply("ㄨㄛˇ ㄅㄨˊ ㄏㄨㄟˋ ㄕㄨㄛ ㄓㄨㄥ ㄨㄣˊ（ㄎㄨ ㄎㄨ\n*沒有啦 開玩笑啦 我會啦 只是很爛而已* :clown:");
        } 

        // ======== PROGRAMMING AID ======== //
        if (event.command.get_command_name() == "c_includes") {
            event.reply("#include <stdio.h>\n#include <stdlib.h>\n#include <stdbool.h>\n#include <string.h>\n#include <math.h>");
        }
        
        if (event.command.get_command_name() == "cpp_includes") {
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
        }

        if (event.command.get_command_name() == "say") {
            std::string quote = std::get<std::string>(event.get_parameter("quote"));
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
        }

        // ======== SHUFFLE ======== //
        if (event.command.get_command_name() == "shuffle" || event.command.get_command_name() == "shuffle_alt" || event.command.get_command_name() == "shuffle_separator") {
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
            std::string mood = std::get<std::string>(event.get_parameter("mood"));
            std::string kaomoji_mood_path = (std::filesystem::path(__FILE__).parent_path()/"kaomojis/").string() + mood + "_kaomojis.txt";
            std::ifstream kaomoji_mood_file(kaomoji_mood_path);
            std::string kaomoji_line;

            std::string output = "";

            while (getline(kaomoji_mood_file, kaomoji_line)) {
                output = output + kaomoji_line + "\n";
            }

            kaomoji_mood_file.close();

            output = "```\n" + output + "```";

            event.reply(output);
        }

        // ======== MATH ======== // (Random number, recall theorems, etc)
        std::vector<std::string> math_operators = {"add", "subtract", "minus", "multiply", "divide", "int_divide", "modulus", "power", "factorial", "log"};
        if (std::find(math_operators.begin(), math_operators.end(), event.command.get_command_name()) != math_operators.end()) {
            std::string curr_operator = event.command.get_command_name();
            double first_num = (curr_operator != "factorial" ? std::stod(std::get<std::string>(event.get_parameter("first_number"))) : std::stod(std::get<std::string>(event.get_parameter("number"))));
            double second_num = (curr_operator != "factorial" ? std::stod(std::get<std::string>(event.get_parameter("second_number"))) : -1.0);
            bool valid = true;

            // Check validity (Division by 0, integer stuff, negative ranges for powers and logs etc)
            if ((curr_operator == "divide" || curr_operator == "int_divide" || curr_operator == "modulus" || curr_operator == "log") && second_num == 0) {
                // Division by 0
                event.reply("Invalid Input");
                valid = false;
            } else if (curr_operator == "int_divide" || curr_operator == "modulus" || curr_operator == "factorial") {
                // Integer restrictions
                bool first_int = (abs(first_num - (int)(first_num)) <= 0.000000001);
                bool second_int = (abs(second_num - (int)(second_num)) <= 0.000000001);

                if (!first_int || !second_int) {
                    event.reply("Invalid Input");
                    valid = false;
                }
            } else if (curr_operator == "power") {
                // Negative ranges for powers
                bool second_int = (abs(second_num - (int)(second_num)) <= 0.000000001);

                if (first_num < 0 && !second_int) {
                    event.reply("Invalid Input");
                    valid = false;
                }
            } else if (curr_operator == "log") {
                // Negative ranges for logs and base 1 ranges (Base is first_num)
                if (first_num < 0 || second_num < 0 || first_num == 1) {
                    event.reply("Invalid Input");
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

                // Remove trailing zeroes
                std::string ans_str = std::to_string(ans);
                ans_str.erase(ans_str.find_last_not_of('0') + 1, std::string::npos);
                ans_str.erase(ans_str.find_last_not_of('.') + 1, std::string::npos);
                
                if (ans_str[ans_str.length() - 1] == '.') { ans_str.erase(ans_str.begin() + ans_str.length() - 1); } // Convert 123. to 123

                event.reply(ans_str);
            }
        }

        // ======== TO DO LIST ======== //

        // ======== FORMAT TEXT ======== // (Subscripts, Superscripts, Greek symbols, Math symbols, just made for copy and pasting ease, could be considered a mini text parser)

        // ======== JAPANESE SUPPORT ======== //

        // ======== EMOJI KITCHEN ======= // (When I'm on my computer for example, I want to access Emoji Kitchen too)

        // ======== Shun4MIDI ======== //
    });

    // ========= LISTENING ======== //
    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        // Carry on only if it's not from the bot itself
        // Read usernames
        std::string bot_username_path = (std::filesystem::path(__FILE__).parent_path().parent_path().parent_path()/"bot_username.txt").string();;
        std::ifstream bot_username_file(bot_username_path);
        std::string BOT_USERNAME;
        getline(bot_username_file, BOT_USERNAME);
        bot_username_file.close();

        if (event.msg.author.format_username() != BOT_USERNAME) {
            std::string message = event.msg.content;

            // ======== Shun4miBotSays (My function only) ======= //
            if (message.find("/bot_say") == 0 && event.msg.author.username == "shun4midx") { // Begins with /spin
                std::string command = "/bot_say";
                std::string quote = message.substr(command.length() + 1, message.length() - command.length());
                bot.message_delete(event.msg.id, event.msg.channel_id);
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
                event.reply(list);
            }

            // ======== Shun4mi ======== //
            std::transform(message.begin(), message.end(), message.begin(), ::tolower);
            if (message.find("shun4mi") != std::string::npos || message.find("shunami") != std::string::npos || message.find("tsunami") != std::string::npos || message.find("tsun4mi") != std::string::npos) {
                event.reply("I love Shun4mis! :ocean::ocean:", true);
            }
        }
    });

    // ======== INIT PART OF THE CODE ======== //
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            // ======= SHUN TRIVIA ======== //
            bot.global_command_create(dpp::slashcommand("shun_names", "Outputs all forms of Shun's names", bot.me.id));
            bot.global_command_create(dpp::slashcommand("shun_projects", "Outputs all forms of Shun's current projects", bot.me.id));

            // ======== Shun4miBot QUIRKS ======= //
            bot.global_command_create(dpp::slashcommand("best_programming_language", "What is the best programming language?", bot.me.id));
            bot.global_command_create(dpp::slashcommand("is_cpp_good", "Is C++ good?", bot.me.id));
            bot.global_command_create(dpp::slashcommand("is_shun_good", "Is Shun good?", bot.me.id));
            bot.global_command_create(dpp::slashcommand("do_i_speak_japanese", "Do I speak Japanese?", bot.me.id));
            bot.global_command_create(dpp::slashcommand("do_i_speak_mandarin", "Do I speak Mandarin?", bot.me.id));

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

            // // ======== SHUFFLE ======== //
            bot.global_command_create(dpp::slashcommand("shuffle", "Shuffles amongst choices separated by a space bar", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list", "List to shuffle", true)));
            bot.global_command_create(dpp::slashcommand("shuffle_alt", "Shuffles amongst choices separated by a | symbol", bot.me.id).add_option(dpp::command_option(dpp::co_string, "list", "List to shuffle", true)));
            bot.global_command_create(dpp::slashcommand("shuffle_separator", "Shuffles amongst choices separated by a specified separator that is one character long", bot.me.id).add_option(dpp::command_option(dpp::co_string, "separator", "Separator between each choice", true)).add_option(dpp::command_option(dpp::co_string, "list", "List to shuffle", true)));

            // // ======== KAOMOJIS ======== // (Outputs multiple kaomojis to copy and paste from depending on a certain mood)
            bot.global_command_create(dpp::slashcommand("kaomoji_list", "Lists out a bunch of kaomojis depending on the mood chosen by the user", bot.me.id).add_option(dpp::command_option(dpp::co_string, "mood", "Mood of kaomojis to list", true).set_auto_complete(true)));

            // ======== MATH ======== // (Include some theorems when needed later in the future)
            bot.global_command_create(dpp::slashcommand("add", "Adds two numbers together", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number to add", true)).add_option(dpp::command_option(dpp::co_string, "second_number", "Second number to add", true)));
            bot.global_command_create(dpp::slashcommand("subtract", "Subtracts two numbers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number in the subtraction equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second number in the subtraction equation", true))));
            bot.global_command_create(dpp::slashcommand("minus", "Subtracts two numbers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number in the subtraction equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second number in the subtraction equation", true))));
            bot.global_command_create(dpp::slashcommand("multiply", "Multiplies two numbers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number in the multiplication equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second number in the multiplication equation", true))));
            bot.global_command_create(dpp::slashcommand("divide", "Divides two numbers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First number in the division equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second number in the division equation", true))));
            bot.global_command_create(dpp::slashcommand("int_divide", "Integer divides two integers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First integer in the integer division equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second integer in the integer division equation", true))));
            bot.global_command_create(dpp::slashcommand("modulus", "Finds the modulus of two integers", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "First integer in the integer modulus equation", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Second integer in the integer modulus equation", true))));
            bot.global_command_create(dpp::slashcommand("power", "Finds the power of one number to the other number", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "Base of the expression", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Exponent of the expression", true))));
            bot.global_command_create(dpp::slashcommand("factorial", "Finds the factorial of an integer", bot.me.id).add_option(dpp::command_option(dpp::co_string, "number", "Number to be factorial'ed", true)));
            bot.global_command_create(dpp::slashcommand("log", "Finds the log base one number to the other number", bot.me.id).add_option(dpp::command_option(dpp::co_string, "first_number", "Base of the expression", true)).add_option(dpp::command_option(dpp::command_option(dpp::co_string, "second_number", "Ohter number of the expression", true))));

            // ======== TO DO LIST ======== //

            // ======== FORMAT TEXT ======== // (Subscripts, Superscripts, Greek symbols, Math symbols, just made for copy and pasting ease, could be considered a mini text parser)

            // ======== JAPANESE SUPPORT ======== // (Mainly like converting words I know from English to Japanese but of course it could be romaji to kanji)

            // ======== Shun4MIDI ======== //
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