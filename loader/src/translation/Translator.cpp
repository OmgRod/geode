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

    // Check if the parsed value is an object
    if (translationsObject.isObject()) {
        // Manually iterate over the object by using .object() to get the key-value map
        auto object = translationsObject.object();
        for (auto it = object.begin(); it != object.end(); ++it) {
            // Extract key as string
            if (it->first.isString()) {
                std::string key = it->first.asString().unwrap();

                // Extract value as string
                if (it->second.isString()) {
                    std::string value = it->second.asString().unwrap();
                    translations[key] = value;
                } else {
                    log::error("Value for key {} is not a string.", key);
                }
            } else {
                log::error("Key in JSON is not a string.");
            }
        }
    } else {
        log::error("Parsed JSON is not an object.");
    }
}
