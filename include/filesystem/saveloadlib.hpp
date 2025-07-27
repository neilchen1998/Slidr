#ifndef INCLUDE_FILESYSTEM_SAVELOADLIB_H_
#define INCLUDE_FILESYSTEM_SAVELOADLIB_H_

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace fs
{
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
        json root_data;

    // 2. Add the "game_name" field
    root_data["game_name"] = "My Awesome Chess Game";

    // 3. Create a JSON array for "entries"
    json entries_array = json::array();

    // 4. Create and add multiple entry objects to the array
    // Example 1
    json entry1;
    entry1["name"] = "Alice";
    entry1["date"] = getCurrentEpochTimestamp(); // Current time in milliseconds
    entry1["moves"] = 42;
    entries_array.push_back(entry1);

    // Example 2 (simulating a different time and moves)
    // You might get slightly different timestamps if run quickly
    // For demonstration, let's manually adjust the time for distinct entries
    json entry2;
    entry2["name"] = "Bob";
    entry2["date"] = getCurrentEpochTimestamp() - 10000; // 10 seconds ago
    entry2["moves"] = 55;
    entries_array.push_back(entry2);

    // Example 3
    json entry3;
    entry3["name"] = "Charlie";
    entry3["date"] = getCurrentEpochTimestamp() - 20000; // 20 seconds ago
    entry3["moves"] = 30;
    entries_array.push_back(entry3);

    // 5. Add the "entries" array to the root object
    root_data["entries"] = entries_array;

    // 6. Write the JSON object to a file
    std::string filename = "game_data_with_entries.json";
    std::ofstream output_file(filename);

    if (output_file.is_open()) {
        // Use dump(4) for pretty-printing with 4 spaces indentation
        output_file << root_data.dump(4) << std::endl;
        output_file.close();
        std::cout << "Successfully created and wrote JSON to '" << filename << "':\n";
        std::cout << root_data.dump(4) << std::endl;
    } else {
        std::cerr << "Error: Could not open file '" << filename << "' for writing." << std::endl;
        return 1; // Indicate an error
    }

    // Optional: Read the file back to verify and demonstrate access
    std::cout << "\nAttempting to read back from '" << filename << "' for verification...\n";
    std::ifstream input_file(filename);
    if (input_file.is_open()) {
        try {
            json read_data;
            input_file >> read_data;
            std::cout << "Successfully read:\n" << read_data.dump(4) << std::endl;

            // Accessing root field
            std::cout << "\nGame Name: " << read_data["game_name"] << std::endl;

            // Accessing array elements
            std::cout << "\nEntries:\n";
            if (read_data.contains("entries") && read_data["entries"].is_array()) {
                for (const auto& entry : read_data["entries"]) {
                    std::cout << "  Name: " << entry["name"] << ", ";
                    std::cout << "Date (Epoch ms): " << entry["date"] << ", ";
                    std::cout << "Moves: " << entry["moves"] << std::endl;

                    // Convert epoch milliseconds back to human-readable for display
                    long long epoch_ms = entry["date"].get<long long>();
                    std::time_t t = static_cast<std::time_t>(epoch_ms / 1000); // Convert ms to seconds
                    std::tm* local_tm = std::localtime(&t);
                    std::ostringstream oss;
                    oss << std::put_time(local_tm, "%Y-%m-%d %H:%M:%S");
                    std::cout << "  Date (Human-readable): " << oss.str() << std::endl;
                }
            }

        } catch (const json::parse_error& e) {
            std::cerr << "JSON parse error when reading: " << e.what() << std::endl;
            return 1;
        } catch (const json::type_error& e) {
            std::cerr << "JSON type error when accessing data: " << e.what() << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Error: Could not open file '" << filename << "' for reading." << std::endl;
        return 1;
    }

    return 0; // Indicate success
    }
}   // namespace fs

#endif // INCLUDE_FILESYSTEM_SAVELOADLIB_H_
