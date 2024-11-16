#include "Translator.hpp"
#include <iostream>
#include <Geode/Geode.hpp>
#include <Geode/loader/Mod.hpp>
#include <matjson.hpp>
#include <fstream>
#include <filesystem>

using namespace geode::prelude;

Translator::Translator(int64_t languageSetting) {
    if (languageSetting == 0) {
        currentLang = "en-us";
    } else if (languageSetting == 1) {
        currentLang = "pt-pt";
    } else {
        currentLang = "en-us";
    }

    loadTranslations();
}

std::string Translator::getTranslation(const std::string& translationKey) const {
    auto it = translations.find(translationKey);
    if (it != translations.end()) {
        return it->second;
    }
    return "Translation not found";
}

Result<void, std::string> Translator::loadTranslations() {
    std::filesystem::path path = Mod::get()->getResourcesDir() / "translation" / currentLang / "translations.json";

    std::ifstream file(path);
    if (!file.is_open()) {
        return Err("Failed to open translation file: " + path.string());
    }

    std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    auto result = matjson::parse(fileContents);
    if (!result) {
        return Err("Failed to parse JSON: " + result.unwrapErr());
    }

    matjson::Value translationsObject = result.unwrap();

    // Check if the parsed JSON is an object
    if (!translationsObject.isObject()) {
        return Err("Parsed JSON is not an object, got: " + jsonTypeToString(translationsObject.type()));
    }

    // Iterate manually over key-value pairs
    for (auto& keyValuePair : translationsObject.asObject()) {
        if (keyValuePair.first.isString()) {
            std::string key = keyValuePair.first.asString().unwrap();
            if (keyValuePair.second.isString()) {
                std::string value = keyValuePair.second.asString().unwrap();
                translations[key] = value;
            } else {
                return Err("Value for key \"" + key + "\" is not a string.");
            }
        } else {
            return Err("Key in JSON is not a string.");
        }
    }

    return Ok();
}
