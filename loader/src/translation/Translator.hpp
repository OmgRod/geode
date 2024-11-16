#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <string>
#include <unordered_map>
#include <matjson.hpp>

class Translator {
public:
    // Constructor that initializes the language and loads translations
    Translator(int64_t languageSetting);

    // Gets the current language
    std::string getLang() const;

    // Retrieves the translation for a given key
    std::string getTranslation(const std::string& translationKey) const;

    // Optionally, a function to add new translations dynamically
    void addTranslation(const std::string& key, const std::string& translation);

private:
    std::string currentLang;  // Current language (e.g., "en-us", "pt-pt")
    std::unordered_map<std::string, std::string> translations;  // Map of translation keys and their values

    // Loads translations from the JSON file
    void loadTranslations();
};

#endif // TRANSLATOR_HPP
