#ifndef ANIMALESE_TEXT_UTILITIES_H
#define ANIMALESE_TEXT_UTILITIES_H

#include <string>

class TextUtils {
   public:
    static char to_lowercase(char c);
    static std::string shorten_word(const std::string &str);
    static std::string shorten_text(const std::string &text);
    static std::vector<std::string> get_words_from_text(
        const std::string &text);
};

#endif  // ANIMALESE_TEXT_UTILITIES_H
