#include <iostream>
#include <string>
#include <cctype>

class TipoSimbolo {
public:
    static const int ERROR = -1;
    static const int IDENTIFICADOR = 0;
    static const int OPADIC = 1;
    static const int OPMULT = 2;
    static const int PESOS = 3;
    static const int ENTERO = 4;
    static const int REAL = 5;  // Agregado para distinguir números reales
    static const int IGUAL = 6; // Agregado para el símbolo igual
    static const int UNDERSCORE = 7; // Agregado para el guion bajo
    static const int TAB = 8; // Agregado para el tabulador
    static const int PARENTESIS_IZQ = 9; // Agregado para el paréntesis izquierdo
    static const int PARENTESIS_DER = 10; // Agregado para el paréntesis derecho
    static const int ASTERISCO = 11; // Agregado para el asterisco
    static const int SLASH = 12; // Agregado para la barra inclinada (/)
    static const int PIPE = 13; // Agregado para la barra vertical (|)
    static const int DOUBLE_PIPE = 14; // Agregado para la doble barra vertical (||)
    static const int PUNTO = 15; // Agregado para el punto (.)
    static const int MENOS = 16; // Agregado para el símbolo menos (-)
};

// Enumeración para los tipos de tokens posibles
enum TokenType {
    IDENTIFIER,
    REAL_NUMBER,
    INVALID,
    OPERATOR_ADDITIVE,
    OPERATOR_MULTIPLICATIVE,
    DOLLAR_SYMBOL,  // Nuevo tipo para el símbolo del dólar
    EQUAL_SYMBOL,   // Nuevo tipo para el símbolo igual
    UNDERSCORE_SYMBOL, // Nuevo tipo para el guion bajo
    TAB_SYMBOL, // Nuevo tipo para el tabulador
    PARENTESIS_IZQ_SYMBOL, // Nuevo tipo para el paréntesis izquierdo
    PARENTESIS_DER_SYMBOL, // Nuevo tipo para el paréntesis derecho
    ASTERISCO_SYMBOL, // Nuevo tipo para el asterisco
    SLASH_SYMBOL, // Nuevo tipo para la barra inclinada (/)
    PIPE_SYMBOL, // Nuevo tipo para la barra vertical (|)
    DOUBLE_PIPE_SYMBOL, // Nuevo tipo para la doble barra vertical (||)
    PUNTO_SYMBOL, // Nuevo tipo para el punto (.)
    MENOS_SYMBOL, // Nuevo tipo para el símbolo menos (-)
    END_OF_INPUT
};

// Clase para representar un token
class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

// Clase para el analizador léxico
class Lexer {
private:
    std::string input;
    size_t position;

    // Función para obtener el carácter actual
    char currentChar() const {
        if (position < input.length()) {
            return input[position];
        } else {
            return '\0'; // Fin de la cadena de entrada
        }
    }

    // Función para avanzar al siguiente carácter
    void consumeChar() {
        position++;
    }

public:
    // Constructor que recibe la cadena de entrada
    Lexer(const std::string& str) : input(str), position(0) {}

    // Función para reportar errores léxicos
    void reportError(const std::string& message) const {
        std::cerr << "Error lexico: " << message << " (Posicion: " << position << ")\n";
    }

    // Función para obtener el siguiente token
    Token getNextToken() {
        // Ignorar espacios en blanco
        while (std::isspace(currentChar())) {
            consumeChar();
        }

        if (std::isalpha(currentChar())) {
            // Identificadores: letra(letra|digito|_)*
            std::string identifier;
            while (std::isalnum(currentChar()) || currentChar() == '_') {
                identifier += currentChar();
                consumeChar();
            }
            return Token(IDENTIFIER, identifier);
        } else if (std::isdigit(currentChar())) {
            // Números Reales: entero.entero+
            std::string realNumber;
            while (std::isdigit(currentChar())) {
                realNumber += currentChar();
                consumeChar();
            }
            if (currentChar() == '.') {
                realNumber += currentChar();
                consumeChar();
                while (std::isdigit(currentChar())) {
                    realNumber += currentChar();
                    consumeChar();
                }
                return Token(REAL_NUMBER, realNumber);
            } else {
                // Número real inválido (sin parte decimal)
                reportError("Numero real invalido (sin parte decimal)");
                return Token(INVALID, realNumber);
            }
        } else if (currentChar() == '+') {
            consumeChar();
            return Token(OPERATOR_ADDITIVE, "+");
        } else if (currentChar() == '*') {
            consumeChar();
            return Token(OPERATOR_MULTIPLICATIVE, "*");
        } else if (currentChar() == '$') {
            consumeChar();
            return Token(DOLLAR_SYMBOL, "$");
        } else if (currentChar() == '=') {
            consumeChar();
            return Token(EQUAL_SYMBOL, "=");
        } else if (currentChar() == '_') {
            consumeChar();
            return Token(UNDERSCORE_SYMBOL, "_");
        } else if (currentChar() == '\t') {
            consumeChar();
            return Token(TAB_SYMBOL, "\\t");
        } else if (currentChar() == '(') {
            consumeChar();
            return Token(PARENTESIS_IZQ_SYMBOL, "(");
        } else if (currentChar() == ')') {
            consumeChar();
            return Token(PARENTESIS_DER_SYMBOL, ")");
        } else if (currentChar() == '*') {
            consumeChar();
            return Token(ASTERISCO_SYMBOL, "*");
        } else if (currentChar() == '/') {
            consumeChar();
            if (currentChar() == '/') {
                consumeChar();
                return Token(DOUBLE_PIPE_SYMBOL, "||");
            } else {
                return Token(SLASH_SYMBOL, "/");
            }
        } else if (currentChar() == '|') {
            consumeChar();
            if (currentChar() == '|') {
                consumeChar();
                return Token(DOUBLE_PIPE_SYMBOL, "||");
            } else {
                return Token(PIPE_SYMBOL, "|");
            }
        } else if (currentChar() == '.') {
            consumeChar();
            return Token(PUNTO_SYMBOL, ".");
        } else if (currentChar() == '-') {
            consumeChar();
            return Token(MENOS_SYMBOL, "-");
        } else if (currentChar() == '\0') {
            // Fin de la cadena de entrada
            return Token(END_OF_INPUT, "");
        } else {
            // Símbolo no identificado
            reportError("Simbolo no identificado");
            consumeChar(); // Avanzar al siguiente carácter
            return Token(INVALID, std::string(1, currentChar()));
        }
    }
};

int main() {
    // Solicitar al usuario que ingrese una cadena para analizar léxicamente
    std::string input;
    std::cout << "Ingrese una cadena para analizar lexicamente: ";
    std::getline(std::cin, input);

    // Crear un objeto Lexer con la cadena de entrada
    Lexer lexer(input);

    // Obtener y mostrar los tokens hasta que se encuentre un token inválido
    Token token = lexer.getNextToken();
    while (token.type != END_OF_INPUT) {
        // Mostrar información sobre el token
        std::cout << "Token: " << token.value << " - Tipo: ";
        switch (token.type) {
            case IDENTIFIER:
                std::cout << "Identificador\n";
                break;
            case REAL_NUMBER:
                std::cout << "Numero Real\n";
                break;
            case OPERATOR_ADDITIVE:
                std::cout << "Operador Aditivo\n";
                break;
            case OPERATOR_MULTIPLICATIVE:
                std::cout << "Operador Multiplicativo\n";
                break;
            case DOLLAR_SYMBOL:
                std::cout << "Simbolo de Dolar\n";
                break;
            case EQUAL_SYMBOL:
                std::cout << "Simbolo Igual\n";
                break;
            case UNDERSCORE_SYMBOL:
                std::cout << "Guion Bajo\n";
                break;
            case TAB_SYMBOL:
                std::cout << "Tabulador\n";
                break;
            case PARENTESIS_IZQ_SYMBOL:
                std::cout << "Parentesis Izquierdo\n";
                break;
            case PARENTESIS_DER_SYMBOL:
                std::cout << "Parentesis Derecho\n";
                break;
            case ASTERISCO_SYMBOL:
                std::cout << "Asterisco\n";
                break;
            case SLASH_SYMBOL:
                std::cout << "Barra Inclinada (/)\n";
                break;
            case PIPE_SYMBOL:
                std::cout << "Barra Vertical (|)\n";
                break;
            case DOUBLE_PIPE_SYMBOL:
                std::cout << "Doble Barra Vertical (||)\n";
                break;
            case PUNTO_SYMBOL:
                std::cout << "Punto (.)\n";
                break;
            case MENOS_SYMBOL:
                std::cout << "Simbolo Menos (-)\n";
                break;
            case INVALID:
                std::cout << "Simbolo No Identificado\n";
                break;
            default:
                std::cout << "Desconocido\n";
                break;
        }
        // Obtener el siguiente token
        token = lexer.getNextToken();
    }

    return 0;
}

