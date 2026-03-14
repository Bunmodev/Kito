#pragma once

#include <vector>
#include <string>

namespace kito {

    enum class TokenType {
        TAG_OPEN,    // <
        TAG_CLOSE,   // >
        SLASH,       // /
        EQUALS,      // =
        IDENTIFIER,  // panel, button, id, margin
        STRING,      // "my_id"
        EOF_TYPE
    };

    struct Token {
        TokenType type;
        std::string lexeme;
    };

    class Lexer {
    public:
        // Changed from std::string to Token objects
        static std::vector<Token> lex(const std::string& str);
    };
}