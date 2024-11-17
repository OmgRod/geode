#include "Translator.hpp"
#include <Geode/Geode.hpp> // For Mod::get()->getSettingValue

using namespace geode::prelude;

Translator::Translator() {
    // Default to English if no language is specified
    currentLang = "en-us";
    loadTranslations();
}

void Translator::setLanguage(int64_t languageSetting) {
    switch (languageSetting) {
        case 0:
            currentLang = "en-us";  // English
            break;
        case 1:
            currentLang = "pt-pt";  // Portuguese
            break;
        default:
            currentLang = "en-us";  // Default to English if an unrecognized setting is passed
            break;
    }

    loadTranslations();  // Load translations after changing language
}

void Translator::loadTranslations() {
    // Populate the translations table for English and Portuguese
    translations = {
        {"en-us", {
            {"geode.mods.installedTab", "Installed"},
            {"geode.mods.featuredTab", "Featured"},
            {"geode.mods.downloadTab", "Download"},
            {"geode.mods.recentTab", "Recent"},
            {"geode.mods.modtoberTab", "Modtober"}
        }},
        {"pt-pt", {
            {"geode.mods.installedTab", "Instalados"},
            {"geode.mods.featuredTab", "Destaques"},
            {"geode.mods.downloadTab", "Transferir"},
            {"geode.mods.recentTab", "Recentes"},
            {"geode.mods.modtoberTab", "Modtober"}
        }}
    };
}

std::string Translator::getTranslation(const std::string& translationKey) const {
    auto langIt = translations.find(currentLang);  // Find the correct language
    if (langIt != translations.end()) {
        const auto& langTranslations = langIt->second;
        auto keyIt = langTranslations.find(translationKey);
        if (keyIt != langTranslations.end()) {
            return keyIt->second;  // Return the translation if found
        }
    }

    return "[Missing translation: " + translationKey + "]";  // Return a placeholder if the key isn't found
}
