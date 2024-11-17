#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <string>
#include <unordered_map>

class Translator {
private:
    std::string currentLang; // Holds the current language code
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> translations;

    void loadTranslations(); // Loads translations into the map

public:
    Translator(); // Default constructor
    void setLanguage(int64_t languageSetting); // Setter to change the language dynamically
    std::string getTranslation(const std::string& translationKey) const;
};

#endif // TRANSLATOR_HPP
