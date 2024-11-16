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

    if (!translationsObject.isObject()) {
        log::error("Parsed JSON is not an object.");
        return;
    }

    for (const auto& pair : translationsObject.asObject()) {
        auto keyResult = pair.first.asString();
        if (!keyResult) {
            log::error("Failed to extract key from JSON: {}", pair.first.dump());
            continue;
        }
        std::string key = keyResult.unwrap();

        auto valueResult = pair.second.asString();
        if (!valueResult) {
            log::error("Failed to extract value for key {}", key);
            continue;
        }
        std::string value = valueResult.unwrap();

        translations[key] = value;
    }
}
