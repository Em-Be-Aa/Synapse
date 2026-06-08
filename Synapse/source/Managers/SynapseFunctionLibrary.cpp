#include "SynapseFunctionLibrary.h"
#include <fstream>
#include <iostream>

nlohmann::json SynapseFunctionLibrary::loadJson()
{
    // Try multiple candidate paths relative to the working directory.
    // It's common for the working directory to be the project root or the build/exe folder,
    // so we try a few likely locations and the old absolute path for convenience.
    std::vector<std::string> candidates = {
        "source/GameConfig/config.json",
        "source/GameConfig/gameconfig.json",
        "Synapse/source/GameConfig/config.json",
        "Synapse/source/GameConfig/gameconfig.json",
        "GameConfig/config.json",
        "E:/Learning/Synapse/Synapse/source/GameConfig/gameconfig.json"
    };

    nlohmann::json config;
    for (const auto &filepath : candidates)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
            continue;

        try {
            file >> config;
            return config;
        }
        catch (const nlohmann::json::parse_error& e) {
            std::cerr << "JSON PARSE ERROR in " << filepath << ":\n" << e.what() << "\n";
            return nlohmann::json({});
        }
    }

    // If we reach here, none of the candidate files could be opened
    std::cerr << "ENGINE ERROR: Failed to open config file. Tried paths:\n";
    for (const auto &p : candidates) std::cerr << "  " << p << "\n";
    std::cerr << "Check your IDE's Working Directory or place config.json in one of the above locations.\n";
    return nlohmann::json({});
}
