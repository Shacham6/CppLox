#include <utility>

#include <utility>

#pragma once

#include <types.hh>

namespace Shach {
  enum TokenType {
    // Single-character tokens.
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
        BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
        IDENTIFIER, STRING, NUMBER,

    // Keywords.
        AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, EOF_,
  };

  class Token {
    public:
      const TokenType Type;
      const string Lexeme;
      const string Literal;
      const int Line;

      Token(TokenType type, string lexeme, string literal, int line)
          : Type(type),
            Lexeme(std::move(lexeme)),
            Literal(std::move(literal)),
            Line(line) {}

      string ToString() const;
  };
}