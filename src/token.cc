// Project Level
#include <token.hh>

// STD & STL
#include <sstream>

// fmt
#include <fmt/format.h>

using Shach::TokenType;


static string ToString(Shach::TokenType tokenType) {
#define __T(tt, value) case tt : return value;

  switch (tokenType) {
    // Single-character tokens.
    __T(TokenType::LEFT_PAREN, "LEFT_PAREN")
    __T(TokenType::RIGHT_PAREN, "RIGHT_PAREN")
    __T(TokenType::LEFT_BRACE, "LEFT_BRACE")
    __T(TokenType::RIGHT_BRACE, "RIGHT_BRACE")
    __T(TokenType::COMMA, "COMMA")
    __T(TokenType::DOT, "DOT")
    __T(TokenType::MINUS, "MINUS")
    __T(TokenType::PLUS, "PLUS")
    __T(TokenType::SEMICOLON, "SEMICOLON")
    __T(TokenType::SLASH, "SLASH")
    __T(TokenType::STAR, "STAR")

    // One or two character tokens.
    __T(TokenType::BANG, "BANG")
    __T(TokenType::BANG_EQUAL, "BANG_EQUAL")
    __T(TokenType::EQUAL, "EQUAL")
    __T(TokenType::EQUAL_EQUAL, "EQUAL_EQUAL")
    __T(TokenType::GREATER, "GREATER")
    __T(TokenType::GREATER_EQUAL, "GREATER_EQUAL")
    __T(TokenType::LESS, "LESS")
    __T(TokenType::LESS_EQUAL, "LESS_EQUAL")

    // Literals.
    __T(TokenType::IDENTIFIER, "IDENTIFIER")
    __T(TokenType::STRING, "STRING")
    __T(TokenType::NUMBER, "NUMBER")

    // Keywords.
    __T(TokenType::AND, "AND")
    __T(TokenType::CLASS, "CLASS")
    __T(TokenType::ELSE, "ELSE")
    __T(TokenType::FALSE, "FALSE")
    __T(TokenType::FUN, "FUN")
    __T(TokenType::FOR, "FOR")
    __T(TokenType::IF, "IF")
    __T(TokenType::NIL, "NIL")
    __T(TokenType::OR, "OR")
    __T(TokenType::PRINT, "PRINT")
    __T(TokenType::RETURN, "RETURN")
    __T(TokenType::SUPER, "SUPER")
    __T(TokenType::THIS, "THIS")
    __T(TokenType::TRUE, "TRUE")
    __T(TokenType::VAR, "VAR")
    __T(TokenType::WHILE, "WHILE")
    __T(TokenType::EOF_, "EOF")

    default:
      return "";
  }

#undef __T
}


string Shach::Token::ToString() const {
  std::ostringstream s;
  s << ::ToString(Type) << " " << Lexeme << " " << Literal;
  return s.str();
}

