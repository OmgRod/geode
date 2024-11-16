#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <string>
#include <map>
#include <filesystem>
#include <matjson.hpp>

class Translator {
public:
    // Constructor that takes a language setting (0 for en-us, 1 for pt-pt)
    Translator(int64_t languageSetting);

    // Get the translated text for a given key
    std::string getTranslation(const std::string& translationKey) const;

    // Load translations from the JSON file
    void loadTranslations();

    // Save translations to a saved file
    void saveTranslations();

private:
    // Current language setting (e.g., "en-us", "pt-pt")
    std::string currentLang;

    // Map to hold translations (key = translation key, value = translation string)
    std::map<std::string, std::string> translations;
};

#endif // TRANSLATOR_HPP
