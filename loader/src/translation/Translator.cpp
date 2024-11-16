#include "Translator.hpp"
#include <iostream>
#include <Geode/Geode.hpp>
#include <Geode/loader/Mod.hpp>
#include <matjson.hpp>
#include <fstream>
#include <filesystem>

using namespace geode::prelude;

Translator::Translator(int64_t languageSetting) {
    // Determine the current language based on the setting value
    if (languageSetting == 0) {
        currentLang = "en-us";
    } else if (languageSetting == 1) {
        currentLang = "pt-pt";
    } else {
        currentLang = "en-us";  // Default to en-us if the setting is invalid
    }

    // Load translations based on the current language
    loadTranslations();
}

std::string Translator::getTranslation(const std::string& translationKey) const {
    auto it = translations.find(translationKey);
    if (it != translations.end()) {
        return it->second;
    }
    return "Translation not found";  // Return a default message if the key is not found
}

void Translator::loadTranslations() {
    // Build the path to the translations file
    std::filesystem::path path = Mod::get()->getResourcesDir() / "translation" / currentLang / "translations.json";

    // Open the file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open translation file: " << path << std::endl;
        return;
    }

    // Parse the JSON file using matjson
    auto result = matjson::parse(file);
    if (!result) {
        std::cerr << "Failed to parse JSON: " << result.unwrapErr() << std::endl;
        return;
    }

    matjson::Value translationsObject = result.unwrap();

    // Ensure we are working with an object
    if (!translationsObject.isObject()) {
        std::cerr << "Parsed JSON is not an object." << std::endl;
        return;
    }

    // Populate the translations map with key-value pairs from the JSON object
    for (auto& pair : translationsObject) {
        // Extract the key (should be a string)
        auto keyResult = pair.first.asString();
        if (!keyResult) {
            std::cerr << "Failed to extract key from JSON: " << pair.first.dump() << std::endl;
            continue;
        }
        std::string key = keyResult.unwrap();

        // Extract the value (should be a string)
        auto valueResult = pair.second.asString();
        if (!valueResult) {
            std::cerr << "Failed to extract value for key " << key << std::endl;
            continue;
        }
        std::string value = valueResult.unwrap();

        // Store the translation in the map
        translations[key] = value;
    }
}
