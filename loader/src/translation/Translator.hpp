#pragma once

#include <string>
#include <unordered_map>
#include <matjson.hpp>

class Translator {
private:
    std::unordered_map<std::string, std::string> translations;
    std::string currentLang;

    // Loads translations from the current language's JSON file
    void loadTranslations();

public:
    // Constructor that sets the language based on a language setting value
    Translator(int64_t languageSetting);

    // Retrieves a translation for a given key, or a default message if not found
    std::string getTranslation(const std::string& translationKey) const;
};
