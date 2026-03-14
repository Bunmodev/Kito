#include <kito/utils/parser/kitoParser.h>


namespace kito {

    std::string KMLParser::loadKML(const std::string& filename) {
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error opening KML file: " << filename << std::endl;
                return "";
            }
            std::string kml((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            return kml;
        } catch (const std::exception& e) {
            std::cerr << "Error loading KML: " << e.what() << std::endl;
            return "";
        }
    }

     std::vector<std::unique_ptr<ui::Widget>> KMLParser::parseKML(const std::string& filename) {
        // 1. Load the raw text
        std::string source = loadKML(filename);
        if (source.empty()) return {};

        // 2. Tokenize (Modular call to Lexer)
        Lexer lexer;
        std::vector<Token> tokens = lexer.lex(source);

        // 3. Parse (The Recursive Descent starting point)
        int index = 0;
        auto element = parseElement(tokens, index);
        std::vector<std::unique_ptr<ui::Widget>> result;
        if (element) {
            result.push_back(std::move(element));
        }
        return result;
    }

    std::unique_ptr<kito::ui::Widget> KMLParser::parseElement(std::vector<Token>& tokens, int& index) {
        if (index >= tokens.size() || tokens[index].type == TokenType::EOF_TYPE) return nullptr;

        // 1. Consume Opening Bracket '<'
        if (tokens[index].type != TokenType::TAG_OPEN) return nullptr;
        index++; 

        // 2. Get Widget Type (e.g., "panel")
        if (tokens[index].type != TokenType::IDENTIFIER) return nullptr;
        std::string widgetType = tokens[index].lexeme;
        index++;

        // 3. Collect Attributes (Pairs of Key/Value)
        std::vector<std::pair<std::string, std::string>> attributes;
        while (index < tokens.size() && tokens[index].type == TokenType::IDENTIFIER) {
            std::string key = tokens[index].lexeme;
            index++;

            if (tokens[index].type == TokenType::EQUALS) {
                index++; // Consume '='
                if (tokens[index].type == TokenType::STRING) {
                    attributes.push_back({key, tokens[index].lexeme});
                    index++; // Consume "value"
                }
            }
        }

        // 4. Create the Widget via Factory
        // (This uses the refactored factory we built earlier)
        auto widget = ui_factory::createKMLWidget(widgetType, attributes);

        // 5. Handle Closing of Opening Tag ('>' or '/>')
        if (tokens[index].type == TokenType::SLASH) {
            index += 2; // Consume '/>'
            return widget; // Self-closing tag, no children possible
        }
        
        if (tokens[index].type == TokenType::TAG_CLOSE) {
            index++; // Consume '>'
        }

        // 6. RECURSIVE CHILD PARSING
        // Keep parsing as long as we don't see "</"
        while (index < tokens.size()) {
            // Peek for </
            if (tokens[index].type == TokenType::TAG_OPEN && 
                index + 1 < tokens.size() && 
                tokens[index + 1].type == TokenType::SLASH) {
                break; 
            }

            // It's a child element!
            auto child = parseElement(tokens, index);
            if (child && widget) {
                widget->addChild(std::move(child));
            } else {
                break; 
            }
        }

        // 7. Consume the Closing Tag (e.g., </panel>)
        if (index + 3 < tokens.size() && 
            tokens[index].type == TokenType::TAG_OPEN && 
            tokens[index + 1].type == TokenType::SLASH) {
            
            index += 4; // Consumes '<', '/', 'IDENTIFIER', '>'
        }

        return widget;
    }

    
}
    