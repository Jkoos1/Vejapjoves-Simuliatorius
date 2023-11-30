#ifndef TRANSLATION_UTILS_H
#define TRANSLATION_UTILS_H

#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>

class TranslationUtils {
public:
    TranslationUtils(const std::string& filename);
    std::string getTranslation(const std::string& key, const std::string& language);

private:
    nlohmann::json translations;
};

#endif
