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

void Translator::loadTranslations() {
    std::filesystem::path path = Mod::get()->getResourcesDir() / "translation" / currentLang / "translations.json";

    std::ifstream file(path);
    if (!file.is_open()) {
        log::error("Failed to open translation file: {}", path);
        return;
    }

    std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    auto result = matjson::parse(fileContents);
    if (!result) {
        log::error("Failed to parse JSON: {}", result.unwrapErr());
        return;
    }

    matjson::Value translationsObject = result.unwrap();

    if (translationsObject.isObject()) {
        for (auto& pair : translationsObject) {
            // Extract key and value directly from the pair
            std::string key;
            if (pair.first.isString()) {
                key = pair.first.asString().unwrap();
            } else {
                log::error("Invalid key type in JSON.");
                continue;
            }

            std::string value;
            if (pair.second.isString()) {
                value = pair.second.asString().unwrap();
            } else {
                log::error("Invalid value type for key {} in JSON.", key);
                continue;
            }

            translations[key] = value;
        }
    } else {
        log::error("Parsed JSON is not an object.");
    }
}
