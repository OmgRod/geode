// Translator.hpp
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <string>
#include <unordered_map>

class Translator {
public:
    Translator();

    // Set the language based on a setting
    void setLanguage(int64_t languageSetting);

    // Get the translation for a specific key
    std::string getTranslation(const std::string& translationKey) const;

private:
    // Current language (en-us or pt-pt)
    std::string currentLang;

    // The map of translations for different languages
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> translations;

    // Load translations for all supported languages
    void loadTranslations();
};

#endif // TRANSLATOR_HPP
