#include "Translator.hpp"
#include <stdexcept>
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

std::string Translator::getLang() const {
    return currentLang;
}

std::string Translator::getTranslation(const std::string& translationKey) const {
    auto it = translations.find(translationKey);
    if (it != translations.end()) {
        return it->second;
    }
    return "Translation not found";  // Return a default message if the key is not found
}

void Translator::addTranslation(const std::string& key, const std::string& translation) {
    translations[key] = translation;
}

void Translator::loadTranslations() {
    // Build the path to the translations file
    std::string path = Mod::get()->getResourcesDir() + "/translation/" + currentLang + ".json";

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
