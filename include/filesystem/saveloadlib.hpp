#ifndef INCLUDE_FILESYSTEM_SAVELOADLIB_H_
#define INCLUDE_FILESYSTEM_SAVELOADLIB_H_

#include <iostream>     // std::cout, std::cerr
#include <chrono>       // std::chrono::system_clock::now
#include <fstream>      // std::ofstream
#include <string>       // std::string
#include <string_view>  // std::string_view
#include <filesystem>   // std::filesystem::create_directories

#include <fmt/core.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace fs
{
    constexpr std::string_view JSON_FILE_PATH {"./leaderboard/game_data_with_entries.json"};

    // JSON property names
    constexpr std::string_view GAME_NAME_JSON_PROPERTY_NAME {"game_name"};
    constexpr std::string_view GAME_CATEGORY_JSON_PROPERTY_NAME {"best_move_category"};
    constexpr std::string_view PLAYER_NAME_JSON_PROPERTY_NAME {"name"};
    constexpr std::string_view DATE_JSON_PROPERTY_NAME {"date"};
    constexpr std::string_view MOVE_JSON_PROPERTY_NAME {"moves"};

    long long getCurrentEpochTimestamp()
    {
        // Get the current time point
        auto now = std::chrono::system_clock::now();

        // Convert to duration since epoch
        auto duration = now.time_since_epoch();

        // Convert duration to seconds
        return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }

    int demo()
    {
        // Create a directory
        std::filesystem::create_directories("./leaderboard");

        // Create the main json file
        json root_data;

        root_data[GAME_NAME_JSON_PROPERTY_NAME] = "8 Puzzle";

        // Create an array to store players' moves
        json entries = json::array();

        json entry1;
        entry1[PLAYER_NAME_JSON_PROPERTY_NAME] = "Alice";
        entry1[DATE_JSON_PROPERTY_NAME] = getCurrentEpochTimestamp();
        entry1[MOVE_JSON_PROPERTY_NAME] = 42;
        entries.push_back(entry1);

        json entry2;
        entry2[PLAYER_NAME_JSON_PROPERTY_NAME] = "Bob";
        entry2[DATE_JSON_PROPERTY_NAME] = getCurrentEpochTimestamp() - 10000;
        entry2[MOVE_JSON_PROPERTY_NAME] = 55;
        entries.push_back(entry2);

        json entry3;
        entry3[PLAYER_NAME_JSON_PROPERTY_NAME] = "Charlie";
        entry3[DATE_JSON_PROPERTY_NAME] = getCurrentEpochTimestamp() - 20000;
        entry3[MOVE_JSON_PROPERTY_NAME] = 30;
        entries.push_back(entry3);

        // Push the entries to the best move category
        root_data[GAME_CATEGORY_JSON_PROPERTY_NAME] = entries;

        // Write the data
        std::ofstream output_file(JSON_FILE_PATH.data());

        if (output_file.is_open())
        {
            // Use dump(4) for pretty-printing with 4 spaces indentation
            output_file << root_data.dump(4) << std::endl;
            output_file.close();
            std::cout << root_data.dump(4) << std::endl;
        }
        else
        {
            std::cerr << "Error: Could not open file '" << JSON_FILE_PATH << "' for writing." << std::endl;
            return 1;
        }

        // Optional: Read the file back to verify and demonstrate access
        std::cout << "\nAttempting to read back from '" << JSON_FILE_PATH << "' for verification...\n";
        std::ifstream input_file(JSON_FILE_PATH.data());
        if (input_file.is_open())
        {
            try
            {
                json read_data;
                input_file >> read_data;
                std::cout << "Successfully read:\n" << read_data.dump(4) << std::endl;

                // Accessing root field
                std::cout << "\nGame Name: " << read_data[GAME_NAME_JSON_PROPERTY_NAME] << std::endl;

                // Accessing array elements
                std::cout << "\nEntries:\n";
                if (read_data.contains(GAME_CATEGORY_JSON_PROPERTY_NAME) && read_data[GAME_CATEGORY_JSON_PROPERTY_NAME].is_array())
                {
                    for (const auto& entry : read_data[GAME_CATEGORY_JSON_PROPERTY_NAME])
                    {
                        fmt::println(". Name: {}, Date: {}, Moves: {}", entry[PLAYER_NAME_JSON_PROPERTY_NAME].get<std::string>(), entry[DATE_JSON_PROPERTY_NAME].get<long long>(), entry[MOVE_JSON_PROPERTY_NAME].get<int>());
                    }
                }

            }
            catch (const json::parse_error& e)
            {
                std::cerr << "JSON parse error when reading: " << e.what() << std::endl;
                return 1;
            }
            catch (const json::type_error& e)
            {
                std::cerr << "JSON type error when accessing data: " << e.what() << std::endl;
                return 1;
            }
        }
        else
        {
            std::cerr << "Error: Could not open file '" << JSON_FILE_PATH << "' for reading." << std::endl;
            return 1;
        }

        return 0;
    }
}   // namespace fs

#endif // INCLUDE_FILESYSTEM_SAVELOADLIB_H_
