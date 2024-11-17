#pragma once

#include <string>
#include <unordered_map>
#include <Geode/Result.hpp>
#include <matjson.hpp>

class Translator {
private:
    std::unordered_map<std::string, std::string> translations; // Translation key-value pairs
    std::string currentLang; // Current language code (e.g., "en", "fr", etc.)

    Result<void, std::string> loadTranslations(); // Load translations from a file or source

public:
    Translator(int64_t languageSetting); // Constructor for setting the language

    std::string getTranslation(const std::string& translationKey) const; // Fetch a translation
};
