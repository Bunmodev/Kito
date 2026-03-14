#pragma once 
#include <string>

enum class TokenType {
    TAG_OPEN,    // <
    TAG_CLOSE,   // >
    SLASH,       // /
    EQUALS,      // =
    IDENTIFIER,  // panel, button, color
    STRING,      // "side_bar", "#ff0000"
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme; // The actual text (e.g., "button")
    int line;           // GREAT for showing the professor you handle error reporting!
};