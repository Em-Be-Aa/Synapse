#include "SynapseFunctionLibrary.h"
#include <fstream>
#include <iostream>

nlohmann::json SynapseFunctionLibrary::loadJson()
{
    // Consider passing the path as a parameter eventually, e.g., loadJson(const std::string& filepath)
    std::string filepath = "E:/Learning/Synapse/Synapse/source/GameConfig/gameconfig.json";
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "ENGINE ERROR: Failed to open file at path: " << filepath << "\n";
        std::cerr << "Check your IDE's Working Directory settings!\n";
        return nlohmann::json({}); // Return an empty JSON object
    }

    nlohmann::json config;

    try {
        file >> config;
    }
    catch (const nlohmann::json::parse_error& e) {
        // Catches syntax errors (missing commas, brackets) in the JSON file
        std::cerr << "JSON PARSE ERROR in " << filepath << ":\n" << e.what() << "\n";
        return nlohmann::json({});
    }

    // file.close() is automatically called when 'file' goes out of scope, 
    // so you don't actually need to write it manually.

    return config;
}
