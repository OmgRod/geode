#include "Translator.hpp"
#include <iostream>
#include <Geode/Geode.hpp>
#include <Geode/loader/Mod.hpp>
#include <matjson.hpp>
#include <fstream>

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
    std::filesystem::path path = Mod::get()->getResourcesDir() / "translation" / currentLang / ".json";

    // Open the file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open translation file: " << path << std::endl;
        return;
    }

    // Parse the JSON file
    auto result = matjson::parse(file);
    if (!result) {
        std::cerr << "Failed to parse JSON: " << result.unwrapErr() << std::endl;
        return;
    }

    matjson::Value translationsObject = result.unwrap();

    // Populate the translations map with key-value pairs from the JSON object
    for (auto& [key, value] : translationsObject) {
        if (value.isString()) {
            translations[key] = value.asString().unwrap();
        }
    }
}

void Translator::saveTranslations() {
    // Build the path to save the translations file
    std::filesystem::path path = Mod::get()->getSaveDir() / "translations.json";

    // Create a matjson object to represent the translations
    matjson::Object translationsObject;
    for (const auto& [key, value] : translations) {
        translationsObject[key] = value;
    }

    // Open the file to save
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open translation file for saving: " << path << std::endl;
        return;
    }

    // Serialize and write the translations object to file
    matjson::write(file, translationsObject);
    std::cout << "Translations saved to " << path << std::endl;
}

// Example of how to load/save data with `matjson`
template<>
struct matjson::Serialize<std::map<std::string, std::string>> {
    static std::map<std::string, std::string> from_json(matjson::Value const& value) {
        std::map<std::string, std::string> result;
        for (auto& [key, val] : value.asObject()) {
            if (val.isString()) {
                result[key] = val.asString().unwrap();
            }
        }
        return result;
    }

    static matjson::Value to_json(std::map<std::string, std::string> const& value) {
        auto obj = matjson::Object();
        for (const auto& [key, val] : value) {
            obj[key] = val;
        }
        return obj;
    }
};