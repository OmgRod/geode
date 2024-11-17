#include "Translator.hpp"
#include "Geode/utils/JsonValidation.hpp" // JSON validation utilities

// Constructor that sets the current language
Translator::Translator(int64_t languageSetting) {
    // Map language setting to language code (example: 0 = "en", 1 = "fr")
    switch (languageSetting) {
        case 0:
            currentLang = "en";
            break;
        case 1:
            currentLang = "fr";
            break;
        default:
            currentLang = "en"; // Default to English
            break;
    }

    // Load translations for the selected language
    auto result = loadTranslations();
    if (!result) {
        // Handle errors during loading, log or handle appropriately
        throw std::runtime_error("Failed to load translations: " + result.unwrapErr());
    }
}

// Load translations from a JSON file or another source
Result<void, std::string> Translator::loadTranslations() {
    std::string fileName = "translations_" + currentLang + ".json";

    auto result = matjson::parseFromFile(fileName);
    if (!result) {
        return Err(std::string("Failed to parse JSON: ") + result.unwrapErr().toString());
    }

    auto& translationsObject = result.unwrap();
    if (!translationsObject.isObject()) {
        return Err(std::string("Parsed JSON is not an object, got: ") +
                   jsonValueTypeToString(translationsObject.type()));
    }

    auto& obj = translationsObject.getObject(); // Assuming `getObject()` provides a map
    for (const auto& keyValuePair : obj) {
        const auto& key = keyValuePair.first;
        const auto& value = keyValuePair.second;

        if (!value.isString()) {
            return Err(std::string("Expected translation for key '") + key +
                       "' to be a string, got: " +
                       jsonValueTypeToString(value.type()));
        }

        translations[key] = value.asString(); // Store the key-value pair
    }

    return Ok();
}

// Fetch a translation by key
std::string Translator::getTranslation(const std::string& translationKey) const {
    auto it = translations.find(translationKey);
    if (it != translations.end()) {
        return it->second; // Return the translation if found
    }

    // Return a placeholder or log missing key
    return "[Missing translation: " + translationKey + "]";
}
