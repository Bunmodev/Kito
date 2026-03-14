#include <kito/utils/parser/lexer.h>
#include <cctype>

namespace kito {

std::vector<Token> Lexer::lex(const std::string& str) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < str.length()) {
        char c = str[i];

        if (std::isspace(c)) { i++; continue; }

        if (c == '<') { tokens.push_back({TokenType::TAG_OPEN, "<"}); i++; }
        else if (c == '>') { tokens.push_back({TokenType::TAG_CLOSE, ">"}); i++; }
        else if (c == '/') { tokens.push_back({TokenType::SLASH, "/"}); i++; }
        else if (c == '=') { tokens.push_back({TokenType::EQUALS, "="}); i++; }
        
        // Handle Strings (Attributes like "login_btn")
        else if (c == '"') {
            std::string result;
            i++; // Skip opening quote
            while (i < str.length() && str[i] != '"') {
                result += str[i++];
            }
            i++; // Skip closing quote
            tokens.push_back({TokenType::STRING, result});
        }
        
        // Handle Identifiers (Tags and Attribute names)
        else if (std::isalpha(c)) {
            std::string result;
            while (i < str.length() && (std::isalnum(str[i]) || str[i] == '_' || str[i] == '-')) {
                result += str[i++];
            }
            tokens.push_back({TokenType::IDENTIFIER, result});
        }
        else {
            i++; // Ignore unknown characters
        }
    }

    tokens.push_back({TokenType::EOF_TYPE, ""});
    return tokens;
}

}