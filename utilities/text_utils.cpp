#include "text_utils.h"

#include <sstream>

char TextUtils::to_lowercase(char c) { return std::tolower(c); }

std::vector<std::string> TextUtils::get_words_from_text(
    const std::string &text) {
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string word;
    while (std::getline(iss, word, ' ')) {
        words.push_back(word);
    }
    return words;
}
