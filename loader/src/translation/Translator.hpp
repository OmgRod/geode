#pragma once

#include <string>
#include <unordered_map>

class Translator {
private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> translations;
    std::string currentLang;

    void loadTranslations();

public:
    Translator();

    std::string getTranslation(const std::string& translationKey) const;
};
