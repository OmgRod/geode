#include "Translator.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

Translator::Translator() {
    currentLang = "en-us";
    loadTranslations();
}

void Translator::setLanguage(int64_t languageSetting) {
    switch (languageSetting) {
        case 0:
            currentLang = "en-us";
            log::debug("Language set to English (en-us)");
            break;
        case 1:
            currentLang = "pt-pt";
            log::debug("Language set to Portuguese (pt-pt)");
            break;
        default:
            currentLang = "en-us";
            log::debug("Language set to default English (en-us)");
            break;
    }

    loadTranslations();
}

void Translator::loadTranslations() {
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

    // Log translations to verify
    log::debug("Translations loaded for language: {}", currentLang);
    for (const auto& [key, value] : translations[currentLang]) {
        log::debug("Loaded translation: {} -> {}", key, value);
    }
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
