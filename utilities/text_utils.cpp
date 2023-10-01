#include "text_utils.h"

#include <sstream>

char TextUtils::to_lowercase(char c) {
    return std::tolower(static_cast<unsigned char>(c));
}

std::string TextUtils::shorten_word(const std::string &str) {
    if (str.size() > 1) {
        return std::string(1, str[0]);
    }
    return str;
}

std::string TextUtils::shorten_text(const std::string &text) {
    std::istringstream iss(text);
    std::string word;
    std::string result;

    while (iss >> word) {
        std::string cleanedWord;
        for (char c : word) {
            if (std::isalpha(c)) {
                cleanedWord += c;
            }
        }
        result += shorten_word(cleanedWord);
    }
    return result;
}

std::vector<std::string> TextUtils::get_words_from_text(
    const std::string &text) {
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string word;
    while (std::getline(iss, word, ' ')) {  // ' ' is the delimiter
        words.push_back(word);
    }
    return words;
}
