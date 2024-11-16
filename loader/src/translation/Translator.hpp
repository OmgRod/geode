#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <string>
#include <unordered_map>
#include <matjson.hpp>

class Translator {
public:
    // Constructor that initializes the language and loads translations
    Translator(int64_t languageSetting);

    // Retrieves the translation for a given key
    std::string getTranslation(const std::string& translationKey) const;

private:
    std::string currentLang;  // Current language (e.g., "en-us", "pt-pt")
    std::unordered_map<std::string, std::string> translations;  // Map of translation keys and their values

    // Loads translations from the JSON file
    void loadTranslations();
};

#endif // TRANSLATOR_HPP
