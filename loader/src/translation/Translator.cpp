#include "Translator.hpp"

Translator::Translator(int64_t languageSetting) {
    // Map language setting to language code
    switch (languageSetting) {
        case 0:
            currentLang = "en-us";
            break;
        case 1:
            currentLang = "pt-pt";
            break;
        default:
            currentLang = "en-us";
            break;
    }

    loadTranslations();
}

void Translator::loadTranslations() {
    // Populate the translations table
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
    auto langIt = translations.find(currentLang);
    if (langIt != translations.end()) {
        const auto& langTranslations = langIt->second;
        auto keyIt = langTranslations.find(translationKey);
        if (keyIt != langTranslations.end()) {
            return keyIt->second;
        }
    }

    return "[Missing translation: " + translationKey + "]";
}
