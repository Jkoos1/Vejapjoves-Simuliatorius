#include "TranslationUtils.h"

TranslationUtils::TranslationUtils(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open translation file: " << filename << std::endl;
        return;
    }
    file >> translations;
}

std::string TranslationUtils::getTranslation(const std::string& key, const std::string& language) {
    try {
        return translations.at(language).at(key);
    }
    catch (std::exception& e) {
        std::cerr << "Translation error: " << e.what() << std::endl;
        return key;
    }
}
