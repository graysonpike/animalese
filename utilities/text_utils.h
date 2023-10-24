#ifndef ANIMALESE_TEXT_UTILITIES_H
#define ANIMALESE_TEXT_UTILITIES_H

#include <string>

class TextUtils {
   public:
    static char to_lowercase(char c);
    // Given a string of text, returns a shortened version where all words are
    // reduced to their first character and non-alphabetical characters are
    // removed.
    static std::string shorten_text(const std::string &text);
    // Given a string of text, returns a list of the individual words from the
    // text, as delimited by the space character.
    static std::vector<std::string> get_words_from_text(
        const std::string &text);
};

#endif  // ANIMALESE_TEXT_UTILITIES_H
