#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <string>
#include <unordered_map>

class Translator {
private:
    std::string currentLang;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> translations;

    void loadTranslations();

public:
    Translator();
    void setLanguage(int64_t languageSetting);
    std::string getTranslation(const std::string& translationKey) const;
};

#endif